function tokenize(input) 
{
    let tokens = [];
    let i = 0;

    function skipWhitespace() 
    {
        while (i < input.length) 
        {
            if (/\s/.test(input[i])) 
            {
                i++;
            } 
            else if (input[i] === '/' && input[i + 1] === '/') 
            {
                i += 2;
                while (i < input.length && input[i] !== '\n') i++;
            } 
            else if (input[i] === '/' && input[i + 1] === '*') 
            {
                i += 2;
                while (i < input.length && !(input[i] === '*' && input[i + 1] === '/')) i++;
                if (i < input.length) i += 2;
            } 
            else break;
        }
    }

    function parseString() 
    {
        i++; // skip opening "
        let str = '';
        while (i < input.length) 
        {
            if (input[i] === '"') 
            {
                i++;
                break;
            }
            if (input[i] === '\\') 
            {
                i++;
                const esc = input[i++];
                if (esc === 'n') str += '\n';
                else if (esc === 't') str += '\t';
                else if (esc === '"') str += '"';
                else if (esc === '\\') str += '\\';
                else str += esc;
            } 
            else 
            {
                str += input[i++];
            }
        }

        tokens.push('!', 'string', str.length.toString());
        for (let c of str) tokens.push(c.charCodeAt(0).toString());
    }

    function parseIdentifier() 
    {
        let start = i;
        if (i >= input.length || !/[a-zA-Z_]/.test(input[i])) return null;

        i++;
        while (i < input.length && /[a-zA-Z0-9_]/.test(input[i])) i++;

        if (input[i] === ':') 
        {
            i++;
            return input.slice(start, i);
        }

        return input.slice(start, i);
    }

    function parseNumber() 
    {
        let start = i;

        if (input[i] === '0' && i + 1 < input.length) {
            let next = input[i + 1];
            if (next === 'b' || next === 'B') {
                i += 2;
                while (i < input.length && /[01]/.test(input[i])) i++;
                return input.slice(start, i);
            }
            if (next === 'x' || next === 'X') {
                i += 2;
                while (i < input.length && /[0-9a-fA-F]/.test(input[i])) i++;
                return input.slice(start, i);
            }
            if (next === 'o' || next === 'O') {
                i += 2;
                while (i < input.length && /[0-7]/.test(input[i])) i++;
                return input.slice(start, i);
            }
        }

        let seenDot = false;
        while (i < input.length) {
            if (/[0-9]/.test(input[i])) {
                i++;
            } else if (input[i] === '.' && !seenDot) {
                seenDot = true;
                i++;
            } else {
                break;
            }
        }

        return input.slice(start, i);
    }


    function parseList() 
    {
        i++; // skip [

        let tempTokens = [];
        let itemCount = 0;

        while (true) 
        {
            skipWhitespace();
            if (input[i] === ']') 
            {
                i++; // skip ]
                break;
            }

            let saved = tokens;
            tokens = [];
            parseExpr();
            tempTokens.push(...tokens);
            itemCount++;
            tokens = saved;

            skipWhitespace();
            if (input[i] === ',') i++;
        }

        tokens.push('!', 'list', itemCount.toString(), ...tempTokens);
    }

    function parseExpr() 
    {
        skipWhitespace();

        if (input[i] === '"') 
        {
            parseString();
            return;
        }

        if (input[i] === '[') 
        {
            parseList();
            return;
        }

        if (/[0-9]/.test(input[i])) 
        {
            tokens.push(parseNumber());
            return;
        }

        let id = parseIdentifier();
        if (!id) return;

        skipWhitespace();

        if (input[i] === '(') 
        {
            tokens.push('!', id);
            i++; // skip (
            while (true) 
            {
                skipWhitespace();
                if (input[i] === ')') 
                {
                    i++;
                    break;
                }
                parseExpr();
                skipWhitespace();
                if (input[i] === ',') i++;
            }
        } 
        else 
        {
            tokens.push(id);
        }
    }

    while (i < input.length) 
    {
        skipWhitespace();
        if (input[i] === ';') 
        {
            i++;
            continue;
        }

        let start = i;
        let name = parseIdentifier();
        if (!name) 
        {
            i++;
            continue;
        }

        skipWhitespace();
        if (input[i] === '=') 
        {
            i++;
            skipWhitespace();
            tokens.push("!!", "register", "!", "rename", "!", "string", name.length.toString());
            for (let c of name) tokens.push(c.charCodeAt(0).toString());
            parseExpr();
        } 
        else 
        {
            i = start;
            parseExpr();
        }
    }

    return tokens;
}

function rawer_compile(input) 
{
    let commands = input.split(';');
    let result = [];
    for (let command of commands) 
    {
        command = command.trim();
        if (command) 
        {
            result.push(tokenize(command));
        }
    }
    
    let result_string = rawer_labelparser(result);
    return result_string;
}

function rawer_labelparser(original_input) 
{
    // we need this to know exactly where the labels were positioned originally
    let unreversed_input = original_input.map(tokens => tokens.join(' ')).join(' ');
    
    // split by any kind of whitespace
    let splited = unreversed_input.toString().split(/\s+/);
    
    let input = original_input.map(tokens => tokens.reverse().join(' '))
        .join('\n').toString();


    // remove empty strings
    splited = splited.filter(token => token.trim() !== '');
    
    let labels = [];
    let correction = 0;
    for (let i = 0; i < splited.length; i++)
    {
        let word = splited[i];
        if (word.endsWith(':')) 
        {
            let label = word.slice(0, -1);
            labels.push([label, i - correction]);
            correction++;
        }
    }

    // lets remove all label: from the input
    input = input.replaceAll(/(\w+):/g, '');

    
    for (let label of labels) 
    {
        input = input.replaceAll(new RegExp(`\\b${label[0]}\\b`, 'g'), `${label[1]}`);
    }
    return input;
}
