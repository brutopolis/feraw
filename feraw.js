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

        tokens.push(',' + str);
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

        if (["true", "false", "stack", "context", "program"].includes(name))
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
                case "program":
                    tokens.push('%');
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
            tokens.push("," + name);
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
    let unreversed_input = original_input.map(tokens => tokens.join('\t')).join('\t');
    
    // split by tab only
    let splited = unreversed_input.toString().split(/\t+/);
    
    let input = original_input.map(tokens => tokens.reverse().join('\t'))
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

        // Remove label: outside strings/comments
        let labelMatch = input.slice(i).match(/^(\w+):/);
        if (labelMatch) {
            i += labelMatch[0].length;
            continue;
        }

        out += c;
        i++;
    }
    input = out;

    // Replace label references, but skip inside strings/comments
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
        let labelRegex = new RegExp(`\\b${label[0]}\\b`, 'g');

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

            // Try to match label at this position
            let match = input.slice(i2).match(new RegExp(`^\\b${label[0]}\\b`));
            if (match) {
                out2 += `${label[1]}`;
                i2 += label[0].length;
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
function feraw_expand_functions(input) {
    let i = 0;
    let out = '';
    let inDoubleQuotes = false;
    let inBackticks = false;
    let escape = false;

    function isIdentChar(ch) {
        if (!ch) return false;
        const c = ch.charCodeAt(0);
        return (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || ch === '_';
    }

    function extractBlock(startIdx) {
        let j = startIdx;
        let depth = 1;
        let inDQ = false, inBT = false, inSQ = false, esc = false;
        let inLineComment = false, inBlockComment = false;
        let maxNesting = 50; // Prevent excessive nesting
        
        while (j < input.length && depth > 0 && depth <= maxNesting) {
            const ch = input[j];
            
            if (esc) { 
                esc = false; 
                j++; 
                continue; 
            }
            
            if (ch === '\\' && (inDQ || inBT || inSQ)) { 
                esc = true; 
                j++; 
                continue; 
            }
            
            // Handle comments first to avoid confusion with strings
            if (!inDQ && !inBT && !inSQ && !inLineComment && !inBlockComment) {
                if (ch === '/' && j + 1 < input.length && input[j + 1] === '/') {
                    inLineComment = true;
                    j += 2;
                    continue;
                }
                if (ch === '/' && j + 1 < input.length && input[j + 1] === '*') {
                    inBlockComment = true;
                    j += 2;
                    continue;
                }
            }
            
            if (inLineComment) {
                if (ch === '\n') inLineComment = false;
                j++;
                continue;
            }
            
            if (inBlockComment) {
                if (ch === '*' && j + 1 < input.length && input[j + 1] === '/') {
                    inBlockComment = false;
                    j += 2;
                    continue;
                }
                j++;
                continue;
            }
            
            // Handle strings when not in comments
            if (!inDQ && !inBT && !inSQ && !inLineComment && !inBlockComment) {
                if (ch === '"') { inDQ = true; j++; continue; }
                if (ch === '`') { inBT = true; j++; continue; }
                if (ch === "'") { inSQ = true; j++; continue; }
            } else {
                if (inDQ && ch === '"') { inDQ = false; j++; continue; }
                if (inBT && ch === '`') { inBT = false; j++; continue; }
                if (inSQ && ch === "'") { inSQ = false; j++; continue; }
            }
            
            // Only count braces outside strings and comments
            if (!inDQ && !inBT && !inSQ && !inLineComment && !inBlockComment) {
                if (ch === '{') { 
                    depth++; 
                } else if (ch === '}') {
                    depth--;
                    if (depth === 0) break;
                }
            }
            
            j++;
        }
        
        if (depth > maxNesting) {
            console.warn('Maximum nesting depth exceeded in function block');
            return -1;
        }
        
        return depth === 0 ? j : -1;
    }

    while (i < input.length) {
        const c = input[i];

        // Handle string literals and escapes more robustly
        if (escape) { out += c; escape = false; i++; continue; }
        if (c === '\\') { out += c; escape = true; i++; continue; }
        if (!inDoubleQuotes && !inBackticks && (c === '"' || c === '`')) {
            if (c === '"') inDoubleQuotes = true; else inBackticks = true;
            out += c; i++; continue;
        }
        if (inDoubleQuotes && c === '"') { inDoubleQuotes = false; out += c; i++; continue; }
        if (inBackticks && c === '`') { inBackticks = false; out += c; i++; continue; }
        if (inDoubleQuotes || inBackticks) { out += c; i++; continue; }

        // More robust detection: name = function{ ... };
        const assignMatch = input.slice(i).match(/^([a-zA-Z_$][a-zA-Z0-9_$]*)\s*=\s*function\s*\{/);
        if (assignMatch) {
            const name = assignMatch[1];
            const assignStart = i + assignMatch[0].length - 1; // position of '{'
            const blockEnd = extractBlock(assignStart + 1);
            
            if (blockEnd === -1) { 
                // More graceful fallback for malformed assignment
                console.warn(`Malformed function assignment for ${name}, skipping`);
                out += assignMatch[0].slice(0, -1); // output everything except '{'
                i += assignMatch[0].length - 1;
                continue; 
            }
            
            try {
                const content = feraw_compile(input.slice(assignStart + 1, blockEnd));
                const tokens = content.split(/[\t\n]+/).filter(Boolean);

                out += `${name} = list(0);\n`;
                for (const str of tokens) {
                    if (str[0] === ',') {
                        // Escape quotes properly
                        const escaped = (str.slice(1)).replace(/\\/g, '\\\\').replace(/"/g, '\\"');
                        out += `push(${name}, "${escaped}");\n`;
                    } else {
                        // Validate token before adding
                        if (str.trim()) {
                            out += `push(${name}, "${str}");\n`;
                        }
                    }
                }
                out += `for(i = 0; less(i, length(${name})); i = add(i, 1)) {retype(${name}, i, 0);}\n`;
                i = blockEnd + 1;
                // Skip optional semicolon
                if (i < input.length && input[i] === ';') i++;
                continue;
            } catch (err) {
                console.warn(`Error compiling function ${name}: ${err.message}`);
                out += assignMatch[0];
                i += assignMatch[0].length;
                continue;
            }
        }

        // More robust detection: function{ ... } (not part of identifier)
        if (input.slice(i, i + 9) === 'function{' && (i === 0 || !isIdentChar(input[i - 1]))) {
            const openIdx = i + 8;
            const blockEnd = extractBlock(openIdx + 1);
            
            if (blockEnd === -1) { 
                console.warn('Malformed standalone function block, skipping');
                out += 'function';
                i += 8;
                continue; 
            }
            
            try {
                const content = feraw_compile(input.slice(openIdx + 1, blockEnd));
                const tokens = content.split(/[\t\n]+/).filter(Boolean);

                out += "function_prototype = list(0);\n";
                for (const str of tokens) {
                    if (str[0] === ',') {
                        const escaped = (str.slice(1)).replace(/\\/g, '\\\\').replace(/"/g, '\\"');
                        out += `push(function_prototype, "${escaped}");\n`;
                    } else if (/^[\$\#\!\?\:\&\@\%]/.test(str)) {
                        out += `push(function_prototype, "${str}");\n`;
                    } else if (str.trim()) {
                        out += `push(function_prototype, ${str});\n`;
                    }
                }
                out += `remove(context, function_prototype);\n`;
                i = blockEnd + 1;
                continue;
            } catch (err) {
                console.warn(`Error compiling standalone function: ${err.message}`);
                out += 'function{';
                i += 9;
                continue;
            }
        }

        // Default: copy character
        out += c;
        i++;
    }
    return out;
}

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
    if (depth > 10) {
        console.warn('Maximum expansion depth reached, stopping to prevent infinite recursion');
        return input;
    }
    
    let previousInput = input;
    input = feraw_expand_macros(input);
    input = feraw_expand_functions(input);
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
        output += `    bruter_free(context);\n`;
        output += `    return EXIT_SUCCESS;\n}\n`;
        
        fs.writeFileSync(outputPath, output);
    }

    function generateOutputFeraw(outputPath, { otherLines }) {
        let joinedCode = otherLines.join('\n');
        joinedCode = feraw_compile(joinedCode);
        fs.writeFileSync(outputPath, joinedCode);
    }

    // Main execution
    if (process.argv.length < 3) {
        console.error(`Usage: ${path.basename(process.argv[1])} <input.feraw> <output.(c|feraw)>`);
        process.exit(1);
    }
    else if (process.argv.length == 3) {
        process.stdout.write(feraw_compile(fs.readFileSync(process.argv[2], 'utf8')));
        process.stdout.write('\n');
        process.exit(0);
    };
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
        } else if (outputFile.endsWith(".feraw")) {
            generateOutputFeraw(outputFile, processed);
        } else {
            throw new Error("Unsupported output extension, use .c or .feraw");
        }
        
        console.log(`Successfully generated: ${outputFile}`);
    } catch (err) {
        console.error(`Error: ${err.message}`);
        process.exit(1);
    }
}