#!/usr/bin/env node

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
        tokens.push(',' + str.replace(/ /g, '\\s'));
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

function feraw_expand_all(input, depth = 0)
{
    // Prevent infinite recursion
    if (depth > 128) {
        console.warn('Maximum expansion depth reached, stopping to prevent infinite recursion');
        return input;
    }
    
    let previousInput = input;
    input = feraw_expand_props(input);
    
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
        let result = [];
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

        for (let i = 0; i < result.length; i++) 
        {
            result[i] = result[i].reverse();
        }

        // rverse the lines to have the correct order
        let result_string = result.map(cmd => cmd.join(' ')).join('\n');
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