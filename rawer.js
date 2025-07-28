
function splitOutsideStrings(input, char = ';') {
    let parts = [];
    let current = '';
    let inString = false;
    let escape = false;

    for (let i = 0; i < input.length; i++) {
        let c = input[i];

        if (escape) {
            current += c;
            escape = false;
            continue;
        }

        if (c === '\\') {
            current += c;
            escape = true;
            continue;
        }

        if (c === '"') {
            inString = !inString;
            current += c;
            continue;
        }

        if (c === '{') // lets make sure we don't split inside a block
        {
            let blockDepth = 1;
            current += c;
            i++;
            while (i < input.length && blockDepth > 0) {
                if (input[i] === '{') {
                    blockDepth++;
                } else if (input[i] === '}') {
                    blockDepth--;
                }
                current += input[i];
                i++;
            }
            i--; // adjust for the loop increment
            continue;
        }
        else if (c === '(' || c === ')') // lets make sure we don't split inside a function call
        {
            let parenDepth = c === '(' ? 1 : -1;
            current += c;
            i++;
            while (i < input.length && parenDepth !== 0) {
                if (input[i] === '(') {
                    parenDepth++;
                } else if (input[i] === ')') {
                    parenDepth--;
                }
                current += input[i];
                i++;
            }
            i--; // adjust for the loop increment
            continue;
        }
        else if (c === '[' || c === ']') // lets make sure we don't split inside a list
        {
            let listDepth = c === '[' ? 1 : -1;
            current += c;
            i++;
            while (i < input.length && listDepth !== 0) {
                if (input[i] === '[') {
                    listDepth++;
                } else if (input[i] === ']') {
                    listDepth--;
                }
                current += input[i];
                i++;
            }
            i--; // adjust for the loop increment
            continue;
        }
        else if(c === '/' && input[i + 1] === '/') { // single-line comment
            while (i < input.length && input[i] !== '\n') {
                current += input[i];
                i++;
            }
            current += '\n'; // preserve the newline
            continue;
        }
        else if(c === '/' && input[i + 1] === '*') { // multi-line comment
            current += c; // add the first /
            current += input[i + 1]; // add the second *
            i += 2; // skip the /*
            while (i < input.length) {
                current += input[i];
                if (input[i] === '*' && input[i + 1] === '/') {
                    current += '/'; // add the closing /
                    current += input[i + 1]; // add the closing *
                    i += 2; // skip the */
                    break;
                }
                i++;
            }
            continue;
        }

        if (c === char && !inString) {
            parts.push(current.trim());
            current = '';
            continue;
        }

        current += c;
    }

    if (current.trim() !== '') {
        parts.push(current.trim());
    }

    return parts;
}

let counter = 0;

function preprocessTernary(code) {
    return code.split('\n').map(line => {
        let i = 0;
        let inString = false;
        let buffer = '';
        let qmark = -1, colon = -1, semicolon = -1;

        while (i < line.length) {
            let c = line[i];

            if (c === '"') {
                inString = !inString;
            } else if (!inString) {
                if (c === '?' && qmark === -1) qmark = i;
                else if (c === ':' && colon === -1) colon = i;
                else if (c === ';' && semicolon === -1) semicolon = i;
            }

            buffer += c;
            i++;
        }

        if (qmark === -1 || colon === -1 || semicolon === -1) return line;

        let condition = buffer.slice(0, qmark).trim();
        let a = buffer.slice(qmark + 1, colon).trim();
        let b = buffer.slice(colon + 1, semicolon).trim();

        let id = counter++;
        let result = [
            `if(${condition}, cond_true_${id}, cond_false_${id});`,
            `cond_true_${id}:`,
            `${a};`,
            `goto(after_cond_${id});`,
            `cond_false_${id}:`,
            `${b};`,
            `after_cond_${id}:`
        ];

        return result.join('\n');
    }).join('\n');
}

