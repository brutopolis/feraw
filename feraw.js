#!/usr/bin/env node
let feraw_if_counter = 0;
let feraw_while_counter = 0;
let feraw_for_counter = 0;
let feraw_switch_counter = 0;

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

            if (input[i] === '\n')
            {
                str += String.fromCharCode(26); // newline
            }
            else if (input[i] === '\r')
            {
                str += String.fromCharCode(28); // carriage return
            }
            else if (input[i] === '\t')
            {
                str += String.fromCharCode(29); // tab
            }
            else if (input[i] === ' ')
            {
                str += String.fromCharCode(30); // space
            }
            else 
            {
                str += input[i];
            }

            i++;
        }

        tokens.push(',' + str);
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

        if (["true", "false", "null", "stack", "context", "code"].includes(name))
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
                    tokens.push('!', 'retype', '@', '0', '0');
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
            tokens.push("," + name);
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

    // Função para restaurar caracteres especiais
    function restoreSpecialChars(str) {
        return str
            .replace(/\x1A/g, '\n')   // 26 -> \n
            .replace(/\x1C/g, '\r')   // 28 -> \r
            .replace(/\x1D/g, '\t')   // 29 -> \t
            .replace(/\x1E/g, ' ');   // 30 -> espaço
    }

    while (i < input.length) {
        const c = input[i];

        // --- Strings e escapes (mesma lógica do seu estilo) ---
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
            if (c === '"') inDoubleQuotes = true; else inBackticks = true;
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

        // Detecta nome = function{ ... };
        let assignMatch = input.slice(i).match(/^([a-zA-Z_$][a-zA-Z0-9_$]*)\s*=\s*function\{/);
        if (assignMatch) {
            let name = assignMatch[1];
            let assignLen = assignMatch[0].length - 1; // até o '{'
            let openIdx = i + assignLen;
            // varre até achar o '}' pareado, com nesting e ignorando strings/escapes
            let j = openIdx + 1;
            let depth = 1;
            let inDQ2 = false;
            let inBT2 = false;
            let esc2 = false;

            while (j < input.length) {
                const ch = input[j];
                if (esc2) { esc2 = false; j++; continue; }
                if (ch === '\\') { esc2 = true; j++; continue; }
                if (!inDQ2 && !inBT2 && (ch === '"' || ch === '`')) {
                    if (ch === '"') inDQ2 = true; else inBT2 = true;
                    j++; continue;
                }
                if (inDQ2 && ch === '"') { inDQ2 = false; j++; continue; }
                if (inBT2 && ch === '`') { inBT2 = false; j++; continue; }
                if (!inDQ2 && !inBT2) {
                    if (ch === '{') { depth++; j++; continue; }
                    if (ch === '}') {
                        depth--;
                        if (depth === 0) break;
                        j++; continue;
                    }
                }
                j++;
            }

            if (depth !== 0) {
                // não fechou: copia literal e segue (fail-safe)
                out += input[i];
                i++;
                continue;
            }

            let content = feraw_compile(input.slice(openIdx + 1, j));
            let tokens = content.split(/[\s\r\n\t]+/).filter(t => t.length > 0);

            out += `${name} = list(0);\n`;
            while (tokens.length > 0) {
                let str = tokens.shift();

                if (str[0] === ',') {
                    // Se começar com vírgula, transforma o conteúdo depois da vírgula em string normal
                    let restored = restoreSpecialChars(str.slice(1));
                    out += `push(${name}, "${restored}");\n`;
                    // NÃO faz retype nesse caso
                } else if (/^[\$\#\!\?\:\&\@\%]/.test(str)) {
                    out += `push(${name}, "${str}");\n`;
                    out += `retype(${name}, sub(length(${name}), 1), 0);\n`;
                } else {
                    out += `push(${name}, ${str});\n`;
                }
            }
            // pula até depois do }
            i = j + 1;
            // pula o ; se existir
            if (input[i] === ';') i++;
            continue;
        }

        // --- Detecta EXACT "function{" (sem espaços) e não parte de identificador maior ---
        if (i + 9 <= input.length) {
            const f = input[i]     === 'f' &&
                      input[i + 1] === 'u' &&
                      input[i + 2] === 'n' &&
                      input[i + 3] === 'c' &&
                      input[i + 4] === 't' &&
                      input[i + 5] === 'i' &&
                      input[i + 6] === 'o' &&
                      input[i + 7] === 'n' &&
                      input[i + 8] === '{';

            if (f) {
                // evita pegar "myfunction{...}"
                const prev = i > 0 ? input[i - 1] : '';
                if (!isIdentChar(prev)) {
                    // índice do '{'
                    const openIdx = i + 8;
                    // varre até achar o '}' pareado, com nesting e ignorando strings/escapes
                    let j = openIdx + 1;
                    let depth = 1;
                    let inDQ2 = false;
                    let inBT2 = false;
                    let esc2 = false;

                    while (j < input.length) {
                        const ch = input[j];

                        if (esc2) { esc2 = false; j++; continue; }
                        if (ch === '\\') { esc2 = true; j++; continue; }

                        if (!inDQ2 && !inBT2 && (ch === '"' || ch === '`')) {
                            if (ch === '"') inDQ2 = true; else inBT2 = true;
                            j++; continue;
                        }
                        if (inDQ2 && ch === '"') { inDQ2 = false; j++; continue; }
                        if (inBT2 && ch === '`') { inBT2 = false; j++; continue; }

                        if (!inDQ2 && !inBT2) {
                            if (ch === '{') { depth++; j++; continue; }
                            if (ch === '}') {
                                depth--;
                                if (depth === 0) break;
                                j++; continue;
                            }
                        }

                        j++;
                    }

                    if (depth !== 0) {
                        // não fechou: copia literal e segue (fail-safe)
                        out += input[i];
                        i++;
                        continue;
                    }

                    let content = feraw_compile(input.slice(openIdx + 1, j));
                    
                    out += "function_prototype = list(0);\n";
                    let tokens = content.split(/[\s\r\n\t]+/).filter(t => t.length > 0);

                    while (tokens.length > 0) {
                        let str = tokens.shift();

                        if (str[0] === ',') {
                            let restored = restoreSpecialChars(str.slice(1));
                            out += `push(function_prototype, "${restored}");\n`;
                        } else if (/^[\$\#\!\?\:\&\@\%]/.test(str)) {
                            out += `push(function_prototype, "${str}");\n`;
                            out += `retype(function_prototype, sub(length(function_prototype), 1), 0);\n`;
                        } else {
                            out += `push(function_prototype, ${str});\n`;
                        }
                    }
                    out += `remove(context, function_prototype);\n`;
                    i = j + 1;
                    continue;
                }
            }
        }

        // default: copia
        out += c;
        i++;
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
        let c = str[i];

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
        let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
        if (!nameMatch) { out += str[i++]; continue; }

        let base = nameMatch[1];
        i += base.length;

        // Captura props encadeados (.foo ou [expr])
        let props = [];
        while (i < str.length) {
            if (str[i] === '.') {
                i++;
                let propMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
                if (!propMatch) break;
                props.push({ key: `"${propMatch[1]}"` });
                i += propMatch[1].length;
                continue;
            }
            if (str[i] === '[') {
                let end = findMatching(str, i, '[', ']');
                if (end === -1) break;
                let inner = str.slice(i + 1, end).trim();
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
            let rightSide = str.slice(i, lookaheadEnd);
            let trimmedRight = rightSide.trimStart();

            if (trimmedRight.startsWith('=')) {
                // assignment (já tá certo da msg anterior)
                let valueExpr = trimmedRight.slice(1).trim();
                valueExpr = feraw_expand_props(valueExpr);

                if (props.length === 1) {
                    let k = props[0].key;
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
                    let lastKey = props[props.length - 1].key;

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
                        let prevKey = props[props.length - 2].key;
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
                let lastKey = props[props.length - 1].key;

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
                        let prevKey = props[props.length - 2].key;
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
                        let prevKey = props[props.length - 2].key;
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
                    for (let p of props) {
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

function findMatching(str, start, open, close) {
    let depth = 0;
    for (let i = start; i < str.length; i++) {
        if (str[i] === open) depth++;
        else if (str[i] === close) {
            depth--;
            if (depth === 0) return i;
        }
    }
    return -1;
}

function feraw_expand_all(input)
{
    input = feraw_expand_props(input);
    input = feraw_expand_ifs(input);
    input = feraw_expand_whiles(input);
    input = feraw_expand_fors(input);
    input = feraw_expand_functions(input);
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
        
        output += `    BruterList *result = bruter_interpret(context, embedded_code, NULL);\n`;
        output += `    bruter_free(result);\n`;
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