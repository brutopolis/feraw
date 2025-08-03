
function splitOutsideStrings(input, char = ';') 
{
    let parts = [];
    let current = '';
    let inString = false;
    let escape = false;

    for (let i = 0; i < input.length; i++) 
    {
        let c = input[i];

        if (escape) 
        {
            current += c;
            escape = false;
            continue;
        }

        if (c === '\\') 
        {
            current += c;
            escape = true;
            continue;
        }

        if (c === '"') 
        {
            inString = !inString;
            current += c;
            continue;
        }

        if (c === '{') // lets make sure we don't split inside a block
        {
            let blockDepth = 1;
            current += c;
            i++;
            while (i < input.length && blockDepth > 0) 
            {
                if (input[i] === '{') 
                {
                    blockDepth++;
                } 
                else if (input[i] === '}') 
                {
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
            while (i < input.length && parenDepth !== 0) 
            {
                if (input[i] === '(') 
                {
                    parenDepth++;
                } 
                else if (input[i] === ')') 
                {
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
            while (i < input.length && listDepth !== 0) 
            {
                if (input[i] === '[') 
                {
                    listDepth++;
                } 
                else if (input[i] === ']') 
                {
                    listDepth--;
                }
                current += input[i];
                i++;
            }
            i--; // adjust for the loop increment
            continue;
        }
        else if (c === '{' || c === '}') // lets make sure we don't split inside a obj
        {
            let listDepth = c === '{' ? 1 : -1;
            current += c;
            i++;
            while (i < input.length && listDepth !== 0) 
            {
                if (input[i] === '{') 
                {
                    listDepth++;
                } 
                else if (input[i] === '}') 
                {
                    listDepth--;
                }
                current += input[i];
                i++;
            }
            i--; // adjust for the loop increment
            continue;
        }
        else if(c === '/' && input[i + 1] === '/') 
        { // single-line comment
            while (i < input.length && input[i] !== '\n') 
            {
                current += input[i];
                i++;
            }
            current += '\n'; // preserve the newline
            continue;
        }
        else if(c === '/' && input[i + 1] === '*') 
        { // multi-line comment
            current += c; // add the first /
            current += input[i + 1]; // add the second *
            i += 2; // skip the /*
            while (i < input.length) 
            {
                current += input[i];
                if (input[i] === '*' && input[i + 1] === '/') 
                {
                    current += '/'; // add the closing /
                    current += input[i + 1]; // add the closing *
                    i += 2; // skip the */
                    break;
                }
                i++;
            }
            i++;
            continue;
        }

        if (c === char && !inString) 
        {
            parts.push(current.trim());
            current = '';
            continue;
        }

        current += c;
    }

    if (current.trim() !== '') 
    {
        parts.push(current.trim());
    }

    return parts;
}

function tokenize(input) 
{
    let tokens = [];
    let i = 0;

    function skipWhitespace() 
    {
        let safety = 0;
        while (i < input.length) 
        {

            if (/\s/.test(input[i])) 
            {
                i++;
            } 
            else if (input[i] === '/' && input[i + 1] === '/') 
            {
                i += 2;
                while (i < input.length && input[i] !== '\n') 
                {
                    i++;
                }
            } 
            else if (input[i] === '/' && input[i + 1] === '*') 
            {
                i += 2;
                while (i < input.length && !(input[i] === '*' && input[i + 1] === '/')) 
                {
                    i++;
                }
                if (i < input.length) i += 2;
            } else break;
        }
    }

    function parseString() 
    {
        let str = '';
        i++; // skip opening "

        let safety = 0;
        while (i < input.length) 
        {

            if (input[i] === '"') 
            {
                i++;
                break;
            }

            if (input[i] === '#') str += '\x013';
            else if (input[i] === '\n') str += '\x14';
            else if (input[i] === '\r') str += '\x15';
            else if (input[i] === '\t') str += '\x16';
            else if (input[i] === ' ') str += '\x17';
            else if (input[i] === ':') str += '\x18';
            else if (input[i] === '\\') 
            {
                i++;
                const esc = input[i++];
                if (esc === 'n') str += '\n';
                else if (esc === 't') str += '\t';
                else if (esc === '"') str += '"';
                else if (esc === '\\') str += '\\';
                else str += esc;
                continue;
            } 
            else 
            {
                str += input[i];
            }

            i++;
        }


        tokens.push('#' + str);
    }

    function parseList(depth = 0) 
    {
        i++; // skip [

        let tempTokens = [];
        let itemCount = 0;

        let safety = 0;
        while (true) 
        {
            skipWhitespace();
            if (i >= input.length) throw new Error("parseList: unexpected end of input");
            if (input[i] === ']') 
            {
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

    
    function parseBlock(depth = 0)
    {
        // to be used in future, for something i don't know yet
    }

    function parseRawToken() 
    {
        let start = i;
        while (i < input.length && !/\s/.test(input[i]) && !"()[]{},=;".includes(input[i])) {
            i++;
        }
        return input.slice(start, i);
    }

    function parseExpr(depth = 0) 
    {
        skipWhitespace();
        if (i >= input.length) return;

        if (input[i] === '"') return parseString();
        if (input[i] === '[') return parseList(depth);
        
        // in near future we will use this for something, block name is ilustrative only
        // if (input[i] === '{') return parseBlock(depth);

        // 0x, 0b, 0o
        if (input[i] === '0') 
        {
            let start = i;
            i++;
            while (
                i < input.length &&
                !/\s|[\]\[\(\)\{\},]/.test(input[i]) 
            ) {
                i++;
            }

            let numStr = input.slice(start, i);
            let num = Number(numStr);

            if (isNaN(num)) throw new Error("parseExpr: invalid number format: " + numStr);
            tokens.push(num + '');
            return;
        }

        let name = parseRawToken();
        if (!name) throw new Error("parseExpr: invalid or empty token");

        if (["true", "false", "null", "stack", "context"].includes(name))
        {
            switch (name)
            {
                case "true":
                    tokens.push('1');
                    return;
                case "false":
                    tokens.push('0');
                    return;
                case "null":
                    tokens.push('!', 'retype', '0', '0');
                    return;
                case "stack":
                    tokens.push('&');
                    return;
                case "context":
                    tokens.push('@');
                    return;
            } 
        }

        skipWhitespace();
        if (i >= input.length) 
        {
            tokens.push(name);
            return;
        }

        if (input[i] === '(')
        {
            if (["!", "?"].includes(name)) 
            {
                tokens.push(name);
            }
            else if (["if", "goto", "else"].includes(name)) 
            {
                switch (name)
                {
                    case "if":
                        tokens.push("?");
                        break;
                    case "goto":
                    case "else":
                        tokens.push('?', '1');
                        break;
                }
            }
            else 
            {
                tokens.push('!', name);
            }

            i++; // skip '('
            let safety = 0;

            while (true) 
            {

                skipWhitespace();
                if (i >= input.length) throw new Error("Function call not closed with )");

                if (input[i] === ')') 
                {
                    i++;
                    break;
                }

                parseExpr(depth + 1);
                skipWhitespace();
                if (input[i] === ',') i++;
            }
        } 
        else 
        {
            let exprTokens = [name];

            while (true) 
            {
                skipWhitespace();

                if (input[i] === '(') 
                {
                    i++; // skip '('
                    let argTokens = [];
                    let safety = 0;

                    while (true) 
                    {
                        skipWhitespace();
                        if (i >= input.length) throw new Error("Function call not closed with )");

                        if (input[i] === ')') 
                        {
                            i++;
                            break;
                        }

                        parseExpr(depth + 1);
                        argTokens.push(...tokens.splice(tokens.length - 1));
                        skipWhitespace();
                        if (input[i] === ',') i++;
                    }

                    exprTokens = ['!', ...exprTokens, ...argTokens];
                    continue;
                }

                break;
            }

            skipWhitespace();

            if (input[i] === '=') 
            {
                i++; // skip '='
                skipWhitespace();

                parseExpr(depth + 1);
                let value = tokens.splice(tokens.length - 1);

                tokens.push('!', 'set', ...value, ...exprTokens);
                return;
            }

            tokens.push(...exprTokens);
        }
    }


    let safety = 0;
    while (i < input.length) 
    {
        skipWhitespace();
        if (i >= input.length) break;

        let start = i;
        let name = parseRawToken();
        skipWhitespace();

        if (input[i] === '=') 
        {
            i++;
            skipWhitespace();
            tokens.push("!", "define", "@", "!", "rename");
            parseExpr();
            tokens.push("#" + name);
        } 
        else 
        {
            i = start;
            parseExpr();
        }
    }

    return tokens;
}

function feraw_labelparser(original_input) 
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

function expandMacros(input) 
{
    const macroMap = new Map();
    // --- Helper function to find matching closing character ---
    function findMatching(input, start, openChar, closeChar) 
    {
        let depth = 1;
        let inString = false;
        let stringChar = '';
        let escapeNext = false;
        for (let i = start + 1; i < input.length; i++) 
        {
            let char = input[i];
            if (escapeNext) 
            {
                escapeNext = false;
                continue;
            }
            if (char === '\\') 
            {
                escapeNext = true;
                continue;
            }
            if (!inString && (char === '"' || char === "'")) 
            {
                inString = true;
                stringChar = char;
                continue;
            } 
            else if (inString && char === stringChar) 
            {
                inString = false;
                stringChar = '';
                continue;
            }
            // Ignore delimiters inside strings for nesting calculation
            if (inString) 
            {
                continue;
            }
            if (char === openChar)
            {
                depth++;
            } 
            else if (char === closeChar) 
            {
                depth--;
                if (depth === 0) 
                {
                    return i;
                }
            }
        }
        return -1;
    }

    let i = 0;
    let outputWithoutDefs = '';
    while (i < input.length) 
    {
        // Basic string handling for definition parsing
        if (input[i] === '"' || input[i] === "'") 
        {
            let stringChar = input[i];
            outputWithoutDefs += input[i];
            i++;
            let escapeNext = false;
            while (i < input.length) 
            {
                if (escapeNext) 
                {
                    outputWithoutDefs += input[i];
                    escapeNext = false;
                    i++;
                    continue;
                }
                if (input[i] === '\\')
                {
                    outputWithoutDefs += input[i];
                    escapeNext = true;
                    i++;
                    continue;
                }
                if (input[i] === stringChar) 
                {
                    outputWithoutDefs += input[i];
                    i++;
                    break;
                }
                outputWithoutDefs += input[i];
                i++;
            }
            continue;
        }
        // Skip whitespace and comments for definition parsing
        if (/\s/.test(input[i])) 
        {
            outputWithoutDefs += input[i];
            i++;
            continue;
        }
        if (input[i] === '/' && i + 1 < input.length) 
        {
            if (input[i + 1] === '/') 
            {
                while (i < input.length && input[i] !== '\n') 
                {
                    outputWithoutDefs += input[i];
                    i++;
                }
                if (i < input.length) 
                {
                    outputWithoutDefs += input[i];
                    i++;
                }
                continue;
            } 
            else if (input[i + 1] === '*') 
            {
                outputWithoutDefs += input[i]; i++;
                outputWithoutDefs += input[i]; i++;
                while (i < input.length) 
                {
                    if (input[i] === '*' && i + 1 < input.length && input[i + 1] === '/') 
                    {
                        outputWithoutDefs += input[i]; i++;
                        outputWithoutDefs += input[i]; i++;
                        break;
                    }
                    outputWithoutDefs += input[i];
                    i++;
                }
                continue;
            }
        }
        
        let potentialStart = i;
        let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(input.substring(i));
        if (nameMatch) 
        {
            let macroName = nameMatch[1];
            i += nameMatch[0].length;
            while (i < input.length && /\s/.test(input[i])) i++;
            if (i < input.length && input[i] === '=') 
            {
                i++; // Skip '='
                while (i < input.length && /\s/.test(input[i])) i++;
                // Check for 'macro' keyword
                if (i + 5 <= input.length && input.substring(i, i + 5) === 'macro') 
                {
                    i += 5; // Skip 'macro'
                    while (i < input.length && /\s/.test(input[i])) i++;
                    if (i < input.length && input[i] === '(') 
                    {
                        let bodyStart = i + 1;
                        let bodyEnd = findMatching(input, i, '(', ')'); // Find matching ')'
                        if (bodyEnd !== -1) 
                        {
                            let macroBody = input.substring(bodyStart, bodyEnd);
                            // Store the macro definition
                            macroMap.set(macroName, macroBody);
                            // Skip the entire definition including ';'
                            i = bodyEnd + 1; // Move past ')'
                            while (i < input.length && /\s/.test(input[i])) i++;
                            if (i < input.length && input[i] === ';') 
                            {
                                i++; // Skip ';'
                            } // else maybe warn about missing semicolon?
                            // Do NOT add this definition to outputWithoutDefs
                            continue; // Continue processing the *rest* of the input
                        } 
                        else 
                        {
                            console.error("Unterminated macro definition for:", macroName);
                            i = potentialStart;
                        }
                    } 
                    else 
                    {
                        // 'macro' not followed by '(', not a definition
                        i = potentialStart;
                    }
                } 
                else 
                {
                    // '=' not followed by 'macro', not a definition
                    i = potentialStart;
                }
            } 
            else 
            {
                // Name not followed by '=', not a definition
                i = potentialStart;
            }
        }
        outputWithoutDefs += input[potentialStart];
        i = potentialStart + 1;
    }
    // Work on the input without definitions
    input = outputWithoutDefs;
    // --- Step 2: Expand Macro Calls (Unchanged) ---
    let previous;
    do {
        previous = input;
        let outputAfterExpansion = '';
        i = 0;
        // --- Main Expansion Loop ---
        while (i < input.length) 
        {
            // --- Attempt to Match a Macro Call: identifier '(' ---
            let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(input.substring(i));
            if (nameMatch) 
            {
                let callName = nameMatch[1];
                let callStart = i + callName.length;
                // Check if it's a macro call: name '(' (skip whitespace)
                let tempIndex = callStart;
                while (tempIndex < input.length && /\s/.test(input[tempIndex])) tempIndex++;
                if (tempIndex < input.length && input[tempIndex] === '(') 
                {
                    let argsStart = tempIndex + 1;
                    let argsEnd = findMatching(input, tempIndex, '(', ')');
                    if (argsEnd !== -1) 
                    {
                        const macroBody = macroMap.get(callName);
                        if (macroBody !== undefined) 
                        {
                            let argsStr = input.substring(argsStart, argsEnd);
                            // --- Split Arguments Robustly ---
                            function splitArgsRobust(str) 
                            {
                                let args = [];
                                let current = '';
                                let depth = 0;
                                let inArgString = false;
                                let argStringChar = '';
                                let argEscapeNext = false;
                                for (let j = 0; j < str.length; j++) 
                                {
                                    let argChar = str[j];
                                    if (argEscapeNext) 
                                    {
                                        current += argChar;
                                        argEscapeNext = false;
                                        continue;
                                    }
                                    if (argChar === '\\') 
                                    {
                                        current += argChar;
                                        argEscapeNext = true;
                                        continue;
                                    }
                                    if (!inArgString && (argChar === '"' || argChar === "'")) 
                                    {
                                        inArgString = true;
                                        argStringChar = argChar;
                                        current += argChar;
                                        continue;
                                    } 
                                    else if (inArgString && argChar === argStringChar) 
                                    {
                                        inArgString = false;
                                        argStringChar = '';
                                        current += argChar;
                                        continue;
                                    }
                                    if (inArgString) 
                                    {
                                        current += argChar;
                                        continue;
                                    }
                                    if (argChar === '(' || argChar === '[' || argChar === '{') 
                                    {
                                        depth++;
                                    } 
                                    else if (argChar === ')' || argChar === ']' || argChar === '}') 
                                    {
                                        depth--;
                                    }
                                    if (argChar === ',' && depth === 0) 
                                    {
                                        args.push(current.trim());
                                        current = '';
                                    } 
                                    else 
                                    {
                                        current += argChar;
                                    }
                                }
                                if (current.trim() !== '' || args.length > 0 || str.endsWith(",")) 
                                {
                                    args.push(current.trim());
                                }
                                return args;
                            }
                            const args = splitArgsRobust(argsStr);
                            
                            // --- Perform Substitution on the Macro Body ---
                            let expanded = macroBody;
                            
                            // 1. Replace $@ (all arguments joined as-is)
                            expanded = expanded.replace(/\$@/g, args.join(', '));

                            // replace all $count by the argument count
                            expanded = expanded.replace(/\$count/g, args.length.toString());
                            
                            // 2. Replace numbered arguments $N from back to front
                            for (let idx = args.length - 1; idx >= 0; idx--) 
                            {
                                const regExp = new RegExp(`\\$${idx}\\b`, 'g');
                                expanded = expanded.replace(regExp, args[idx]);
                            }
                            outputAfterExpansion += expanded;
                            i = argsEnd + 1; // Move past the closing ')'
                            continue; // Continue processing the rest of the input
                        }
                    } 
                    else 
                    {
                        console.error("Unterminated macro call for:", callName);
                    }
                }
            }
            // Add current character if it wasn't the start of a recognized macro call
            outputAfterExpansion += input[i];
            i++;
        }
        input = outputAfterExpansion;
    } while (previous !== input); // Repeat until no more expansions occur
    return input;
}

function feraw_compile(input) 
{
    input = expandMacros(input);

    let commands = splitOutsideStrings(input, ';');
    let result = [];
    for (let command of commands) 
    {
        if (command) 
        {
            result.push(tokenize(command));
        }
    }

    let result_string = feraw_labelparser(result);
    return result_string;
}
