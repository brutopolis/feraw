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
        // copy content inside ""
        let str = '';
        i++; // skip the opening quote
        while (i < input.length) 
        {
            if (input[i] === '"') 
            {
                i++;
                break;
            }
            else if (input[i] === '\n')
            {
                // replace to a unused ascii character
                str += '\x14'; // ASCII 20 is a non-printable character
                i++;
                continue;
            }
            else if (input[i] === '\r')
            {
                // replace to a unused ascii character
                str += '\x15'; // ASCII 21 is a non-printable character
                i++;
                continue;
            }
            else if (input[i] === '\t')
            {
                // replace to a unused ascii character
                str += '\x16'; // ASCII 22 is a non-printable character
                i++;
                continue;
            }
            else if (input[i] === ' ')
            {                
                // replace to a unused ascii character
                str += '\x17'; // ASCII 23 is a non-printable character
                i++;
                continue;
            }
            else if (input[i] === ':')
            {
                // replace to a unused ascii character
                str += '\x18'; // ASCII 24 is a non-printable character
                i++;
                continue;
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

        tokens.push('#' + str);
    }

    function parseList()
    {
        i++; // skip [
        let tempTokens = [];
        let itemCount = 0;

        while (true) 
        {
            skipWhitespace();
            if (i >= input.length || input[i] === ']') 
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

    function parseBuffer()
    {
        i++; // skip [
        let tempTokens = [];
        let itemCount = 0;

        while (true) 
        {
            skipWhitespace();
            if (i >= input.length || input[i] === ']') 
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

        tokens.push('!', 'buffer', itemCount.toString(), ...tempTokens);
    }

    function parseRawToken() 
    {
        let start = i;
        while (i < input.length && !/\s/.test(input[i]) && !"()[]{},=;".includes(input[i]))
        {
            i++;
        }
        return input.slice(start, i);
    }

    function parseExpr() 
    {
        skipWhitespace();
        if (i >= input.length) return;

        if (input[i] === '"') 
        {
            parseString();
            return;
        }
        else if (input[i] === '[') 
        {
            parseList();
            return;
        }
        else if (input[i] === '{') // buffer
        {
            parseBuffer();
            return;
        }

        let start = i;
        let name = parseRawToken();
        skipWhitespace();

        if (input[i] === '(') 
        {
            if (name == 'skip' || name == 'back' || name == 'goto' || name == 'break' || name == '!')
            {
                switch (name)
                {
                    case 'skip':
                        tokens.push('>');
                        break;
                    case 'back':
                        tokens.push('<');
                        break;
                    case 'goto':
                        tokens.push(',');
                        break;
                    case 'break':
                        tokens.push(';');
                        break;
                    case '!':
                        tokens.push('!');
                        break;
                    default:
                        throw new Error(`Unknown command: ${name}`);
                }
            }
            else 
            {
                tokens.push('!', name);
            }

            i++; // skip (
            while (true) 
            {
                skipWhitespace();
                if (i >= input.length || input[i] === ')') 
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
            tokens.push(name);
        }
    }

    while (i < input.length) 
    {
        skipWhitespace();
        if (i >= input.length) break;
        if (input[i] === ';') 
        {
            i++;
            continue;
        }

        let start = i;
        let name = parseRawToken();
        skipWhitespace();

        if (input[i] === '=') 
        {
            i++;
            skipWhitespace();
            tokens.push("!", "register", "context", "!", "rename", "#" + name);
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
