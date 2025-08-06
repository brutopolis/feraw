function replaceIdentifiersOutsideStrings(code) {
    let result = '';
    let inString = false;
    let escape = false;
    let i = 0;

    while (i < code.length) {
        const c = code[i];

        if (inString) {
            result += c;
            if (escape) {
                escape = false;
            } else if (c === '\\') {
                escape = true;
            } else if (c === '"') {
                inString = false;
            }
            i++;
        } else {
            if (c === '"') {
                inString = true;
                result += c;
                i++;
            } else {
                const match = code.slice(i).match(/^([a-zA-Z_]\w*):/);
                if (match) {
                    result += match[0] + ';'; 
                    i += match[0].length;
                } else {
                    result += c;
                    i++;
                }
            }
        }
    }

    return result;
}

function splitOutsideStrings(input, char = ';') 
{
    let parts = [];
    let current = '';
    let inDoubleQuotes = false;
    let inSingleQuotes = false;
    let inBackticks = false;
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
            inDoubleQuotes = !inDoubleQuotes;
            current += c;
            continue;
        }

        if (c === "'") 
        {            
            inSingleQuotes = !inSingleQuotes;
            current += c;
            continue;
        }

        if (c === '`') 
        {            
            inBackticks = !inBackticks;
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

        if (c === char && !inDoubleQuotes && !inSingleQuotes) 
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
            } 
            else break;
        }
    }

    function parseString() 
    {
        let str = '';
        i++; // skip opening "

        if (!input.includes('='))
        {
            isAssignment = true; // if there is no =, we assume this is a string assignment
        }

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

        // check if is a assignment, if not we assume this is a string literal
        tokens.push('#' + str);
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
        // if (input[i] === '[') return parseList(depth);
        
        // in near future we will use this for something, block name is ilustrative only
        // if (input[i] === '{') return parseBlock(depth);

        // 0x, 0b, 0o, 1e8 etc
        if (input[i] >= '0' && input[i] <= '9' || input[i] === '-' || input[i] === '.' )
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
                    while (true) 
                    {
                        skipWhitespace();
                        if (i >= input.length) throw new Error("Function call not closed with )");
                        if (input[i] === ')') 
                        {
                            i++; // skip ')'
                            break;
                        }
                        parseExpr(depth + 1); // Parse the argument expression
                        // Take the tokens generated for the argument
                        argTokens.push(...tokens.splice(tokens.length - 1)); 
                        skipWhitespace();
                        if (input[i] === ',') i++; // skip ','
                    }

                    exprTokens = ['!', ...exprTokens, ...argTokens]; 
                    continue; 
                }

                if (input[i] === '[') 
                {
                    let start = i;
                    i++; // skip '['
                    skipWhitespace();
                    // Parse the expression inside the brackets (the index)
                    parseExpr(depth + 1);
                    skipWhitespace();
                    // Ensure the closing bracket exists
                    if (input[i] !== ']') throw new Error("parseExpr: missing closing ]");
                    i++; // skip ']'

                    // lets check if we are under a funcion call
                    let discount = 0;
                    for (let j = start - 1; j >= 0; j--) 
                    {
                        if (input[j] === '(')
                        {
                            discount--;
                        }
                        else if (input[j] === ')')
                        {
                            discount++;
                        }
                    }
                    let tokensDiscounted = [];
                    for (let j = 0; j < -discount; j++) 
                    {
                        tokensDiscounted.push(tokens.shift());
                        tokensDiscounted.push(tokens.shift());
                    }
                    tokens = [...tokensDiscounted, '!', 'get', ...exprTokens, ...tokens];
                    exprTokens = [];
                    continue;
                }
                // --- Break Condition ---
                // If the next character is neither '(' nor '[', the chain ends.
                break; 
            }
            // --- END WHILE LOOP FOR CHAIN PROCESSING ---

            skipWhitespace();
            
            // --- Handle Assignment: expr = value ---
            if (input[i] === '=') 
            {
                i++; // skip '='
                skipWhitespace();
                // Parse the Right-Hand Side (RHS) of the assignment
                parseExpr(depth + 1); 
                
                if (exprTokens.length >= 4 && exprTokens[0] === '!' && exprTokens[1] === 'get')
                {
                    // It's a list assignment like target[index] = value or target[index1][index2]... = value
                    
                    exprTokens.shift(); // Remove '!' from the start
                    exprTokens.shift(); // Remove 'get' from the start
                    // Extract the final index (the index for the last 'get' operation)
                    let finalIndexToken = exprTokens.pop(); // e.g., '0' or '1'
                    let objname = exprTokens.shift(); // e.g., 'obj' or 'obj[0]'
                    tokens.unshift('!', 'set', objname, ...exprTokens,finalIndexToken);                    
                } 
                else 
                {
                    // This handles assignments to simple variables
                    // e.g., a = value;  
                    // Push in the order: value, variable_name, !, set
                    tokens.shift(); // Remove '!' from the start
                    tokens.shift(); // Remove 'get' from the start
                    tokens = ['!', 'set', ...tokens, ...exprTokens];
                }
                return; // Crucial: Stop parsing this expression after handling assignment
            }
            
            // --- Not an Assignment ---
            // Push the accumulated expression tokens (representing the access chain)
            tokens.push(...exprTokens);
        }
    } // End of parseExpr function


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

