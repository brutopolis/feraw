#!/usr/bin/env node
let feraw_if_counter = 0;
let feraw_while_counter = 0;
let feraw_for_counter = 0;
let feraw_switch_counter = 0;

function splitOutsideStrings(input, char = ';') 
{
    const parts = [];
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
    const tokens = [];
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
        const stringChar = input[i]; // Store the opening quote character
        i++; // skip opening quote
        
        if (!input.includes('='))
        {
            isAssignment = true; // if there is no =, we assume this is a string assignment
        }

        while (i < input.length)
        {
            if (input[i] === stringChar) // Check for matching closing quote
            {
                i++;
                break;
            }

            str += input[i];

            i++;
        }

        // Check if string was properly closed
        if (i >= input.length && input[i-1] !== stringChar) {
            console.warn(`Unterminated string literal starting with ${stringChar}`);
        }

        // replace spaces in strings by \s as requested
        tokens.push(';' + str.replace(/ /g, '\\s'));
    }
    
    function parseBlock(depth = 0)
    {
        // to be used in future, for something i don't know yet
    }

    function parseRawToken() 
    {
        const start = i;
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
        if (input[i] === '`') return parseString(); // Treat backticks like quotes
        if (input[i] === "'") // char as int
        {
            i++; // skip opening '
            if (i >= input.length) {
                console.warn('Unterminated character literal');
                return;
            }
            let char = input[i++];
            if (char === '\\') 
            {
                if (i >= input.length) {
                    console.warn('Incomplete escape sequence');
                    return;
                }
                char = input[i++];
                if (char === 'n') char = '\n';
                else if (char === 't') char = '\t';
                else if (char === '"') char = '"';
                else if (char === '\'') char = '\'';
                else if (char === '\\') char = '\\';
            }
            if (i < input.length && input[i] === "'") i++; // skip closing '
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

        const name = parseRawToken();
        if (!name) {
            // Skip empty tokens instead of throwing
            console.warn('Empty token encountered, skipping');
            return;
        }

        if (["true", "false", "stack", "context", "code"].includes(name))
        {
            switch (name)
            {
                case "true":
                    tokens.push('1');
                    return;
                case "false":
                    tokens.push('0');
                    return;
                case "stack":
                    tokens.push('&');
                    return;
                case "context":
                    tokens.push('@');
                    return;
                case "code":
                    tokens.push('~');
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
    const maxIterations = 10000; // Prevent infinite loops
    while (i < input.length && safety < maxIterations) 
    {
        const startPos = i; // Track position to detect infinite loops
        skipWhitespace();
        if (i >= input.length) break;

        const start = i;
        const name = parseRawToken();
        skipWhitespace();

        if (input[i] === '=') 
        {
            i++;
            skipWhitespace();
            tokens.push("!", "set", "@");
            tokens.push(";" + name);
            parseExpr();
        } 
        else 
        {
            i = start;
            parseExpr();
        }
        
        // Safety check: ensure we're making progress
        if (i === startPos) {
            console.warn(`Parser stuck at position ${i}, advancing`);
            i++; // Force advancement to prevent infinite loop
        }
        
        safety++;
    }
    
    if (safety >= maxIterations) {
        console.warn('Maximum parser iterations reached, stopping to prevent infinite loop');
    }

    return tokens;
}
function feraw_labelparser(original_input) 
{
    // we need this to know exactly where the labels were positioned originally
    let unreversed_input = original_input.map(tokens => tokens.join(' ')).join(' ');
    
    // split by tab only
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

    // Remove all label: from the input, but skip inside strings and comments
    let out = '';
    let i = 0;
    let inDoubleQuotes = false;
    let inSingleQuotes = false;
    let inBackticks = false;
    let inLineComment = false;
    let inBlockComment = false;
    let escape = false;

    while (i < input.length) {
        let c = input[i];

        // Handle escapes in strings
        if (escape) {
            out += c;
            escape = false;
            i++;
            continue;
        }
        if (c === '\\' && (inDoubleQuotes || inSingleQuotes || inBackticks)) {
            out += c;
            escape = true;
            i++;
            continue;
        }

        // Handle entering/exiting strings
        if (!inDoubleQuotes && !inSingleQuotes && !inBackticks && !inLineComment && !inBlockComment) {
            if (c === '"') { inDoubleQuotes = true; out += c; i++; continue; }
            if (c === "'") { inSingleQuotes = true; out += c; i++; continue; }
            if (c === '`') { inBackticks = true; out += c; i++; continue; }
            if (c === '/' && input[i + 1] === '/') { inLineComment = true; out += c; i++; continue; }
            if (c === '/' && input[i + 1] === '*') { inBlockComment = true; out += c; i++; continue; }
        }
        else {
            // Handle exiting strings
            if (inDoubleQuotes && c === '"') { inDoubleQuotes = false; out += c; i++; continue; }
            if (inSingleQuotes && c === "'") { inSingleQuotes = false; out += c; i++; continue; }
            if (inBackticks && c === '`') { inBackticks = false; out += c; i++; continue; }
            if (inLineComment && c === '\n') { inLineComment = false; out += c; i++; continue; }
            if (inBlockComment && c === '*' && input[i + 1] === '/') { inBlockComment = false; out += c + input[i + 1]; i += 2; continue; }
        }

        // If inside string or comment, just copy
        if (inDoubleQuotes || inSingleQuotes || inBackticks || inLineComment || inBlockComment) {
            out += c;
            i++;
            continue;
        }

        // Remove label: outside strings/comments, only if not part of a larger word
        let labelMatch = input.slice(i).match(/^(\w+):/);
        if (labelMatch) {
            // Only remove if not preceded or followed by a word character
            let before = i > 0 ? input[i - 1] : '';
            let after = input[i + labelMatch[0].length] || '';
            if (!/\w/.test(before) && !/\w/.test(after)) {
                i += labelMatch[0].length;
                continue;
            }
        }

        out += c;
        i++;
    }
    input = out;

    // Replace label references, but skip inside strings/comments and only whole words
    for (let label of labels) 
    {
        let out2 = '';
        let i2 = 0;
        let inDoubleQuotes = false;
        let inSingleQuotes = false;
        let inBackticks = false;
        let inLineComment = false;
        let inBlockComment = false;
        let escape = false;
        const labelName = label[0];
        const labelValue = label[1];

        while (i2 < input.length) {
            let c = input[i2];

            // Handle escapes in strings
            if (escape) {
                out2 += c;
                escape = false;
                i2++;
                continue;
            }
            if (c === '\\' && (inDoubleQuotes || inSingleQuotes || inBackticks)) {
                out2 += c;
                escape = true;
                i2++;
                continue;
            }

            // Handle entering/exiting strings/comments
            if (!inDoubleQuotes && !inSingleQuotes && !inBackticks && !inLineComment && !inBlockComment) {
                if (c === '"') { inDoubleQuotes = true; out2 += c; i2++; continue; }
                if (c === "'") { inSingleQuotes = true; out2 += c; i2++; continue; }
                if (c === '`') { inBackticks = true; out2 += c; i2++; continue; }
                if (c === '/' && input[i2 + 1] === '/') { inLineComment = true; out2 += c; i2++; continue; }
                if (c === '/' && input[i2 + 1] === '*') { inBlockComment = true; out2 += c; i2++; continue; }
            }
            else {
                // Handle exiting strings
                if (inDoubleQuotes && c === '"') { inDoubleQuotes = false; out2 += c; i2++; continue; }
                if (inSingleQuotes && c === "'") { inSingleQuotes = false; out2 += c; i2++; continue; }
                if (inBackticks && c === '`') { inBackticks = false; out2 += c; i2++; continue; }
                if (inLineComment && c === '\n') { inLineComment = false; out2 += c; i2++; continue; }
                if (inBlockComment && c === '*' && input[i2 + 1] === '/') { inBlockComment = false; out2 += c + input[i2 + 1]; i2 += 2; continue; }
            }

            // If inside string or comment, just copy
            if (inDoubleQuotes || inSingleQuotes || inBackticks || inLineComment || inBlockComment) {
                out2 += c;
                i2++;
                continue;
            }

            // Only replace if it's a whole word (not part of a larger word)
            if (
                input.slice(i2, i2 + labelName.length) === labelName &&
                (i2 === 0 || !/\w/.test(input[i2 - 1])) &&
                (i2 + labelName.length === input.length || !/\w/.test(input[i2 + labelName.length]))
            ) {
                out2 += `${labelValue}`;
                i2 += labelName.length;
                continue;
            }

            out2 += c;
            i2++;
        }
        input = out2;
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

            ifBlock = feraw_expand_all(ifBlock);

            let trueLabel = `if${id}_true`;
            let afterLabel = `if${id}_after`;

            out += `?(${cond}, ${trueLabel});\n`;
            out += `?(1, ${afterLabel});\n`;
            out += `${trueLabel}:\n`;
            out += ifBlock + '\n';
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

function feraw_expand_props(str) {
    let out = '';
    let i = 0;
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    while (i < str.length) {
        const c = str[i];

        // Handle strings
        if (escape) { out += c; escape = false; i++; continue; }
        if (c === '\\') { out += c; escape = true; i++; continue; }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true; else inBackticks = true;
            out += c; i++; continue;
        }
        if (inDoubleQuotes && c === '"') { inDoubleQuotes = false; out += c; i++; continue; }
        if (inBackticks && c === '`') { inBackticks = false; out += c; i++; continue; }
        if (inDoubleQuotes || inBackticks) { out += c; i++; continue; }

        // Detecta identificador base
        const nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
        if (!nameMatch) { out += str[i++]; continue; }

        const base = nameMatch[1];
        i += base.length;

        // Captura props encadeados (.foo ou [expr])
        const props = [];
        while (i < str.length) {
            if (str[i] === '.') {
                i++;
                const propMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
                if (!propMatch) break;
                props.push({ key: `"${propMatch[1]}"` });
                i += propMatch[1].length;
                continue;
            }
            if (str[i] === '[') {
                const end = findMatching(str, i, '[', ']');
                if (end === -1) {
                    // Malformed bracket access, skip it gracefully
                    console.warn('Malformed bracket access, skipping');
                    out += str[i];
                    i++;
                    break;
                }
                const inner = str.slice(i + 1, end).trim();
                if (/^"(.*?)"$/.test(inner)) {
                    props.push({ key: inner });
                } else {
                    props.push({ key: inner });
                }
                i = end + 1;
                continue;
            }
            break;
        }

        if (props.length > 0) {
            // olha até ; pra ver se é atribuição
            let lookaheadEnd = str.indexOf(';', i);
            if (lookaheadEnd === -1) lookaheadEnd = str.length;
            const rightSide = str.slice(i, lookaheadEnd);
            const trimmedRight = rightSide.trimStart();

            if (trimmedRight.startsWith('=')) {
                // assignment
                let valueExpr = trimmedRight.slice(1).trim();
                valueExpr = feraw_expand_props(valueExpr);

                if (props.length === 1) {
                    const k = props[0].key;
                    if (k === `"type"`) {
                        out += `retype(@, "${base}", ${valueExpr})`;
                    } 
                    else if (k === `"name"`) 
                    {
                        out += `rename(${base}, "${base}", ${valueExpr})`;
                    } else {
                        out += `set(${base}, ${k}, ${valueExpr})`;
                    }
                } 
                else 
                {
                    const lastKey = props[props.length - 1].key;

                    if (lastKey === `"type"`) 
                    {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 2; j++) 
                        {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        out += `retype(${objExpr}, ${props[props.length - 2].key}, ${valueExpr})`;
                    } 
                    else if (lastKey === `"name"`) 
                    {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 2; j++) {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        const prevKey = props[props.length - 2].key;
                        out += `rename(${objExpr}, ${prevKey}, ${valueExpr})`;

                    } else {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 1; j++) {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        out += `set(${objExpr}, ${lastKey}, ${valueExpr})`;
                    }
                }
                i = lookaheadEnd;
                continue;
            } else {
                // ----------- GET MODE -----------
                const lastKey = props[props.length - 1].key;

                if (lastKey === `"name"`) 
                {
                    if (props.length === 1) 
                    {
                        out += `nameof(@, "${base}")`;
                    } 
                    else 
                    {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 2; j++) 
                        {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        const prevKey = props[props.length - 2].key;
                        out += `nameof(${objExpr}, ${prevKey})`;
                    }
                }
                else if (lastKey === `"type"`) 
                {
                    if (props.length === 1) 
                    {
                        out += `typeof(@, "${base}")`;
                    } 
                    else 
                    {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 2; j++) {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        const prevKey = props[props.length - 2].key;
                        out += `typeof(${objExpr}, ${prevKey})`;
                    }
                } else if (lastKey === `"length"`) {
                    if (props.length === 1) {
                        out += `length(${base})`;
                    } else {
                        let objExpr = base;
                        for (let j = 0; j < props.length - 1; j++) {
                            objExpr = `get(${objExpr}, ${props[j].key})`;
                        }
                        out += `length(${objExpr})`;
                    }
                } else {
                    // default: get encadeado
                    let expr = base;
                    for (const p of props) {
                        expr = `get(${expr}, ${p.key})`;
                    }
                    out += expr;
                }

                continue;
            }
        } else {
            out += base;
            continue;
        }
    }

    return out;
}

// --- NEW: Infix math & conditional operators expansion ---
// Transforms infix expressions (a + b * c >= d && e | f) into functional form.
// Added bitwise operators: | ^ & << >> >>> and unary ~
(function(){
    const BIN_PRECEDENCE = {
        '||': 1,
        '&&': 2,
        '|': 3,
        '^': 4,
        '&': 5,
        '==': 6, '!=': 6,
        '<': 7, '<=': 7, '>': 7, '>=': 7,
        '<<': 8, '>>': 8, '>>>': 8,
        '+': 9, '-': 9,
        '*': 10, '/': 10, '%': 10
    };
    const ASSOCIATIVITY = {
        '||':'L','&&':'L','|':'L','^':'L','&':'L','==':'L','!=':'L','<':'L','<=':'L','>':'L','>=':'L','<<':'L','>>':'L','>>>':'L','+':'L','-':'L','*':'L','/':'L','%':'L'
    };
    const OP_FUNC = {
        '+':'add','-':'sub','*':'mul','/':'div','%':'mod',
        '==':'equals','!=':'not_equals','<':'less','<=':'less_equal','>':'greater','>=':'greater_equal',
        '&&':'and','||':'or',
        '|':'bit_or','^':'bit_xor','&':'bit_and','<<':'lshift','>>':'rshift','>>>':'urshift'
    };
    const UNARY_FUNC = { '!':'not', '-':'neg', '~':'bit_not' };

    function tokenizeExpr(expr){
        const tokens = [];
        let i=0; const len=expr.length;
        while(i<len){
            // skip whitespace
            if(/\s/.test(expr[i])){ i++; continue; }
            const c = expr[i];
            // string literals (single, double, backtick) just copy verbatim
            if(c==='"' || c==='\'' || c==='`'){
                let quote=c; let j=i+1; let out=quote; let esc=false;
                for(; j<len; j++){
                    const ch=expr[j];
                    out+=ch;
                    if(esc){ esc=false; continue; }
                    if(ch==='\\'){ esc=true; continue; }
                    if(ch===quote){ j++; break; }
                }
                tokens.push(out); i=j; continue;
            }
            // numbers (including hex, bin, float)
            if(/[0-9]/.test(c) || (c==='.' && /[0-9]/.test(expr[i+1]))){
                let j=i+1;
                while(j<len && /[0-9a-zA-ZxX\.]/.test(expr[j])) j++;
                tokens.push(expr.slice(i,j)); i=j; continue;
            }
            // identifiers
            if(/[A-Za-z_$]/.test(c)){
                let j=i+1; while(j<len && /[A-Za-z0-9_$]/.test(expr[j])) j++;
                tokens.push(expr.slice(i,j)); i=j; continue;
            }
            const three = expr.slice(i,i+3);
            if(['>>>'].includes(three)){ tokens.push(three); i+=3; continue; }
            const two = expr.slice(i,i+2);
            if(['==','!=','<=','>=','&&','||','<<','>>'].includes(two)){ tokens.push(two); i+=2; continue; }
            if(['+','-','*','/','%','<','>','!','(',')','|','^','&','~'].includes(c)) { tokens.push(c); i++; continue; }
            // anything else (comma, dot, brackets) => abort (return original tokens with flag)
            return null; // signal unsupported complexity -> skip transform
        }
        return tokens;
    }

    function toAST(tokens){
        if(!tokens) return null;
        // Shunting Yard producing output queue (as tokens) + operator stack
        const output=[]; const ops=[];
        let prevType = 'START';
        for(let i=0;i<tokens.length;i++){
            const t = tokens[i];
            if(t === '('){ ops.push(t); prevType='OPEN'; continue; }
            if(t === ')'){
                while(ops.length && ops[ops.length-1] !== '('){ output.push(ops.pop()); }
                if(!ops.length) return null; // mismatched
                ops.pop(); // remove '('
                prevType='CLOSE';
                continue;
            }
            if(t in BIN_PRECEDENCE || t==='!' || t==='-' || t==='~'){
                // determine unary '-' or '!'
                let isUnary = false;
                if(t==='!' ) isUnary = true;
                else if(t==='-' && (prevType === 'START' || prevType==='OPEN' || prevType==='OP')) isUnary = true;
                if(isUnary){
                    // represent unary as distinct token e.g. 'u!' or 'u-'
                    const ut = 'u'+t;
                    // treat precedence very high
                    ops.push(ut);
                } else {
                    while(ops.length){
                        const top = ops[ops.length-1];
                        if(top==='(') break;
                        const topIsUnary = top.startsWith('u');
                        const topOp = topIsUnary ? top.slice(1) : top;
                        const pTop = topIsUnary ? 11 : BIN_PRECEDENCE[topOp];
                        const pCur = BIN_PRECEDENCE[t];
                        if( (ASSOCIATIVITY[t]==='L' && pCur <= pTop) || (ASSOCIATIVITY[t]==='R' && pCur < pTop) ){
                            output.push(ops.pop());
                        } else break;
                    }
                    ops.push(t);
                }
                prevType='OP';
                continue;
            }
            // operand
            output.push(t);
            prevType='VALUE';
        }
        while(ops.length){
            const op=ops.pop();
            if(op==='(') return null; // mismatched
            output.push(op);
        }
        // Build AST from RPN
        const stack=[];
        for(const tk of output){
            if(tk.startsWith('u')){ // unary
                if(stack.length<1) return null;
                const a = stack.pop();
                stack.push({type:'unary', op: tk.slice(1), arg:a});
            } else if(tk in BIN_PRECEDENCE){
                if(stack.length<2) return null;
                const b = stack.pop();
                const a = stack.pop();
                stack.push({type:'binary', op: tk, left:a, right:b});
            } else {
                stack.push({type:'lit', value: tk});
            }
        }
        if(stack.length!==1) return null;
        return stack[0];
    }

    function astToString(node){
        if(!node) return null;
        switch(node.type){
            case 'lit': return node.value;
            case 'unary': {
                const fn = UNARY_FUNC[node.op];
                if(!fn) return null;
                return fn + '(' + astToString(node.arg) + ')';
            }
            case 'binary': {
                const fn = OP_FUNC[node.op];
                if(!fn) return null;
                return fn + '(' + astToString(node.left) + ', ' + astToString(node.right) + ')';
            }
        }
        return null;
    }

    function transformExpression(expr){
        // quick check if expression even has an operator char
        if(!/[+\-*/%<>=!&|^~]/.test(expr)) return expr; // nothing to do
        const tokens = tokenizeExpr(expr);
        if(!tokens) return expr; // unsupported tokens, skip
        // skip pure literal/identifier
        if(tokens.length<=1) return expr;
        const ast = toAST(tokens);
        if(!ast) return expr;
        const out = astToString(ast);
        return out || expr;
    }

    function transformInsideParens(src){
        let i=0; let out='';
        while(i < src.length){
            const c = src[i];
            if(c==='"' || c==='\'' || c==='`'){
                // copy string literal verbatim
                let quote=c; let j=i+1; let esc=false; let seg=quote;
                for(; j<src.length; j++){
                    const ch=src[j]; seg+=ch; if(esc){ esc=false; continue; } if(ch==='\\'){ esc=true; continue; } if(ch===quote){ j++; break; }
                }
                out+=seg; i=j; continue;
            }
            if(c==='('){
                const end = findMatching(src, i, '(', ')');
                if(end === -1){ out+=c; i++; continue; }
                const inner = src.slice(i+1,end);
                const transformedInner = transformExpression(inner.trim());
                out += '(' + (transformedInner) + ')';
                i = end+1; continue;
            }
            out+=c; i++;
        }
        return out;
    }

    function transformAssignments(stmt){
        // find first top-level assignment '=' (not '==','!=','<=','>=')
        let depth=0; let inStr=false; let strCh='';
        for(let i=0;i<stmt.length;i++){
            const c=stmt[i];
            if(inStr){
                if(c==='\\'){ i++; continue; }
                if(c===strCh){ inStr=false; }
                continue;
            }
            if(c==='"'||c==='\''||c==='`'){ inStr=true; strCh=c; continue; }
            if(c==='('||c==='['||c==='{') depth++;
            else if(c===')'||c===']'||c==='}') depth--;
            else if(c==='=' && depth===0){
                // ensure not part of ==, >=, <=, !=
                const before = stmt[i-1];
                const after = stmt[i+1];
                if(before==='=' || before==='!' || before==='<' || before==='>') continue;
                if(after==='=') continue;
                const lhs = stmt.slice(0,i).trimEnd();
                const rhs = stmt.slice(i+1).trim();
                const newRhs = transformExpression(rhs);
                return lhs + ' = ' + newRhs;
            }
        }
        return stmt;
    }

    function transformStatements(src){
        // split by semicolons outside strings/brackets using existing splitter
        let parts;
        try { parts = splitOutsideStrings(src, ';'); }
        catch { return src; }
        const rebuilt = parts.map(p => {
            const trimmed = p.trim();
            if(!trimmed) return p;
            // avoid transforming control structure headers (if/while/for) here
            if(/^(if|while|for)\s*\(/.test(trimmed)) return p;
            // skip macro definitions
            if(/=\s*macro\s*\{/.test(trimmed)) return p;
            let transformed = transformAssignments(p);
            if(transformed === p){
                transformed = transformExpression(p);
            }
            transformed = transformInsideParens(transformed);
            return transformed;
        });
        return rebuilt.join('; ');
    }

    function feraw_expand_operators(input){
        try {
            return transformStatements(input);
        } catch (e){
            console.warn('Operator expansion failed:', e.message);
            return input; // fail gracefully
        }
    }

    // expose globally
    if (typeof globalThis !== 'undefined') {
        globalThis.feraw_expand_operators = feraw_expand_operators;
    }
})();
// --- END infix operators expansion ---

function parseArgs(argStr) {
    const args = [];
    let cur = "";
    let depth = 0;
    let inSingle = false, inDouble = false, inBacktick = false, escape = false;
    const maxDepth = 50; // Prevent stack overflow

    for (let i = 0; i < argStr.length; i++) {
        const c = argStr[i];

        if (escape) {
            cur += c;
            escape = false;
            continue;
        }
        if (c === "\\" && (inSingle || inDouble || inBacktick)) {
            cur += c;
            escape = true;
            continue;
        }
        if (c === "'" && !inDouble && !inBacktick) {
            inSingle = !inSingle;
            cur += c;
            continue;
        }
        if (c === '"' && !inSingle && !inBacktick) {
            inDouble = !inDouble;
            cur += c;
            continue;
        }
        if (c === "`" && !inSingle && !inDouble) {
            inBacktick = !inBacktick;
            cur += c;
            continue;
        }

        if (!inSingle && !inDouble && !inBacktick) {
            if (c === "(" || c === "[" || c === "{") {
                depth++;
                if (depth > maxDepth) {
                    console.warn('Maximum nesting depth reached in parseArgs');
                    break;
                }
            }
            if (c === ")" || c === "]" || c === "}") depth--;
            if (c === "," && depth === 0) {
                if (cur.trim() !== "") args.push(cur.trim());
                cur = "";
                continue;
            }
        }
        cur += c;
    }
    if (cur.trim() !== "") args.push(cur.trim());
    return args;
}

function feraw_expand_macros(src) {
    const macros = {};

    // Helper function to extract macro body with proper brace matching
    function extractMacroBody(src, startIndex) {
        let i = startIndex;
        let depth = 1;
        let inString = false;
        let stringChar = '';
        let escape = false;
        let inLineComment = false;
        let inBlockComment = false;
        
        while (i < src.length && depth > 0) {
            const char = src[i];
            
            if (escape) {
                escape = false;
                i++;
                continue;
            }
            
            if (char === '\\' && inString) {
                escape = true;
                i++;
                continue;
            }
            
            // Handle comments
            if (!inString && !inLineComment && !inBlockComment) {
                if (char === '/' && i + 1 < src.length && src[i + 1] === '/') {
                    inLineComment = true;
                    i += 2;
                    continue;
                }
                if (char === '/' && i + 1 < src.length && src[i + 1] === '*') {
                    inBlockComment = true;
                    i += 2;
                    continue;
                }
            }
            
            if (inLineComment) {
                if (char === '\n') inLineComment = false;
                i++;
                continue;
            }
            
            if (inBlockComment) {
                if (char === '*' && i + 1 < src.length && src[i + 1] === '/') {
                    inBlockComment = false;
                    i += 2;
                    continue;
                }
                i++;
                continue;
            }
            
            // Handle strings
            if (!inString && !inLineComment && !inBlockComment && (char === '"' || char === "'" || char === '`')) {
                inString = true;
                stringChar = char;
            } else if (inString && char === stringChar) {
                inString = false;
                stringChar = '';
            }
            
            // Only count braces outside strings and comments
            if (!inString && !inLineComment && !inBlockComment) {
                if (char === '{') {
                    depth++;
                } else if (char === '}') {
                    depth--;
                }
            }
            
            i++;
        }
        
        return depth === 0 ? i - 1 : -1; // Return index of closing brace
    }

    // Improved macro capture with proper brace matching
    let i = 0;
    while (i < src.length) {
        const macroMatch = src.slice(i).match(/^(\w+)\s*=\s*macro\s*\{/);
        if (macroMatch) {
            const name = macroMatch[1];
            const macroStart = i + macroMatch[0].length - 1; // position of '{'
            const macroEnd = extractMacroBody(src, macroStart + 1);
            
            if (macroEnd === -1) {
                console.warn(`Malformed macro ${name}, skipping`);
                i += macroMatch[0].length;
                continue;
            }
            
            const body = src.slice(macroStart + 1, macroEnd).trim();
            macros[name] = body;
            
            // Remove macro declaration from source
            const beforeMacro = src.slice(0, i);
            const afterMacro = src.slice(macroEnd + 1);
            // Skip optional semicolon
            const afterMatch = afterMacro.match(/^\s*;?\s*/);
            src = beforeMacro + afterMacro.slice(afterMatch ? afterMatch[0].length : 0);
            continue;
        }
        i++;
    }

    // Function to expand macros with safer recursion detection
    function expandMacroSafely(content, expansionStack = []) {
        let result = content;
        let changed = true;
        let passes = 0;
        const maxPasses = 10;
        
        while (changed && passes < maxPasses) {
            changed = false;
            passes++;
            
            for (const name in macros) {
                // Check for circular dependency - completely skip if found
                if (expansionStack.includes(name)) {
                    continue; // Skip this macro entirely
                }
                
                // Function macro: nome(...)
                let pos = 0;
                while (pos < result.length) {
                    const nameRegex = new RegExp("\\b" + name + "\\s*\\(", "g");
                    nameRegex.lastIndex = pos;
                    const match = nameRegex.exec(result);
                    
                    if (!match) break;
                    
                    const callStart = match.index;
                    const parenStart = match.index + match[0].length - 1; // position of '('
                    
                    // Find matching closing parenthesis
                    let parenEnd = -1;
                    let depth = 1;
                    let inString = false;
                    let stringChar = '';
                    let escape = false;
                    
                    for (let j = parenStart + 1; j < result.length && depth > 0; j++) {
                        const char = result[j];
                        
                        if (escape) {
                            escape = false;
                            continue;
                        }
                        
                        if (char === '\\' && inString) {
                            escape = true;
                            continue;
                        }
                        
                        if (!inString && (char === '"' || char === "'" || char === '`')) {
                            inString = true;
                            stringChar = char;
                        } else if (inString && char === stringChar) {
                            inString = false;
                            stringChar = '';
                        }
                        
                        if (!inString) {
                            if (char === '(') depth++;
                            else if (char === ')') {
                                depth--;
                                if (depth === 0) {
                                    parenEnd = j;
                                    break;
                                }
                            }
                        }
                    }
                    
                    if (parenEnd === -1) {
                        console.warn(`Malformed macro call ${name}, skipping`);
                        pos = match.index + match[0].length;
                        continue;
                    }
                    
                    const argsStr = result.slice(parenStart + 1, parenEnd);
                    const args = parseArgs(argsStr);
                    let expanded = macros[name];

                    // substituições $n
                    args.forEach((arg, i) => {
                        const re = new RegExp("\\$" + i + "(?!\\d)", "g");
                        expanded = expanded.replace(re, arg);
                    });

                    // extras
                    expanded = expanded.replace(/\$count\b/g, args.length.toString());
                    expanded = expanded.replace(/\$all\b/g, args.join(", "));

                    // Recursively expand any nested macros in the expanded content
                    expanded = expandMacroSafely(expanded, [...expansionStack, name]);

                    // Replace the macro call with expanded content
                    result = result.slice(0, callStart) + expanded + result.slice(parenEnd + 1);
                    changed = true;
                    pos = callStart + expanded.length;
                }

                // Value macro: nome (not followed by '(')
                const valRegex = new RegExp("\\b" + name + "\\b(?!\\s*\\()", "g");
                if (valRegex.test(result)) {
                    result = result.replace(valRegex, () => {
                        const expanded = expandMacroSafely(macros[name], [...expansionStack, name]);
                        changed = true;
                        return expanded;
                    });
                }
            }
        }
        
        if (passes >= maxPasses) {
            console.warn('Maximum macro expansion passes reached');
        }
        
        return result;
    }

    // Start the expansion process
    return expandMacroSafely(src);
}

function feraw_expand_all(input, depth = 0)
{
    // Prevent infinite recursion
    if (depth > 128) {
        console.warn('Maximum expansion depth reached, stopping to prevent infinite recursion');
        return input;
    }
    
    let previousInput = input;
    input = feraw_expand_macros(input);
    // NEW: infix operators
    if (typeof feraw_expand_operators === 'function') {
        input = feraw_expand_operators(input);
    }
    input = feraw_expand_props(input);
    input = feraw_expand_ifs(input);
    input = feraw_expand_whiles(input);
    input = feraw_expand_fors(input);
    
    // If nothing changed, we're done
    if (input === previousInput) {
        return input;
    }
    
    // Otherwise, try one more pass (but limit depth)
    return feraw_expand_all(input, depth + 1);
}

function feraw_compile(input) 
{
    try {
        input = feraw_expand_all(input);
        const commands = splitOutsideStrings(input, ';');
        const result = [];
        for (const command of commands) 
        {
            if (command && command.trim()) 
            {
                try {
                    result.push(tokenize(command));
                } catch (err) {
                    console.warn(`Error tokenizing command "${command}": ${err.message}`);
                    // Skip malformed commands
                }
            }
        }

        let result_string = feraw_labelparser(result);
        result_string = result_string.replaceAll("\n\n", "\n"); // Remove double newlines
        return result_string;
    } catch (err) {
        console.error(`Compilation error: ${err.message}`);
        return `/* Compilation failed: ${err.message} */`;
    }
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
            const lines = data.split(/\n/);
            
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
                            console.warn(`Missing include file: ${incFile} at ${incPath}`);
                        }
                    } catch (err) {
                        content.push(`/* error including ${incFile}: ${err.message} */`);
                        console.error(`Error including ${incFile}:`, err.message);
                    }
                } else {
                    content.push(line);
                }
            }
        } catch (err) {
            content.push(`/* error processing ${filePath}: ${err.message} */`);
            console.error(`Error processing ${filePath}:`, err.message);
        }
        
        return content;
    }

    function processContent(content) {
        const ccBlocks = [];
        const functions = [];
        let otherLines = [];
        let insideCC = false;
        let depth = 0;
        let ccBuffer = [];

        for (const line of content) {
            // Detect function declarations: void funcName(BruterList
            const funcMatch = line.match(/^\s*void\s+([a-zA-Z0-9_]+|[a-zA-Z_][a-zA-Z0-9_]*)\s*\(\s*BruterList/);
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

    function generateOutputC(outputPath, { ccBlocks, functions, otherLines }) {
        let output = `#include "bruter.h"\n`;
        output += `#include <stdlib.h>\n\n`;
        
        if (ccBlocks.length > 0) {
            output += `/* BEGIN cc blocks */\n`;
            output += ccBlocks.join('\n') + '\n';
            output += `/* END cc blocks */\n\n`;
        }
        
        output += `int main(int argc, char *argv[])\n{\n`;
        
        output += `    BruterList *context = bruter_new(BRUTER_DEFAULT_SIZE, true, true);\n\n`;
        
        // lets add the args to a list called "args"
        output += `    BruterList *args = bruter_new(BRUTER_DEFAULT_SIZE, false, true);\n`;
        output += `    for(int i = 0; i < argc; i++) { bruter_push_pointer(args, argv[i], NULL, BRUTER_TYPE_BUFFER); }\n`;
        output += `    bruter_push_pointer(context, args, "args", BRUTER_TYPE_LIST);\n\n`;

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
        otherLines = joinedCode.split(/\n/).filter(line => line.trim());

        output += `    const char *embedded_code =\n`;
        for (const line of otherLines) {
            if (!line.trim()) continue;
            const escaped = line
                .replace(/\\/g, '\\\\')
                .replace(/"/g, '\\"');
            output += `    "${escaped}\\n"\n`;
        }
        output += `    ;\n\n`;
        
        output += `    bruter_interpret(context, embedded_code, NULL, NULL);\n`;
        output += `\n`;
        output += `    bruter_free(args);\n`;
        output += `    bruter_free(context);\n`;
        output += `    return EXIT_SUCCESS;\n}\n`;
        
        fs.writeFileSync(outputPath, output);
    }

    function generateOutputBruter(outputPath, { otherLines }) {
        let joinedCode = otherLines.join('\n');
        joinedCode = feraw_compile(joinedCode);
        fs.writeFileSync(outputPath, joinedCode);
    }

    // Main execution
    if (process.argv.length < 4) {
        console.error(`Usage: ${path.basename(process.argv[1])} <input.br> <output.(c|br)>`);
        process.exit(1);
    }
    const inputFile = path.resolve(process.argv[2]);
    const outputFile = path.resolve(process.argv[3]);

    try {
        // Step 1: Expand includes
        const expandedContent = expandIncludes(inputFile);
        
        // Step 2: Process content
        const processed = processContent(expandedContent);
        // Step 3: Decide output based on extension
        if (outputFile.endsWith(".c")) {
            generateOutputC(outputFile, processed);
        } else if (outputFile.endsWith(".br")) {
            generateOutputBruter(outputFile, processed);
        } else {
            throw new Error("Unsupported output extension, use .c or .br");
        }
        
        console.log(`Successfully generated: ${outputFile}`);
    } catch (err) {
        console.error(`Error: ${err.message}`);
        process.exit(1);
    }
}