#!/usr/bin/env node
let feraw_if_counter = 0;
let feraw_while_counter = 0;
let feraw_for_counter = 0;
let feraw_switch_counter = 0;

function feraw_isolate_labels(code) {
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
            } else if (c === '"' || c === "'") {
                inString = false;
            }
            i++;
        } else {
            if (c === '"' || c === "'") {
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
                i++;
            }
            current += '\n'; // preserve the newline
            continue;
        }
        else if(c === '/' && input[i + 1] === '*') 
        { // multi-line comment
            i += 2; // skip the /*
            while (i < input.length) 
            {
                if (input[i] === '*' && input[i + 1] === '/') 
                {
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
        let needCompaction = false;
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

            if (input[i] === ',') 
            {
                str += String.fromCharCode(24);
                needCompaction = true;
            }
            else if (input[i] === ';')
            {
                str += String.fromCharCode(25); // semicolon
                needCompaction = true;
            }
            else if (input[i] === '\n')
            {
                str += String.fromCharCode(26); // newline
                needCompaction = true;
            }
            else if (input[i] === '\r')
            {
                str += String.fromCharCode(28); // carriage return
                needCompaction = true;
            }
            else if (input[i] === '\t')
            {
                str += String.fromCharCode(29); // tab
                needCompaction = true;
            }
            else if (input[i] === ' ')
            {
                str += String.fromCharCode(30); // space
                needCompaction = true;
            }
            else if (input[i] === ':')
            {
                str += String.fromCharCode(31); // colon
                needCompaction = true;
            }
            else 
            {
                str += input[i];
            }

            i++;
        }

        // if it need to be compacted to a single token we mark it with a comma bcause it will needto be corrected before used
        if (needCompaction || str.includes('\\'))
        {
            tokens.push(',' + str);
        }
        // if it is a simple string without any special characters, we can mark it with a semicolon, this avoid the parser trying to correct the string
        else 
        {
            tokens.push(';' + str); 
        }
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
        if (input[i] === "'") // char as int
        {
            i++; // skip opening '
            let char = input[i++];
            if (char === '\\') 
            {
                char = input[i++];
                if (char === 'n') char = '\n';
                else if (char === 't') char = '\t';
                else if (char === '"') char = '"';
                else if (char === '\'') char = '\'';
                else if (char === '\\') char = '\\';
            }
            i++;
            tokens.push('' + char.charCodeAt(0));
            return;
        }
        
        // if (input[i] === '[') return parseList(depth);
        
        // if (input[i] === '{') return parseBlock(depth);

        // 0x, 0b, 0o, 1e8 etc
        if (input[i] >= '0' && input[i] <= '9' || (input[i] === '-' && (i + 1 < input.length && input[i + 1] >= '0' && input[i + 1] <= '9')) || input[i] == '.')
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
            else if (name == "inline") 
            {
                // lets find the end of the parentesis
                let endParen = findMatching(input, i, '(', ')');
                // now we simply put the content as it is
                if (endParen === -1) throw new Error("parseExpr: missing closing ) for br");
                let content = input.slice(i + 1, endParen);
                tokens.push(content);
                i = endParen + 1; // move the index to after the closing parenthesis
                return;
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
                
                // This handles assignments to simple variables
                // e.g., a = value;  
                // Push in the order: value, variable_name, !, set
                tokens.shift(); // Remove '!' from the start
                tokens.shift(); // Remove 'get' from the start
                tokens = ['!', 'set', ...tokens, ...exprTokens];

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
            tokens.push("!", "set", "@");
            if (name.includes(31) || name.includes(30) || name.includes(29) || name.includes(28) || name.includes(26) || name.includes(25) || name.includes(24))
            {
                // if the name has any special character, we need to compact it
                tokens.push("," + name);
            }
            else 
            {
                tokens.push(";" + name);
            }
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

function feraw_expand_macros(input) 
{
    const macroMap = new Map();

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
                    if (i < input.length && input[i] === '{') 
                    {
                        let bodyStart = i + 1;
                        let bodyEnd = findMatching(input, i, '{', '}'); // Find matching ')'
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

                            
                            let expanded = macroBody;
                            // 1. Replace $@ (all arguments joined as-is)
                            expanded = expanded.replace(/\$all/g, args.join(', '));
                            
                            // 2. replace all $count by the argument count
                            expanded = expanded.replace(/\$count/g, args.length.toString());

                            // 3. replace all $macro_name by the macro name
                            //expanded = expanded.replace(/\$count/g, args.length.toString());
                            
                            // 4. Replace numbered arguments $N from back to front
                            for (let idx = args.length - 1; idx >= 0; idx--) 
                            {
                                const regExp = new RegExp(`\\$${idx}\\b`, 'g');
                                expanded = expanded.replace(regExp, args[idx]);
                            }
                            
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

function feraw_expand_ifs(input) {
    let i = 0;
    let out = '';
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < input.length) {
        let c = input[i];

        // Handle string literals
        if (escape) {
            out += c;
            escape = false;
            i++;
            continue;
        }
        if (c === '\\') {
            out += c;
            escape = true;
            i++;
            continue;
        }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true;
            else inBackticks = true;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes && c === '"') {
            inDoubleQuotes = false;
            out += c;
            i++;
            continue;
        }
        if (inBackticks && c === '`') {
            inBackticks = false;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes || inBackticks) {
            out += c;
            i++;
            continue;
        }

        // Not inside a string, process if
        if (/^if\s*\(/.test(input.slice(i))) {
            let id = feraw_if_counter++;

            i += 2;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'if';
                continue;
            }

            let condStart = i;
            let condEnd = findMatching(input, i, '(', ')');
            let cond = input.slice(condStart + 1, condEnd);
            i = condEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += `if(${cond})`;
                continue;
            }

            let ifBlockEnd = findMatching(input, i, '{', '}');
            let ifBlock = input.slice(i + 1, ifBlockEnd);
            i = ifBlockEnd + 1;
            while (/\s/.test(input[i])) i++;

            let chain = [{ cond, block: ifBlock }];
            let elseBlock = '';

            while (/^else\b/.test(input.slice(i))) {
                i += 4;
                while (/\s/.test(input[i])) i++;
                if (/^if\s*\(/.test(input.slice(i))) {
                    i += 2;
                    while (/\s/.test(input[i])) i++;
                    if (input[i] !== '(') break;
                    let condStart = i;
                    let condEnd = findMatching(input, i, '(', ')');
                    let cond = input.slice(condStart + 1, condEnd);
                    i = condEnd + 1;
                    while (/\s/.test(input[i])) i++;
                    if (input[i] !== '{') break;
                    let blockEnd = findMatching(input, i, '{', '}');
                    let block = input.slice(i + 1, blockEnd);
                    i = blockEnd + 1;
                    chain.push({ cond, block });
                } else if (input[i] === '{') {
                    let elseEnd = findMatching(input, i, '{', '}');
                    elseBlock = input.slice(i + 1, elseEnd);
                    i = elseEnd + 1;
                    break;
                } else {
                    break;
                }
                while (/\s/.test(input[i])) i++;
            }

            for (let j = 0; j < chain.length; j++) {
                chain[j].block = feraw_expand_all(chain[j].block);
            }
            if (elseBlock) {
                elseBlock = feraw_expand_all(elseBlock);
            }

            let trueLabels = chain.map((_, idx) => `if${id}_true_${idx}`);
            let afterLabel = `if${id}_after`;

            out += `?(${chain[0].cond}, ${trueLabels[0]});\n`;
            if (elseBlock) {
                out += elseBlock + '\n';
                out += `?(1, ${afterLabel});\n`;
            } else {
                out += `?(1, ${afterLabel});\n`;
            }
            for (let j = 0; j < chain.length; j++) {
                out += `${trueLabels[j]}:\n`;
                out += chain[j].block + '\n';
                if (j + 1 < chain.length) {
                    out += `?(${chain[j + 1].cond}, ${trueLabels[j + 1]});\n`;
                    out += `?(1, ${afterLabel});\n`;
                }
            }
            out += `${afterLabel}:\n`;
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_whiles(input) {
    let i = 0;
    let out = '';
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < input.length) {
        let c = input[i];

        // Handle string literals
        if (escape) {
            out += c;
            escape = false;
            i++;
            continue;
        }
        if (c === '\\') {
            out += c;
            escape = true;
            i++;
            continue;
        }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true;
            else inBackticks = true;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes && c === '"') {
            inDoubleQuotes = false;
            out += c;
            i++;
            continue;
        }
        if (inBackticks && c === '`') {
            inBackticks = false;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes || inBackticks) {
            out += c;
            i++;
            continue;
        }

        // Not inside a string, process while
        if (/^while\s*\(/.test(input.slice(i))) {
            let id = feraw_while_counter++;
            i += 5;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'while';
                continue;
            }
            let condStart = i;
            let condEnd = findMatching(input, i, '(', ')');
            let cond = input.slice(condStart + 1, condEnd);
            i = condEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += `while(${cond})`;
                continue;
            }
            let whileBlockEnd = findMatching(input, i, '{', '}');
            let whileBlock = input.slice(i + 1, whileBlockEnd);
            i = whileBlockEnd + 1;
            while (/\s/.test(input[i])) i++;
            whileBlock = feraw_expand_all(whileBlock);

            let whileTrueLabel = `while${id}_true`;
            let whileAfterLabel = `while${id}_after`;
            let whileStartLabel = `while${id}_start`;

            out += `${whileStartLabel}:\n`;
            out += `?(${cond}, ${whileTrueLabel});\n`;
            out += `?(1, ${whileAfterLabel});\n`;
            out += `${whileTrueLabel}:\n`;
            out += whileBlock + '\n';
            out += `?(1, ${whileStartLabel});\n`;
            out += `${whileAfterLabel}:\n`;
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_fors(input) {
    let i = 0;
    let out = '';
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < input.length) {
        let c = input[i];

        // Handle string literals
        if (escape) {
            out += c;
            escape = false;
            i++;
            continue;
        }
        if (c === '\\') {
            out += c;
            escape = true;
            i++;
            continue;
        }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true;
            else inBackticks = true;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes && c === '"') {
            inDoubleQuotes = false;
            out += c;
            i++;
            continue;
        }
        if (inBackticks && c === '`') {
            inBackticks = false;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes || inBackticks) {
            out += c;
            i++;
            continue;
        }

        // Not inside a string, process for
        if (/^for\s*\(/.test(input.slice(i))) {
            let id = feraw_for_counter++;
            i += 3;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'for';
                continue;
            }
            let headerStart = i;
            let headerEnd = findMatching(input, i, '(', ')');
            let header = input.slice(headerStart + 1, headerEnd);
            i = headerEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += `for(${header})`;
                continue;
            }
            let forBlockEnd = findMatching(input, i, '{', '}');
            let forBlock = input.slice(i + 1, forBlockEnd);
            i = forBlockEnd + 1;
            while (/\s/.test(input[i])) i++;

            let [init, cond, iter] = header.split(';').map(s => s.trim());
            if (!cond) cond = '1';

            forBlock = feraw_expand_all(forBlock);

            let forStartLabel = `for${id}_start`;
            let forTrueLabel = `for${id}_true`;
            let forAfterLabel = `for${id}_after`;

            out += init ? `${init};\n` : '';
            out += `${forStartLabel}:\n`;
            out += `?(${cond}, ${forTrueLabel});\n`;
            out += `?(1, ${forAfterLabel});\n`;
            out += `${forTrueLabel}:\n`;
            out += forBlock + '\n';
            out += iter ? `${iter};\n` : '';
            out += `?(1, ${forStartLabel});\n`;
            out += `${forAfterLabel}:\n`;
            continue;
        }

        out += input[i++];
    }
    return out;
}

function feraw_expand_brackets(str) 
{
    let out = '';
    let i = 0;
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < str.length) 
    {
        let c = str[i];

        // Handle string literals
        if (escape) 
        {
            out += c;
            escape = false;
            i++;
            continue;
        }

        if (c === '\\') 
        {
            out += c;
            escape = true;
            i++;
            continue;
        }

        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true;
            else inBackticks = true;
            out += c;
            i++;
            continue;
        }

        if (inDoubleQuotes && c === '"') 
        {
            inDoubleQuotes = false;
            out += c;
            i++;
            continue;
        }

        if (inBackticks && c === '`') 
        {
            inBackticks = false;
            out += c;
            i++;
            continue;
        }

        if (inDoubleQuotes || inBackticks) 
        {
            out += c;
            i++;
            continue;
        }

        // Not inside a string, process brackets
        let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
        if (nameMatch) {
            let base = nameMatch[1];
            i += base.length;

            let indexes = [];
            while (i < str.length && str[i] === '[') {
                let end = findMatching(str, i, '[', ']');
                if (end === -1) break;
                let inner = str.slice(i + 1, end);
                indexes.push(inner);
                i = end + 1;
            }

            if (indexes.length > 0) {
                // olhar adiante até o próximo ;
                let lookaheadEnd = str.indexOf(';', i);
                if (lookaheadEnd === -1) lookaheadEnd = str.length;
                let rightSide = str.slice(i, lookaheadEnd);

                // remover espaços do início
                let trimmedRight = rightSide.trimStart();
                if (trimmedRight.startsWith('=')) {
                    // tem atribuição: a[b][c] = ...
                    let valueExpr = trimmedRight.slice(1).trim(); // remove '='
                    // processa valor recursivamente pra pegar gets internos
                    valueExpr = feraw_expand_brackets(valueExpr);

                    if (indexes.length === 1) {
                        // caso simples: a[b] = X
                        out += `set(${base}, ${indexes[0]}, ${valueExpr})`;
                    } else {
                        // último índice vira chave final, os anteriores viram get encadeado
                        let objExpr = base;
                        for (let j = 0; j < indexes.length - 1; j++) {
                            objExpr = `get(${objExpr}, ${indexes[j]})`;
                        }
                        let lastKey = indexes[indexes.length - 1];
                        out += `set(${objExpr}, ${lastKey}, ${valueExpr})`;
                    }
                    i = lookaheadEnd; // pular até ;
                    continue;
                } else {
                    // sem atribuição → só get encadeado
                    let expr = base;
                    for (let idx of indexes) {
                        expr = `get(${expr}, ${idx})`;
                    }
                    out += expr;
                    continue;
                }
            } else {
                out += base;
                continue;
            }
        }
        out += str[i++];
    }

    return out;
}

function feraw_expand_inline_br(input)
{
    let i = 0;
    let out = '';

    while (i < input.length) {
        if (/^br\s*\{/.test(input.slice(i))) 
        {
            i += 2; // skip "br"

            while (/\s/.test(input[i])) i++;

            if (input[i] !== '{') 
            {
                out += 'br';
                continue;
            }

            let argsStart = i;
            let argsEnd = findMatching(input, i, '{', '}');
            let args = input.slice(argsStart + 1, argsEnd);

            out += `inline(${args})`;
            i = argsEnd + 1;
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_dots(str) 
{
    let out = '';
    let i = 0;
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < str.length) {
        let c = str[i];

        // Handle string literals
        if (escape) {
            out += c;
            escape = false;
            i++;
            continue;
        }
        if (c === '\\') {
            out += c;
            escape = true;
            i++;
            continue;
        }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true;
            else inBackticks = true;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes && c === '"') {
            inDoubleQuotes = false;
            out += c;
            i++;
            continue;
        }
        if (inBackticks && c === '`') {
            inBackticks = false;
            out += c;
            i++;
            continue;
        }
        if (inDoubleQuotes || inBackticks) {
            out += c;
            i++;
            continue;
        }

        // captura identificador inicial
        let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
        if (nameMatch) {
            let base = nameMatch[1];
            i += base.length;

            let props = [];
            while (i < str.length && str[i] === '.') {
                i++; // pula o "."
                let propMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
                if (!propMatch) break;
                props.push(propMatch[1]);
                i += propMatch[1].length;
            }

            if (props.length > 0) {
                // olhar adiante até o próximo ';'
                let lookaheadEnd = str.indexOf(';', i);
                if (lookaheadEnd === -1) lookaheadEnd = str.length;
                let rightSide = str.slice(i, lookaheadEnd);

                let trimmedRight = rightSide.trimStart();
                if (trimmedRight.startsWith('=')) {
                    // atribuição
                    let valueExpr = trimmedRight.slice(1).trim(); // remove '='
                    valueExpr = feraw_expand_dots(valueExpr); // processa recursivamente

                    if (props.length === 1) {
                        // foo.bar = X
                        out += `set(${base}, "${props[0]}", ${valueExpr})`;
                    } else {
                        // foo.bar.baz = X
                        let objExpr = base;
                        for (let j = 0; j < props.length - 1; j++) {
                            objExpr = `get(${objExpr}, "${props[j]}")`;
                        }
                        let lastKey = props[props.length - 1];
                        out += `set(${objExpr}, "${lastKey}", ${valueExpr})`;
                    }
                    i = lookaheadEnd; // pular até ;
                    continue;
                } else {
                    // só acesso → get encadeado
                    let expr = base;
                    for (let p of props) {
                        expr = `get(${expr}, "${p}")`;
                    }
                    out += expr;
                    continue;
                }
            } else {
                out += base;
                continue;
            }
        }
        out += str[i++];
    }

    return out;
}

function feraw_expand_macro_calls(code) {
    // Helper: find matching close char ignoring "strings", `backticks`, and 'single quotes'
    function findMatchingWithBT(s, start, openChar, closeChar) {
        let depth = 1;
        let inDouble = false;
        let inBacktick = false;
        let inSingle = false;
        let escape = false;
        for (let i = start + 1; i < s.length; i++) {
            const ch = s[i];
            if (escape) {
                escape = false;
                continue;
            }
            if (inDouble) {
                if (ch === '\\') { escape = true; continue; }
                if (ch === '"') { inDouble = false; continue; }
                continue;
            }
            if (inBacktick) {
                if (ch === '\\') { escape = true; continue; }
                if (ch === '`') { inBacktick = false; continue; }
                continue;
            }
            if (inSingle) {
                if (ch === '\\') { escape = true; continue; }
                if (ch === "'") { inSingle = false; continue; }
                continue;
            }

            if (ch === '"') { inDouble = true; continue; }
            if (ch === '`') { inBacktick = true; continue; }
            if (ch === "'") { inSingle = true; continue; }

            if (ch === openChar) depth++;
            else if (ch === closeChar) {
                depth--;
                if (depth === 0) return i;
            }
        }
        return -1;
    }

    // Pass 1: collect macro names, but never touch content inside "..." or `...`
    const macros = new Set();
    (function collectMacros() {
        let i = 0;
        let inDouble = false, inBacktick = false, inSingle = false, escape = false;
        while (i < code.length) {
            const ch = code[i];
            if (escape) { escape = false; i++; continue; }
            if (inDouble) {
                if (ch === '\\') { escape = true; i++; continue; }
                if (ch === '"') { inDouble = false; i++; continue; }
                i++; continue;
            }
            if (inBacktick) {
                if (ch === '\\') { escape = true; i++; continue; }
                if (ch === '`') { inBacktick = false; i++; continue; }
                i++; continue;
            }
            if (inSingle) {
                if (ch === '\\') { escape = true; i++; continue; }
                if (ch === "'") { inSingle = false; i++; continue; }
                i++; continue;
            }

            if (ch === '"') { inDouble = true; i++; continue; }
            if (ch === '`') { inBacktick = true; i++; continue; }
            if (ch === "'") { inSingle = true; i++; continue; }

            // Try to match: <name> = macro { ... };
            const nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(code.slice(i));
            if (!nameMatch) { i++; continue; }
            const name = nameMatch[1];
            let p = i + name.length;

            // skip whitespace
            while (p < code.length && /\s/.test(code[p])) p++;
            if (code[p] !== '=') { i++; continue; }
            p++;
            while (p < code.length && /\s/.test(code[p])) p++;
            if (code.slice(p, p + 5) !== 'macro') { i++; continue; }
            p += 5;
            while (p < code.length && /\s/.test(code[p])) p++;
            if (code[p] !== '{') { i++; continue; }

            const bodyEnd = findMatchingWithBT(code, p, '{', '}');
            if (bodyEnd === -1) { i++; continue; }

            macros.add(name);

            // jump over definition; consume optional spaces and semicolon
            i = bodyEnd + 1;
            while (i < code.length && /\s/.test(code[i])) i++;
            if (code[i] === ';') i++;
        }
    })();

    if (macros.size === 0) return code;

    // Pass 2: rewrite "lhs = MacroName(...);" into "MacroName(...); lhs =;"
    let out = '';
    let i = 0;
    let inDouble = false, inBacktick = false, inSingle = false, escape = false;

    while (i < code.length) {
        const ch = code[i];

        // Handle string contexts to avoid touching their content
        if (escape) { out += ch; escape = false; i++; continue; }
        if (inDouble) {
            out += ch;
            if (ch === '\\') escape = true;
            else if (ch === '"') inDouble = false;
            i++; continue;
        }
        if (inBacktick) {
            out += ch;
            if (ch === '\\') escape = true;
            else if (ch === '`') inBacktick = false;
            i++; continue;
        }
        if (inSingle) {
            out += ch;
            if (ch === '\\') escape = true;
            else if (ch === "'") inSingle = false;
            i++; continue;
        }

        if (ch === '"') { out += ch; inDouble = true; i++; continue; }
        if (ch === '`') { out += ch; inBacktick = true; i++; continue; }
        if (ch === "'") { out += ch; inSingle = true; i++; continue; }

        // Try to detect: lhs = MacroName(args);
        const lhsMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(code.slice(i));
        if (!lhsMatch) { out += ch; i++; continue; }

        const lhs = lhsMatch[1];
        let p = i + lhs.length;

        // save fallback output if pattern fails
        const fallback = () => { out += code[i]; i++; };

        // skip whitespace
        while (p < code.length && /\s/.test(code[p])) p++;
        if (p >= code.length || code[p] !== '=') { fallback(); continue; }
        p++;
        while (p < code.length && /\s/.test(code[p])) p++;
        const macroNameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(code.slice(p));
        if (!macroNameMatch) { fallback(); continue; }
        const macroName = macroNameMatch[1];
        if (!macros.has(macroName)) { fallback(); continue; }
        p += macroName.length;
        while (p < code.length && /\s/.test(code[p])) p++;
        if (p >= code.length || code[p] !== '(') { fallback(); continue; }

        const close = findMatchingWithBT(code, p, '(', ')');
        if (close === -1) { fallback(); continue; }

        let k = close + 1;
        while (k < code.length && /\s/.test(code[k])) k++;
        if (k >= code.length || code[k] !== ';') { fallback(); continue; }

        // Success: perform rewrite
        const args = code.slice(p, close + 1); // includes parentheses
        out += `${macroName}${args}; ${lhs} =;`;
        i = k + 1; // move past semicolon
    }

    return out;
}

function feraw_expand_all(input)
{
    input = feraw_expand_macro_calls(input);
    input = feraw_isolate_labels(input);
    input = feraw_expand_brackets(input);
    input = feraw_expand_dots(input);
    input = feraw_expand_macros(input);
    input = feraw_expand_ifs(input);
    input = feraw_expand_whiles(input);
    input = feraw_expand_fors(input);
    input = feraw_expand_inline_br(input);
    return input;
}

function feraw_compile(input) 
{
    input = feraw_expand_all(input);
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
    result_string = result_string.replaceAll("\n\n", "\n"); // Remove double newlines
    if (result_string.startsWith("\n")) 
    {
        result_string = result_string.slice(1); // Remove leading newline
    }
    if (result_string.endsWith("\n")) 
    {
        result_string = result_string.slice(0, -1); // Remove trailing newline
    }
    return result_string;
}

// only if under node.js
if (process)
{
    const fs = require('fs');
    const path = require('path');

    function expandIncludes(filePath, baseDir = null) {
        if (!baseDir) baseDir = path.dirname(filePath);
        
        const content = [];
        try {
            const data = fs.readFileSync(filePath, 'utf8');
            const lines = data.split(/\r?\n/);
            
            for (const line of lines) {
                const match = line.match(/^\s*include\(\"([^\"]+)\"\);\s*$/);
                if (match) {
                    const incFile = match[1];
                    const incPath = path.join(baseDir, incFile);
                    const incDir = path.dirname(incPath);
                    
                    try {
                        if (fs.existsSync(incPath) && fs.statSync(incPath).isFile()) {
                            content.push(`/* start include: ${incFile} */`);
                            content.push(...expandIncludes(incPath, incDir));
                            content.push(`/* end include: ${incFile} */`);
                            content.push('');
                        } else {
                            content.push(`/* missing include: ${incFile} */`);
                        }
                    } catch (err) {
                        content.push(`/* error including ${incFile}: ${err.message} */`);
                    }
                } else {
                    content.push(line);
                }
            }
        } catch (err) {
            content.push(`/* error processing ${filePath}: ${err.message} */`);
        }
        
        return content;
    }

    function processContent(content) {
        const ccBlocks = [];
        const functions = [];
        const otherLines = [];
        let insideCC = false;
        let depth = 0;
        let ccBuffer = [];

        for (const line of content) {
            // Detect function declarations
            const funcMatch = line.match(/function\s*\(\s*([a-zA-Z0-9_]+)\s*\)/);
            if (funcMatch) {
                const funcName = funcMatch[1];
                const cleanName = funcName.startsWith('feraw_') 
                    ? funcName.slice(6) 
                    : funcName;
                functions.push([funcName, cleanName]);
            }

            if (!insideCC) {
                if (/^\s*cc\s*\{/.test(line)) {
                    insideCC = true;
                    depth = 1;
                    const cleaned = line.replace(/^\s*cc\s*\{/, '');
                    if (cleaned.trim()) ccBuffer.push(cleaned);
                } else if (/^\s*cc\s*$/.test(line)) {
                    insideCC = true;
                    depth = 1;
                } else {
                    otherLines.push(line);
                }
            } else {
                for (const char of line) {
                    if (char === '{') depth++;
                    if (char === '}') depth--;
                    
                    if (depth === 0) {
                        insideCC = false;
                        break;
                    }
                }
                
                if (!insideCC) {
                    const endIndex = line.indexOf('}') + 1;
                    if (endIndex > 0) {
                        const before = line.substring(0, endIndex - 1);
                        if (before.trim()) ccBuffer.push(before);
                        
                        const after = line.substring(endIndex);
                        if (after.trim()) otherLines.push(after);
                    } else if (line.trim()) {
                        ccBuffer.push(line);
                    }
                    
                    ccBlocks.push(...ccBuffer);
                    ccBuffer = [];
                } else if (line.trim()) {
                    ccBuffer.push(line);
                }
            }
        }
        
        return { ccBlocks, functions, otherLines };
    }

    function generateOutput(outputPath, { ccBlocks, functions, otherLines }) {
        let output = `#include "bruter.h"\n`;
        output += `#include <stdlib.h>\n\n`;
        
        if (ccBlocks.length > 0) {
            output += `/* BEGIN cc blocks */\n`;
            output += ccBlocks.join('\n') + '\n';
            output += `/* END cc blocks */\n\n`;
        }
        
        output += `int main(int argc, char *argv[])\n{\n`;
        output += `    BruterList *context = bruter_new(8, true, true);\n\n`;
        
        if (functions.length > 0) {
            output += `    /* BEGIN function registrations */\n`;
            for (const [funcName, cleanName] of functions) {
                output += `    bruter_push_pointer(context, ${funcName}, "${cleanName}", BRUTER_TYPE_FUNCTION);\n`;
            }
            output += `    /* END function registrations */\n\n`;
        }
        
        // lets join the other lines into a single string
        // apply feraw_compile() to it, then split it into lines again
        // then prepare it for embedding
        let joinedCode = otherLines.join('\n');
        joinedCode = feraw_compile(joinedCode);
        otherLines = joinedCode.split(/\r?\n/).filter(line => line.trim());

        output += `    const char *embedded_code =\n`;
        for (const line of otherLines) {
            if (!line.trim()) continue;
            const escaped = line
                .replace(/\\/g, '\\\\')
                .replace(/"/g, '\\"');
            output += `    "${escaped}\\n"\n`;
        }
        output += `    ;\n\n`;
        
        output += `    BruterList *result = bruter_parse(context, embedded_code);\n`;
        output += `    bruter_free(result);\n`;
        output += `    bruter_free(context);\n`;
        output += `    return EXIT_SUCCESS;\n}\n`;
        
        fs.writeFileSync(outputPath, output);
    }

    // Main execution
    if (process.argv.length < 4) {
        console.error(`Usage: ${path.basename(process.argv[1])} <input.feraw> <output.c>`);
        process.exit(1);
    }

    const inputFile = path.resolve(process.argv[2]);
    const outputFile = path.resolve(process.argv[3]);

    try {
        // Step 1: Expand includes
        const expandedContent = expandIncludes(inputFile);
        
        // Step 2: Process content
        const processed = processContent(expandedContent);
        
        // Step 3: Generate output
        generateOutput(outputFile, processed);
        
        console.log(`Successfully generated: ${outputFile}`);
    } catch (err) {
        console.error(`Error: ${err.message}`);
        process.exit(1);
    }
}