function feraw_expand_macros(input) 
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

    // --- Step 1: Find and Store Macro Definitions ---
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
                // Consume single-line comment
                while (i < input.length && input[i] !== '\n') 
                {
                    outputWithoutDefs += input[i];
                    i++;
                }
                if (i < input.length) 
                { // Add the newline if it exists
                    outputWithoutDefs += input[i];
                    i++;
                }
                continue;
            } 
            else if (input[i + 1] === '*') 
            {
                // Consume multi-line comment
                outputWithoutDefs += input[i]; i++; // Add /
                outputWithoutDefs += input[i]; i++; // Add *
                while (i < input.length) 
                {
                    if (input[i] === '*' && i + 1 < input.length && input[i + 1] === '/') 
                    {
                        outputWithoutDefs += input[i]; i++; // Add *
                        outputWithoutDefs += input[i]; i++; // Add /
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
                            i = potentialStart; // Reset to try parsing normally
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

    // --- Step 2: Expand Macro Calls (Corrected) ---
    // Work on the input without definitions
    input = outputWithoutDefs;
    let previous;
    do 
    {
        previous = input;
        let outputAfterExpansion = '';
        i = 0;
        let inString = false; // Track if inside a string literal
        let stringChar = '';  // Track the quote character for the current string

        // --- Main Expansion Loop ---
        while (i < input.length) 
        {
            let char = input[i];

            // --- String Literal Handling ---
            // Consistently handle strings to prevent misinterpreting comment chars inside them
            if (!inString && (char === '"' || char === "'")) 
            {
                inString = true;
                stringChar = char;
                outputAfterExpansion += char;
                i++;
                continue;
            } 
            else if (inString && char === stringChar) 
            {
                // Check for escaped quote?
                if (i > 0 && input[i-1] === '\\') 
                {
                    // The quote is escaped, treat it as a normal character
                    // The backslash was already added in the 'else' part below or previous iteration
                    // Just add the quote and continue
                    outputAfterExpansion += char;
                    i++;
                    continue;
                }
                inString = false;
                stringChar = '';
                outputAfterExpansion += char;
                i++;
                continue;
            }
            if (inString) 
            {
                outputAfterExpansion += char;
                i++;
                continue;
            }

            // --- Comment Handling ---
            // If not in a string, check for comment start
            if (char === '/' && i + 1 < input.length) 
            {
                if (input[i + 1] === '/') 
                {
                    // Copy the entire single-line comment
                    outputAfterExpansion += char; i++; // Add /
                    outputAfterExpansion += input[i]; i++; // Add /
                    while (i < input.length && input[i] !== '\n') 
                    {
                        outputAfterExpansion += input[i];
                        i++;
                    }
                    if (i < input.length) 
                    { // Add the newline if it exists
                        outputAfterExpansion += input[i];
                        i++;
                    }
                    continue; // Process the next character after the comment
                } 
                else if (input[i + 1] === '*') 
                {
                    // Copy the entire multi-line comment
                    outputAfterExpansion += char; i++; // Add /
                    outputAfterExpansion += input[i]; i++; // Add *
                    while (i < input.length) 
                    {
                        outputAfterExpansion += input[i];
                        if (input[i] === '*' && i + 1 < input.length && input[i + 1] === '/') 
                        {
                            outputAfterExpansion += input[i + 1]; // Add /
                            i += 2; // Move past */
                            break;
                        }
                        i++;
                    }
                    continue; // Process the next character after the comment
                }
            }

            // --- Macro Call Expansion ---
            // If we reach here, we are not in a string or comment.
            // Attempt to Match a Macro Call: identifier '('
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
                            // 1. Replace $@ (all arguments joined as-is) - Use the version from Pasted_Text_1754372135154.txt
                            expanded = expanded.replace(/\$all/g, args.join(', '));
                            // replace all $count by the argument count - Use the version from Pasted_Text_1754372135154.txt
                            expanded = expanded.replace(/\$count/g, args.length.toString());
                            // 2. Replace numbered arguments $N from back to front
                            for (let idx = args.length - 1; idx >= 0; idx--) 
                            {
                                const regExp = new RegExp(`\\$${idx}\\b`, 'g');
                                expanded = expanded.replace(regExp, args[idx]);
                            }
                            // Use $@ replacement from Pasted_Text_1754204706745.txt
                            expanded = expanded.replace(/\$@/g, args.join(', '));

                            outputAfterExpansion += expanded;
                            i = argsEnd + 1; // Move past the closing ')'
                            continue; // Continue processing the rest of the input
                        }
                        // If macro not found, fall through to add the characters normally
                    }
                    else 
                    {
                        console.error("Unterminated macro call for:", callName);
                        // Fall through to add characters normally or handle error
                    }
                }
                // If it's not a '(' or the call is malformed, fall through
            }
            // Add current character if it wasn't the start of a string, comment, or recognized macro call
            outputAfterExpansion += input[i];
            i++;
        }
        input = outputAfterExpansion;
    } while (previous !== input); // Repeat until no more expansions occur

    return input;
}