function tokenize(input) {
    let tokens = [];
    let i = 0;
    const MAX_TOKENS = 1e6;
    const MAX_DEPTH = 1000;

    function skipWhitespace() {
        let safety = 0;
        while (i < input.length) {
            if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: loop exceeded safe bounds");

            if (/\s/.test(input[i])) {
                i++;
            } else if (input[i] === '/' && input[i + 1] === '/') {
                i += 2;
                while (i < input.length && input[i] !== '\n') {
                    if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: comment loop too long");
                    i++;
                }
            } else if (input[i] === '/' && input[i + 1] === '*') {
                i += 2;
                while (i < input.length && !(input[i] === '*' && input[i + 1] === '/')) {
                    if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: block comment loop too long");
                    i++;
                }
                if (i < input.length) i += 2;
            } else break;
        }
    }

    function parseString() {
        let str = '';
        i++; // skip opening "

        let safety = 0;
        while (i < input.length) {
            if (++safety > MAX_TOKENS) throw new Error("parseString: unterminated string");

            if (input[i] === '"') {
                i++;
                break;
            }

            if (input[i] === '\n') str += '\x14';
            else if (input[i] === '\r') str += '\x15';
            else if (input[i] === '\t') str += '\x16';
            else if (input[i] === ' ') str += '\x17';
            else if (input[i] === ':') str += '\x18';
            else if (input[i] === '\\') {
                i++;
                const esc = input[i++];
                if (esc === 'n') str += '\n';
                else if (esc === 't') str += '\t';
                else if (esc === '"') str += '"';
                else if (esc === '\\') str += '\\';
                else str += esc;
                continue;
            } else {
                str += input[i];
            }

            i++;
        }

        if (safety >= MAX_TOKENS) throw new Error("String not terminated");

        tokens.push('#' + str);
    }

    function parseList(depth = 0) {
        if (depth > MAX_DEPTH) throw new Error("Max list nesting exceeded");
        i++; // skip [

        let tempTokens = [];
        let itemCount = 0;

        let safety = 0;
        while (true) {
            if (++safety > MAX_TOKENS) throw new Error("parseList: unterminated list");

            skipWhitespace();
            if (i >= input.length) throw new Error("parseList: unexpected end of input");
            if (input[i] === ']') {
                i++;
                break;
            }

            let saved = tokens;
            tokens = [];
            parseExpr(depth + 1);
            tempTokens.push(...tokens);
            itemCount++;
            tokens = saved;

            skipWhitespace();
            if (input[i] === ',') i++;
        }

        tokens.push('!', 'list', itemCount.toString(), ...tempTokens);
    }


    function parseRawToken() {
        let start = i;
        while (i < input.length && !/\s/.test(input[i]) && !"()[]{},=;".includes(input[i])) {
            i++;
        }
        return input.slice(start, i);
    }

    function parseExpr(depth = 0) {
        if (depth > MAX_DEPTH) throw new Error("Max expression nesting exceeded");

        skipWhitespace();
        if (i >= input.length) return;

        if (input[i] === '"') return parseString();
        if (input[i] === '[') return parseList(depth);
        //if (input[i] === '{') return parseBlock(depth);

        let name = parseRawToken();
        skipWhitespace();

        if (input[i] === '(') {
            if (["skip", "back", "goto", "break", "if", "!"].includes(name)) {
                tokens.push({ skip: '>', back: '<', goto: ',', break: ';', '!': '!', 'if': '?', 'ifelse': '??'}[name]);
            } else {
                tokens.push('!', name);
            }

            i++; // skip (
            let safety = 0;
            while (true) {
                if (++safety > MAX_TOKENS) throw new Error("parseExpr: function call too long");
                skipWhitespace();
                if (i >= input.length) throw new Error("Function call not closed with )");
                if (input[i] === ')') {
                    i++;
                    break;
                }
                parseExpr(depth + 1);
                skipWhitespace();
                if (input[i] === ',') i++;
            }
        } else {
            tokens.push(name);
        }
    }

    let safety = 0;
    while (i < input.length) {
        if (++safety > MAX_TOKENS) throw new Error("Main loop exceeded safe bounds");
        skipWhitespace();
        if (i >= input.length) break;

        let start = i;
        let name = parseRawToken();
        skipWhitespace();

        if (input[i] === '=') {
            i++;
            skipWhitespace();
            tokens.push("!", "register", "context", "!", "rename", "#" + name);
            parseExpr();
        } else {
            i = start;
            parseExpr();
        }
    }

    return tokens;
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

function rawer_compile(input) 
{
    let commands = splitOutsideStrings(preprocessTernary(input), ';');
    let result = [];
    for (let command of commands) 
    {
        if (command) 
        {
            result.push(tokenize(command));
        }
    }

    let result_string = rawer_labelparser(result);
    return result_string;
}