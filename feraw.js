#!/usr/bin/env node
// feraw compiler - mujs compatible version
var feraw_if_counter = 0;
var feraw_while_counter = 0;
var feraw_for_counter = 0;
var feraw_switch_counter = 0;

function splitOutsideStrings(input, char) 
{
    if (char === undefined) char = ';';
    var parts = [];
    var current = '';
    var inDoubleQuotes = false;
    var inSingleQuotes = false;
    var inBackticks = false;
    var escape = false;

    for (var i = 0; i < input.length; i++) 
    {
        var c = input[i];

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
            var blockDepth = 1;
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
            var parenDepth = c === '(' ? 1 : -1;
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
            var listDepth = c === '[' ? 1 : -1;
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
            var objDepth = c === '{' ? 1 : -1;
            current += c;
            i++;
            while (i < input.length && objDepth !== 0) 
            {
                if (input[i] === '{') 
                {
                    objDepth++;
                } 
                else if (input[i] === '}') 
                {
                    objDepth--;
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

        if (c === char && !inDoubleQuotes && !inSingleQuotes && !inBackticks) 
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
    var tokens = [];
    var i = 0;

    function skipWhitespace() 
    {
        var safety = 0;
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
        var str = '';
        var stringChar = input[i]; // store the opening quote character
        i++; // skip opening quote
        if (input.indexOf('=') === -1)
        {
            isAssignment = true; // if there is no =, we assume this is a string assignment
        }

        while (i < input.length)
        {
            if (input[i] === stringChar) // check for the matching closing quote
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
    
    function parseBlock(depth)
    {
        if (depth === undefined) depth = 0;
        // to be used in future, for something i don't know yet
    }

    function parseRawToken() 
    {
        var start = i;
        while (i < input.length && !/\s/.test(input[i]) && "()[]{},=;".indexOf(input[i]) === -1) {
            i++;
        }
        return input.slice(start, i);
    }

    function parseExpr(depth) 
    {
        if (depth === undefined) depth = 0;
        skipWhitespace();
        if (i >= input.length) return;

        if (input[i] === '"') return parseString();
        if (input[i] === '`') return parseString(); // treat backticks like double quotes
        if (input[i] === "'") // char as int
        {
            i++; // skip opening '
            var char = input[i++];
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
            var start = i;
            i++;
            while (
                i < input.length &&
                !/\s|[\]\[\(\)\{\},]/.test(input[i]) 
            ) {
                i++;
            }

            var numStr = input.slice(start, i);
            var num = Number(numStr);

            if (isNaN(num)) throw new Error("parseExpr: invalid number format: " + numStr);
            tokens.push(num + '');
            return;
        }

        var name = parseRawToken();
        if (!name) throw new Error("parseExpr: invalid or empty token");

        if (["true", "false", "null", "stack", "context", "code"].indexOf(name) !== -1)
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
            if (["!", "?"].indexOf(name) !== -1) 
            {
                tokens.push(name);
            }
            else if (name == "inline") 
            {
                // lets find the end of the parentesis
                var endParen = findMatching(input, i, '(', ')');
                // now we simply put the content as it is
                if (endParen === -1) throw new Error("parseExpr: missing closing ) for br");
                var content = input.slice(i + 1, endParen);
                tokens.push(content);
                i = endParen + 1; // move the index to after the closing parenthesis
                return;
            }
            else 
            {
                tokens.push('!', name);
            }

            i++; // skip '('
            var safety = 0;

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
            var exprTokens = [name]; 
            while (true) 
            {
                skipWhitespace();
                if (input[i] === '(') 
                {
                    i++; // skip '('
                    var argTokens = [];
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
                        argTokens = argTokens.concat(tokens.splice(tokens.length - 1)); 
                        skipWhitespace();
                        if (input[i] === ',') i++; // skip ','
                    }

                    exprTokens = ['!'].concat(exprTokens).concat(argTokens); 
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
                tokens = ['!', 'set'].concat(tokens).concat(exprTokens);

                return; // Crucial: Stop parsing this expression after handling assignment
            }
            
            // --- Not an Assignment ---
            // Push the accumulated expression tokens (representing the access chain)
            tokens = tokens.concat(exprTokens);
        }
    } // End of parseExpr function


    var safety = 0;
    while (i < input.length) 
    {
        skipWhitespace();
        if (i >= input.length) break;

        var start = i;
        var name = parseRawToken();
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
    var unreversed_input = [];
    for (var i = 0; i < original_input.length; i++) {
        unreversed_input.push(original_input[i].join(' '));
    }
    unreversed_input = unreversed_input.join(' ');
    
    // split by any kind of whitespace
    var splited = unreversed_input.toString().split(/\s+/);
    
    var processedInput = [];
    for (var i = 0; i < original_input.length; i++) {
        var reversed = original_input[i].slice();
        reversed.reverse();
        processedInput.push(reversed.join(' '));
    }
    var input = processedInput.join('\n').toString();

    // remove empty strings
    var filteredSplited = [];
    for (var i = 0; i < splited.length; i++) {
        if (splited[i].trim() !== '') {
            filteredSplited.push(splited[i]);
        }
    }
    splited = filteredSplited;
    
    var labels = [];
    var correction = 0;
    for (var i = 0; i < splited.length; i++)
    {
        var word = splited[i];
        if (word.length > 0 && word.charAt(word.length - 1) === ':') 
        {
            var label = word.slice(0, -1);
            labels.push([label, i - correction]);
            correction++;
        }
    }

    // lets remove all label: from the input
    input = input.replace(/(\w+):/g, '');

    
    for (var i = 0; i < labels.length; i++) 
    {
        var label = labels[i];
        input = input.replace(new RegExp('\\b' + label[0] + '\\b', 'g'), label[1].toString());
    }
    return input;
}

function findMatching(input, start, openChar, closeChar) 
{
    var depth = 1;
    var inString = false;
    var stringChar = '';
    var escapeNext = false;
    for (var i = start + 1; i < input.length; i++) 
    {
        var char = input[i];
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
        if (!inString && (char === '"' || char === "'" || char === '`')) 
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
    var i = 0;
    var out = '';
    var inDoubleQuotes = false;
    var inBackticks = false;
    var escape = false;

    while (i < input.length) {
        var c = input[i];

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
            var id = feraw_if_counter++;

            i += 2;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'if';
                continue;
            }

            var condStart = i;
            var condEnd = findMatching(input, i, '(', ')');
            var cond = input.slice(condStart + 1, condEnd);
            i = condEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += 'if(' + cond + ')';
                continue;
            }

            var ifBlockEnd = findMatching(input, i, '{', '}');
            var ifBlock = input.slice(i + 1, ifBlockEnd);
            i = ifBlockEnd + 1;
            while (/\s/.test(input[i])) i++;

            var chain = [{ cond: cond, block: ifBlock }];
            var elseBlock = '';

            while (/^else\b/.test(input.slice(i))) {
                i += 4;
                while (/\s/.test(input[i])) i++;
                if (/^if\s*\(/.test(input.slice(i))) {
                    i += 2;
                    while (/\s/.test(input[i])) i++;
                    if (input[i] !== '(') break;
                    var condStart = i;
                    var condEnd = findMatching(input, i, '(', ')');
                    var cond = input.slice(condStart + 1, condEnd);
                    i = condEnd + 1;
                    while (/\s/.test(input[i])) i++;
                    if (input[i] !== '{') break;
                    var blockEnd = findMatching(input, i, '{', '}');
                    var block = input.slice(i + 1, blockEnd);
                    i = blockEnd + 1;
                    chain.push({ cond: cond, block: block });
                } else if (input[i] === '{') {
                    var elseEnd = findMatching(input, i, '{', '}');
                    elseBlock = input.slice(i + 1, elseEnd);
                    i = elseEnd + 1;
                    break;
                } else {
                    break;
                }
                while (/\s/.test(input[i])) i++;
            }

            for (var j = 0; j < chain.length; j++) {
                chain[j].block = feraw_expand_all(chain[j].block);
            }
            if (elseBlock) {
                elseBlock = feraw_expand_all(elseBlock);
            }

            var trueLabels = [];
            for (var j = 0; j < chain.length; j++) {
                trueLabels.push('if' + id + '_true_' + j);
            }
            var afterLabel = 'if' + id + '_after';

            out += '?(' + chain[0].cond + ', ' + trueLabels[0] + ');\n';
            if (elseBlock) {
                out += elseBlock + '\n';
                out += '?(1, ' + afterLabel + ');\n';
            } else {
                out += '?(1, ' + afterLabel + ');\n';
            }
            for (var j = 0; j < chain.length; j++) {
                out += trueLabels[j] + ':\n';
                out += chain[j].block + '\n';
                if (j + 1 < chain.length) {
                    out += '?(' + chain[j + 1].cond + ', ' + trueLabels[j + 1] + ');\n';
                    out += '?(1, ' + afterLabel + ');\n';
                }
            }
            out += afterLabel + ':\n';
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_whiles(input) {
    var i = 0;
    var out = '';
    var inDoubleQuotes = false;
    var inBackticks = false;
    var escape = false;

    while (i < input.length) {
        var c = input[i];

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
            var id = feraw_while_counter++;
            i += 5;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'while';
                continue;
            }
            var condStart = i;
            var condEnd = findMatching(input, i, '(', ')');
            var cond = input.slice(condStart + 1, condEnd);
            i = condEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += 'while(' + cond + ')';
                continue;
            }
            var whileBlockEnd = findMatching(input, i, '{', '}');
            var whileBlock = input.slice(i + 1, whileBlockEnd);
            i = whileBlockEnd + 1;
            while (/\s/.test(input[i])) i++;
            whileBlock = feraw_expand_all(whileBlock);

            var whileTrueLabel = 'while' + id + '_true';
            var whileAfterLabel = 'while' + id + '_after';
            var whileStartLabel = 'while' + id + '_start';

            out += whileStartLabel + ':\n';
            out += '?(' + cond + ', ' + whileTrueLabel + ');\n';
            out += '?(1, ' + whileAfterLabel + ');\n';
            out += whileTrueLabel + ':\n';
            out += whileBlock + '\n';
            out += '?(1, ' + whileStartLabel + ');\n';
            out += whileAfterLabel + ':\n';
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_functions(input) {
    var i = 0;
    var out = '';
    var inDoubleQuotes = false;
    var inBackticks = false;
    var escape = false;

    function isIdentChar(ch) {
        if (!ch) return false;
        var c = ch.charCodeAt(0);
        return (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || ch === '_';
    }

    // Escapa " e \ para caber entre aspas duplas
    function escapeForDoubleQuotedString(s) {
        var r = '';
        for (var k = 0; k < s.length; k++) {
            var ch = s[k];
            if (ch === '\\' || ch === '"') r += '\\' + ch;
            else r += ch;
        }
        return r;
    }

    while (i < input.length) {
        var c = input[i];

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

        // --- Detecta EXACT "function{" (sem espaços) e não parte de identificador maior ---
        // "function" tem 8 chars; "function{" tem 9 no total.
        if (i + 9 <= input.length) {
            // checa literal char-a-char pra não depender de startsWith
            var f = input[i]     === 'f' &&
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
                var prev = i > 0 ? input[i - 1] : '';
                if (!isIdentChar(prev)) {
                    // índice do '{'
                    var openIdx = i + 8;
                    // varre até achar o '}' pareado, com nesting e ignorando strings/escapes
                    var j = openIdx + 1;
                    var depth = 1;
                    var inDQ2 = false;
                    var inBT2 = false;
                    var esc2 = false;

                    while (j < input.length) {
                        var ch = input[j];

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

                    var content = feraw_compile(input.slice(openIdx + 1, j));
                    out += 'fun("' + content + '")';
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
    var i = 0;
    var out = '';
    var inDoubleQuotes = false;
    var inBackticks = false;
    var escape = false;

    while (i < input.length) {
        var c = input[i];

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
            var id = feraw_for_counter++;
            i += 3;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '(') {
                out += 'for';
                continue;
            }
            var headerStart = i;
            var headerEnd = findMatching(input, i, '(', ')');
            var header = input.slice(headerStart + 1, headerEnd);
            i = headerEnd + 1;
            while (/\s/.test(input[i])) i++;
            if (input[i] !== '{') {
                out += 'for(' + header + ')';
                continue;
            }
            var forBlockEnd = findMatching(input, i, '{', '}');
            var forBlock = input.slice(i + 1, forBlockEnd);
            i = forBlockEnd + 1;
            while (/\s/.test(input[i])) i++;

            var headerParts = header.split(';');
            var init = headerParts[0] ? headerParts[0].trim() : '';
            var cond = headerParts[1] ? headerParts[1].trim() : '1';
            var iter = headerParts[2] ? headerParts[2].trim() : '';

            forBlock = feraw_expand_all(forBlock);

            var forStartLabel = 'for' + id + '_start';
            var forTrueLabel = 'for' + id + '_true';
            var forAfterLabel = 'for' + id + '_after';

            out += init ? init + ';\n' : '';
            out += forStartLabel + ':\n';
            out += '?(' + cond + ', ' + forTrueLabel + ');\n';
            out += '?(1, ' + forAfterLabel + ');\n';
            out += forTrueLabel + ':\n';
            out += forBlock + '\n';
            out += iter ? iter + ';\n' : '';
            out += '?(1, ' + forStartLabel + ');\n';
            out += forAfterLabel + ':\n';
            continue;
        }

        out += input[i++];
    }
    return out;
}

function feraw_expand_props(str) {
    var out = '';
    var i = 0;
    var inDoubleQuotes = false;
    var inBackticks = false;
    var escape = false;

    while (i < str.length) {
        var c = str[i];

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
        var nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
        if (!nameMatch) { out += str[i++]; continue; }

        var base = nameMatch[1];
        i += base.length;

        // Captura props encadeados (.foo ou [expr])
        var props = [];
        while (i < str.length) {
            if (str[i] === '.') {
                i++;
                var propMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(str.slice(i));
                if (!propMatch) break;
                props.push({ key: '"' + propMatch[1] + '"' });
                i += propMatch[1].length;
                continue;
            }
            if (str[i] === '[') {
                var end = findMatching(str, i, '[', ']');
                if (end === -1) break;
                var inner = str.slice(i + 1, end).trim();
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
            var lookaheadEnd = str.indexOf(';', i);
            if (lookaheadEnd === -1) lookaheadEnd = str.length;
            var rightSide = str.slice(i, lookaheadEnd);
            
            // Implementação manual de trimStart
            var trimmedRight = rightSide;
            while (trimmedRight.length > 0 && /\s/.test(trimmedRight.charAt(0))) {
                trimmedRight = trimmedRight.slice(1);
            }

            if (trimmedRight.length > 0 && trimmedRight.charAt(0) === '=') {
                // assignment
                var valueExpr = trimmedRight.slice(1);
                // trim manual
                while (valueExpr.length > 0 && /\s/.test(valueExpr.charAt(0))) {
                    valueExpr = valueExpr.slice(1);
                }
                valueExpr = feraw_expand_props(valueExpr);

                if (props.length === 1) {
                    var k = props[0].key;
                    if (k === '"type"') {
                        out += 'retype(@, "' + base + '", ' + valueExpr + ')';
                    } 
                    else if (k === '"name"') 
                    {
                        out += 'rename(' + base + ', "' + base + '", ' + valueExpr + ')';
                    } else {
                        out += 'set(' + base + ', ' + k + ', ' + valueExpr + ')';
                    }
                } 
                else 
                {
                    var lastKey = props[props.length - 1].key;

                    if (lastKey === '"type"') 
                    {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 2; j++) 
                        {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        out += 'retype(' + objExpr + ', ' + props[props.length - 2].key + ', ' + valueExpr + ')';
                    } 
                    else if (lastKey === '"name"') 
                    {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 2; j++) {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        var prevKey = props[props.length - 2].key;
                        out += 'rename(' + objExpr + ', ' + prevKey + ', ' + valueExpr + ')';

                    } else {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 1; j++) {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        out += 'set(' + objExpr + ', ' + lastKey + ', ' + valueExpr + ')';
                    }
                }
                i = lookaheadEnd;
                continue;
            } else {
                // ----------- GET MODE -----------
                var lastKey = props[props.length - 1].key;

                if (lastKey === '"name"') 
                {
                    if (props.length === 1) 
                    {
                        out += 'nameof(@, "' + base + '")';
                    } 
                    else 
                    {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 2; j++) 
                        {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        var prevKey = props[props.length - 2].key;
                        out += 'nameof(' + objExpr + ', ' + prevKey + ')';
                    }
                }
                else if (lastKey === '"type"') 
                {
                    if (props.length === 1) 
                    {
                        out += 'typeof(@, "' + base + '")';
                    } 
                    else 
                    {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 2; j++) {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        var prevKey = props[props.length - 2].key;
                        out += 'typeof(' + objExpr + ', ' + prevKey + ')';
                    }
                } else if (lastKey === '"length"') {
                    if (props.length === 1) {
                        out += 'length(' + base + ')';
                    } else {
                        var objExpr = base;
                        for (var j = 0; j < props.length - 1; j++) {
                            objExpr = 'get(' + objExpr + ', ' + props[j].key + ')';
                        }
                        out += 'length(' + objExpr + ')';
                    }
                } else {
                    // default: get encadeado
                    var expr = base;
                    for (var j = 0; j < props.length; j++) {
                        expr = 'get(' + expr + ', ' + props[j].key + ')';
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
    var depth = 0;
    for (var i = start; i < str.length; i++) {
        if (str[i] === open) depth++;
        else if (str[i] === close) {
            depth--;
            if (depth === 0) return i;
        }
    }
    return -1;
}


function feraw_expand_inline_br(input)
{
    var i = 0;
    var out = '';

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

            var argsStart = i;
            var argsEnd = findMatching(input, i, '{', '}');
            var args = input.slice(argsStart + 1, argsEnd);

            out += 'inline(' + args + ')';
            i = argsEnd + 1;
            continue;
        }

        out += input[i++];
    }

    return out;
}

function feraw_expand_all(input)
{
    input = feraw_expand_props(input);
    input = feraw_expand_ifs(input);
    input = feraw_expand_whiles(input);
    input = feraw_expand_fors(input);
    input = feraw_expand_functions(input);
    input = feraw_expand_inline_br(input);
    return input;
}

function feraw_compile(input) 
{
    input = feraw_expand_all(input);
    var commands = splitOutsideStrings(input, ';');
    var result = [];
    for (var i = 0; i < commands.length; i++) 
    {
        if (commands[i]) 
        {
            result.push(tokenize(commands[i]));
        }
    }

    var result_string = feraw_labelparser(result);
    result_string = result_string.replace(/\n\n/g, "\n"); // Remove double newlines
    return result_string;
}

// only if under node.js
if (typeof process !== 'undefined')
{
    var fs = require('fs');
    var path = require('path');

    var expandIncludes = function(filePath, baseDir) {
        if (baseDir === undefined) baseDir = path.dirname(filePath);
        
        var content = [];
        try {
            var data = fs.readFileSync(filePath, 'utf8');
            var lines = data.split(/\r?\n/);
            
            for (var i = 0; i < lines.length; i++) {
                var line = lines[i];
                var match = line.match(/^\s*include\(\"([^\"]+)\"\);\s*$/);
                if (match) {
                    var incFile = match[1];
                    var incPath = path.join(baseDir, incFile);
                    var incDir = path.dirname(incPath);
                    
                    try {
                        if (fs.existsSync(incPath) && fs.statSync(incPath).isFile()) {
                            content.push('/* start include: ' + incFile + ' */');
                            var includedContent = expandIncludes(incPath, incDir);
                            content = content.concat(includedContent);
                            content.push('/* end include: ' + incFile + ' */');
                            content.push('');
                        } else {
                            content.push('/* missing include: ' + incFile + ' */');
                            console.warn('Missing include file: ' + incFile + ' at ' + incPath);
                        }
                    } catch (err) {
                        content.push('/* error including ' + incFile + ': ' + err.message + ' */');
                        console.error('Error including ' + incFile + ':', err.message);
                    }
                } else {
                    content.push(line);
                }
            }
        } catch (err) {
            content.push('/* error processing ' + filePath + ': ' + err.message + ' */');
            console.error('Error processing ' + filePath + ':', err.message);
        }
        
        return content;
    };

    var processContent = function(content) {
        var ccBlocks = [];
        var functions = [];
        var otherLines = [];
        var insideCC = false;
        var depth = 0;
        var ccBuffer = [];

        for (var i = 0; i < content.length; i++) {
            var line = content[i];
            // Detect function declarations
            var funcMatch = line.match(/function\s*\(\s*([a-zA-Z0-9_]+)\s*\)/);
            if (funcMatch) {
                var funcName = funcMatch[1];
                var cleanName = funcName.indexOf('feraw_') === 0 
                    ? funcName.slice(6) 
                    : funcName;
                functions.push([funcName, cleanName]);
            }

            if (!insideCC) {
                if (/^\s*cc\s*\{/.test(line)) {
                    insideCC = true;
                    depth = 1;
                    var cleaned = line.replace(/^\s*cc\s*\{/, '');
                    if (cleaned.trim()) ccBuffer.push(cleaned);
                } else if (/^\s*cc\s*$/.test(line)) {
                    insideCC = true;
                    depth = 1;
                } else {
                    otherLines.push(line);
                }
            } else {
                for (var j = 0; j < line.length; j++) {
                    var char = line[j];
                    if (char === '{') depth++;
                    if (char === '}') depth--;
                    
                    if (depth === 0) {
                        insideCC = false;
                        break;
                    }
                }
                
                if (!insideCC) {
                    var endIndex = line.indexOf('}') + 1;
                    if (endIndex > 0) {
                        var before = line.substring(0, endIndex - 1);
                        if (before.trim()) ccBuffer.push(before);
                        
                        var after = line.substring(endIndex);
                        if (after.trim()) otherLines.push(after);
                    } else if (line.trim()) {
                        ccBuffer.push(line);
                    }
                    
                    ccBlocks = ccBlocks.concat(ccBuffer);
                    ccBuffer = [];
                } else if (line.trim()) {
                    ccBuffer.push(line);
                }
            }
        }
        
        return { ccBlocks: ccBlocks, functions: functions, otherLines: otherLines };
    };

    var generateOutputC = function(outputPath, data) {
        var ccBlocks = data.ccBlocks;
        var functions = data.functions;
        var otherLines = data.otherLines;
        
        var output = '#include "bruter.h"\n';
        output += '#include <stdlib.h>\n\n';
        
        if (ccBlocks.length > 0) {
            output += '/* BEGIN cc blocks */\n';
            output += ccBlocks.join('\n') + '\n';
            output += '/* END cc blocks */\n\n';
        }
        
        output += 'int main(int argc, char *argv[])\n{\n';
        output += '    BruterList *context = bruter_new(8, true, true);\n\n';
        
        if (functions.length > 0) {
            output += '    /* BEGIN function registrations */\n';
            for (var i = 0; i < functions.length; i++) {
                var funcName = functions[i][0];
                var cleanName = functions[i][1];
                output += '    bruter_push_pointer(context, ' + funcName + ', "' + cleanName + '", BRUTER_TYPE_FUNCTION);\n';
            }
            output += '    /* END function registrations */\n\n';
        }
        
        // lets join the other lines into a single string
        // apply feraw_compile() to it, then split it into lines again
        // then prepare it for embedding
        var joinedCode = otherLines.join('\n');
        joinedCode = feraw_compile(joinedCode);
        var processedLines = joinedCode.split(/\r?\n/);
        var filteredLines = [];
        for (var i = 0; i < processedLines.length; i++) {
            if (processedLines[i].trim()) {
                filteredLines.push(processedLines[i]);
            }
        }

        output += '    const char *embedded_code =\n';
        for (var i = 0; i < filteredLines.length; i++) {
            var line = filteredLines[i];
            if (!line.trim()) continue;
            var escaped = line
                .replace(/\\/g, '\\\\')
                .replace(/"/g, '\\"');
            output += '    "' + escaped + '\\n"\n';
        }
        output += '    ;\n\n';
        
        output += '    BruterList *result = bruter_parse(context, embedded_code, NULL);\n';
        output += '    bruter_free(result);\n';
        output += '    bruter_free(context);\n';
        output += '    return EXIT_SUCCESS;\n}\n';
        
        fs.writeFileSync(outputPath, output);
    };

    var generateOutputFeraw = function(outputPath, data) {
        var otherLines = data.otherLines;
        var joinedCode = otherLines.join('\n');
        joinedCode = feraw_compile(joinedCode);
        fs.writeFileSync(outputPath, joinedCode);
    };

    // Main execution
    if (process.argv.length < 3) {
        console.error('Usage: ' + path.basename(process.argv[1]) + ' <input.feraw> <output.(c|feraw)>');
        process.exit(1);
    }
    else if (process.argv.length == 3) {
        process.stdout.write(feraw_compile(fs.readFileSync(process.argv[2], 'utf8')));
        process.exit(0);
    }
    var inputFile = path.resolve(process.argv[2]);
    var outputFile = path.resolve(process.argv[3]);

    try {
        // Step 1: Expand includes
        var expandedContent = expandIncludes(inputFile);
        
        // Step 2: Process content
        var processed = processContent(expandedContent);
        
        // Step 3: Decide output based on extension
        if (outputFile.indexOf('.c') === outputFile.length - 2) {
            generateOutputC(outputFile, processed);
        } else if (outputFile.indexOf('.feraw') === outputFile.length - 6) {
            generateOutputFeraw(outputFile, processed);
        } else {
            throw new Error("Unsupported output extension, use .c or .feraw");
        }
        
        console.log('Successfully generated: ' + outputFile);
    } catch (err) {
        console.error('Error: ' + err.message);
        process.exit(1);
    }
}