function analyzeCode(code) {
    const lines = code.split('\n');
    const declared = new Set();
    const errors = [];

    const isAssignment = /^\s*([a-zA-Z_]\w*)\s*=/;
    const validFuncs = new Set(['list', 'macro', 'string', 'push', 'new', 'free', 'print']);
    
    for (let i = 0; i < lines.length; i++) {
        let line = lines[i].trim();

        // Detect declarations
        let match = line.match(isAssignment);
        if (match) {
            declared.add(match[1]);
        }

        // Remove string literals
        let clean = line.replace(/"[^"]*"/g, '');

        // Detect variable usage
        let tokens = clean.match(/\b[a-zA-Z_]\w*\b/g);
        if (tokens) {
            for (let token of tokens) {
                if (
                    !declared.has(token) &&
                    !validFuncs.has(token) &&
                    token !== 'end' &&
                    isNaN(Number(token)) &&
                    token !== 'Any' && token !== 'Float' && token !== 'Buffer'
                ) 
                {
                    errors.push(`Possível uso de variável não declarada: "${token}" na linha ${i + 1}`);
                }
            }
        }
    }

    return errors;
}

function feraw_analyze(input)
{
    input = feraw_expand_macros(input);
    analyzeCode(input).forEach(error => {
        console.warn(error);
    });
    return input;
}

function feraw_compile(input) 
{
    input = replaceIdentifiersOutsideStrings(input);
    input = feraw_expand_macros(input);

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
