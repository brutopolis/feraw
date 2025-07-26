function tokenize(input) 
{
    let tokens = [];
    let i = 0;

    function skipWhitespace()
    {
        while (/\s/.test(input[i])) i++;
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
        while (/[a-zA-Z0-9_]/.test(input[i])) i++;
        return input.slice(start, i);
    }

    function parseNumber() 
    {
        let start = i;
        while (/[0-9]/.test(input[i])) i++;
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
        skipWhitespace();

        if (input[i] === '(') 
        {
            tokens.push('!', id);
            i++; // skip (
            while (true) {
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
    for (let command of commands) {
        command = command.trim();
        if (command) {
            result.push(tokenize(command).reverse());
        }
    }

    let result_string = result.map(tokens => tokens.join(' ')).join('\n');
    return result_string.trim();
}