// all comments beside this one been written by AI;
// Function to split input string by a character, respecting string literals, comments, and nested structures
function splitOutsideStrings(input, char = ';') 
{
    // Initialize array to store the resulting parts and a string for the current part being built
    let parts = [];
    let current = '';
    // Flag to track if the parser is currently inside a string literal
    let inString = false;
    // Flag to track if the next character is escaped
    let escape = false;

    // Iterate through each character in the input string
    for (let i = 0; i < input.length; i++) 
    {
        // Store the current character for convenience
        let c = input[i];

        // Handle escaped characters
        if (escape) 
        {
            // Add the escaped character to the current part
            current += c;
            // Reset the escape flag
            escape = false;
            // Continue to the next character
            continue;
        }

        // Check if the current character is an escape character
        if (c === '\\') 
        {
            // Add the escape character to the current part
            current += c;
            // Set the escape flag for the next character
            escape = true;
            // Continue to the next character
            continue;
        }

        // Check if the current character is a double quote (string delimiter)
        if (c === '"') 
        {
            // Toggle the inString flag (entering or exiting a string)
            inString = !inString;
            // Add the quote character to the current part
            current += c;
            // Continue to the next character
            continue;
        }

        // Check if the current character is an opening curly brace (block start)
        if (c === '{') 
        {
            // Initialize a counter for nested block depth
            let blockDepth = 1;
            // Add the opening brace to the current part
            current += c;
            // Increment the loop index to move past the opening brace
            i++;

            // Loop until the matching closing brace is found or end of input
            while (i < input.length && blockDepth > 0) 
            {
                // Check for nested opening braces
                if (input[i] === '{') 
                {
                    // Increase the nesting depth
                    blockDepth++;
                } 
                // Check for closing braces
                else if (input[i] === '}') 
                {
                    // Decrease the nesting depth
                    blockDepth--;
                }

                // Add the current character to the part being built
                current += input[i];
                // Move to the next character
                i++;
            }

            // Adjust the loop index back by one to account for the outer loop's increment
            i--; 
            // Continue to the next character in the outer loop
            continue;
        }
        // Check if the current character is an opening or closing parenthesis (function call)
        else if (c === '(' || c === ')') 
        {
            // Initialize a counter for parenthesis depth (1 for '(', -1 for ')')
            let parenDepth = c === '(' ? 1 : -1;
            // Add the parenthesis to the current part
            current += c;
            // Increment the loop index to move past the parenthesis
            i++;

            // Loop until the parenthesis are balanced (depth is 0) or end of input
            while (i < input.length && parenDepth !== 0) 
            {
                // Check for opening parentheses
                if (input[i] === '(') 
                {
                    // Increase the nesting depth
                    parenDepth++;
                } 
                // Check for closing parentheses
                else if (input[i] === ')') 
                {
                    // Decrease the nesting depth
                    parenDepth--;
                }

                // Add the current character to the part being built
                current += input[i];
                // Move to the next character
                i++;
            }

            // Adjust the loop index back by one to account for the outer loop's increment
            i--; 
            // Continue to the next character in the outer loop
            continue;
        }
        // Check if the current character is an opening or closing square bracket (list)
        else if (c === '[' || c === ']') 
        {
            // Initialize a counter for list depth (1 for '[', -1 for ']')
            let listDepth = c === '[' ? 1 : -1;
            // Add the bracket to the current part
            current += c;
            // Increment the loop index to move past the bracket
            i++;

            // Loop until the brackets are balanced (depth is 0) or end of input
            while (i < input.length && listDepth !== 0) 
            {
                // Check for opening brackets
                if (input[i] === '[') 
                {
                    // Increase the nesting depth
                    listDepth++;
                } 
                // Check for closing brackets
                else if (input[i] === ']') 
                {
                    // Decrease the nesting depth
                    listDepth--;
                }

                // Add the current character to the part being built
                current += input[i];
                // Move to the next character
                i++;
            }

            // Adjust the loop index back by one to account for the outer loop's increment
            i--; 
            // Continue to the next character in the outer loop
            continue;
        }
        // Check if the current characters form a single-line comment (//)
        else if(c === '/' && input[i + 1] === '/') 
        { 
            // Add characters to the current part until a newline is found
            while (i < input.length && input[i] !== '\n') 
            {
                current += input[i];
                i++;
            }
            // Add the newline character to preserve line breaks
            current += '\n'; 
            // Continue to the next character in the outer loop
            continue;
        }
        // Check if the current characters form a multi-line comment (/* ... */)
        else if(c === '/' && input[i + 1] === '*') 
        { 
            // Add the opening comment characters to the current part
            current += c; 
            current += input[i + 1]; 
            // Skip the '/*' characters
            i += 2; 

            // Loop until the closing comment characters are found or end of input
            while (i < input.length) 
            {
                // Add the current character to the part
                current += input[i];

                // Check if the current characters form the closing comment sequence
                if (input[i] === '*' && input[i + 1] === '/') 
                {
                    // Add the closing comment characters to the part
                    current += '/'; 
                    current += input[i + 1]; 
                    // Skip the '*/' characters
                    i += 2; 
                    // Break out of the comment parsing loop
                    break;
                }
                // Move to the next character
                i++;
            }
            // Increment the loop index to account for the outer loop's increment
            i++;
            // Continue to the next character in the outer loop
            continue;
        }

        // Check if the current character is the split character and not inside a string
        if (c === char && !inString) 
        {
            // Add the completed part to the parts array (trimmed of whitespace)
            parts.push(current.trim());
            // Reset the current part string
            current = '';
            // Continue to the next character
            continue;
        }

        // Add the current character to the part being built
        current += c;
    }

    // After the loop, add any remaining content in 'current' to the parts array
    if (current.trim() !== '') 
    {
        parts.push(current.trim());
    }

    // Return the array of split parts
    return parts;
}

// Function to convert an input string into an array of tokens
function tokenize(input) 
{
    // Initialize an array to store the resulting tokens
    let tokens = [];
    // Initialize an index to track the current position in the input string
    let i = 0;
    // Define maximum limits for safety checks to prevent infinite loops
    const MAX_TOKENS = 1e6;
    const MAX_DEPTH = 1000;

    // Helper function to skip over whitespace and comments in the input
    function skipWhitespace() 
    {
        // Initialize a safety counter for loop bounds
        let safety = 0;

        // Loop while the current character is whitespace or part of a comment
        while (i < input.length) 
        {
            // Increment safety counter and check for loop limit
            if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: loop exceeded safe bounds");

            // Check for standard whitespace characters
            if (/\s/.test(input[i])) 
            {
                i++;
            } 
            // Check for single-line comments (//)
            else if (input[i] === '/' && input[i + 1] === '/') 
            {
                // Skip the '//' characters
                i += 2;

                // Skip characters until a newline or end of input is reached
                while (i < input.length && input[i] !== '\n') 
                {
                    // Increment safety counter and check for comment loop limit
                    if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: comment loop too long");
                    i++;
                }
            } 
            // Check for multi-line comments (/* ... */)
            else if (input[i] === '/' && input[i + 1] === '*') 
            {
                // Skip the '/*' characters
                i += 2;

                // Skip characters until the closing '*/' sequence is found
                while (i < input.length && !(input[i] === '*' && input[i + 1] === '/')) 
                {
                    // Increment safety counter and check for block comment loop limit
                    if (++safety > MAX_TOKENS) throw new Error("skipWhitespace: block comment loop too long");
                    i++;
                }

                // If not at the end of input, skip the closing '*/' characters
                if (i < input.length) i += 2;
            } 
            // If none of the above, break the loop (non-whitespace, non-comment character found)
            else 
            {
                break;
            }
        }
    }

    // Helper function to parse a string literal token
    function parseString() 
    {
        // Initialize an empty string to build the parsed string content
        let str = '';
        // Skip the opening double quote character
        i++; 
        // Initialize a safety counter for loop bounds
        let safety = 0;

        // Loop until the closing double quote is found or end of input
        while (i < input.length) 
        {
            // Increment safety counter and check for loop limit
            if (++safety > MAX_TOKENS) throw new Error("parseString: unterminated string");

            // Check for the closing double quote
            if (input[i] === '"') 
            {
                // Skip the closing quote
                i++;
                // Break out of the string parsing loop
                break;
            }

            // Handle special characters within the string
            if (input[i] === '\n') 
            {
                // Replace newline with a special control character
                str += '\x14';
            }
            else if (input[i] === '\r') 
            {
                // Replace carriage return with a special control character
                str += '\x15';
            }
            else if (input[i] === '\t') 
            {
                // Replace tab with a special control character
                str += '\x16';
            }
            else if (input[i] === ' ') 
            {
                // Replace space with a special control character
                str += '\x17';
            }
            else if (input[i] === ':') 
            {
                // Replace colon with a special control character
                str += '\x18';
            }
            // Check for escape sequences
            else if (input[i] === '\\') 
            {
                // Skip the backslash
                i++;
                // Store the escaped character
                const esc = input[i++];
                // Handle common escape sequences
                if (esc === 'n') 
                {
                    str += '\n';
                }
                else if (esc === 't') 
                {
                    str += '\t';
                }
                else if (esc === '"') 
                {
                    str += '"';
                }
                else if (esc === '\\') 
                {
                    str += '\\';
                }
                // If not a recognized escape, add the character as-is
                else 
                {
                    str += esc;
                }
                // Continue to the next character in the outer loop
                continue;
            } 
            // If not a special character or escape, add the character directly
            else 
            {
                str += input[i];
            }

            // Move to the next character
            i++;
        }

        // Check if the string was properly terminated
        if (safety >= MAX_TOKENS) throw new Error("String not terminated");

        // Add the parsed string (prefixed with '#') to the tokens array
        tokens.push('#' + str);
    }

    // Helper function to parse a list token (enclosed in square brackets)
    function parseList(depth = 0) 
    {
        // Check for maximum nesting depth to prevent stack overflow
        if (depth > MAX_DEPTH) throw new Error("Max list nesting exceeded");

        // Skip the opening square bracket '['
        i++; 
        // Initialize a temporary array to store tokens within the list
        let tempTokens = [];
        // Initialize a counter for the number of items in the list
        let itemCount = 0;
        // Initialize a safety counter for loop bounds
        let safety = 0;

        // Loop indefinitely until the closing bracket ']' is found
        while (true) 
        {
            // Increment safety counter and check for loop limit
            if (++safety > MAX_TOKENS) throw new Error("parseList: unterminated list");

            // Skip any whitespace or comments before the next item
            skipWhitespace();

            // Check for unexpected end of input
            if (i >= input.length) throw new Error("parseList: unexpected end of input");

            // Check for the closing square bracket ']'
            if (input[i] === ']') 
            {
                // Skip the closing bracket
                i++;
                // Break out of the list parsing loop
                break;
            }

            // Save the current tokens array and temporarily clear it
            let saved = tokens;
            tokens = [];

            // Recursively parse the next expression (list item)
            parseExpr(depth + 1);

            // Add the tokens generated from parsing the item to the temporary array
            tempTokens.push(...tokens);

            // Increment the item count
            itemCount++;

            // Restore the original tokens array
            tokens = saved;

            // Skip any whitespace or comments after the item
            skipWhitespace();

            // Check for a comma separating list items
            if (input[i] === ',') 
            {
                // Skip the comma
                i++;
            }
        }

        // Add list-specific tokens to the main tokens array:
        // '!' indicates a special structure
        // 'list' is the type identifier
        // itemCount is the number of items in the list
        // tempTokens contains the tokens of all list items
        tokens.push('!', 'list', itemCount.toString(), ...tempTokens);
    }

    // Placeholder function for parsing block structures (currently unused)
    function parseBlock(depth = 0)
    {
        // To be used in future, for something I don't know yet
    }

    // Helper function to parse a raw token (a sequence of non-whitespace, non-special characters)
    function parseRawToken() 
    {
        // Record the starting index of the token
        let start = i;

        // Loop while the current character is not whitespace and not a special delimiter
        while (i < input.length && !/\s/.test(input[i]) && !"()[]{},=;".includes(input[i])) 
        {
            // Move to the next character
            i++;
        }

        // Return the substring from the start index to the current index
        return input.slice(start, i);
    }

    // Main recursive function to parse expressions
    function parseExpr(depth = 0) 
    {
        // Check for maximum nesting depth to prevent stack overflow
        if (depth > MAX_DEPTH) throw new Error("Max expression nesting exceeded");

        // Skip any leading whitespace or comments
        skipWhitespace();

        // Check for end of input
        if (i >= input.length) return;

        // Check if the current character is a double quote (start of a string)
        if (input[i] === '"') 
        {
            // Parse the string literal and return
            return parseString();
        }

        // Check if the current character is an opening square bracket (start of a list)
        if (input[i] === '[') 
        {
            // Parse the list and return
            return parseList(depth);
        }

        // Check for special number formats starting with '0' (e.g., 0x, 0b, 0o)
        if (input[i] === '0') 
        {
            // Record the starting index of the number
            let start = i;
            // Skip the '0'
            i++;

            // Continue reading characters that could be part of the number
            while (
                i < input.length &&
                !/\s|[\]\[\(\)\{\},]/.test(input[i]) 
            ) 
            {
                i++;
            }

            // Extract the number string
            let numStr = input.slice(start, i);
            // Attempt to convert the string to a JavaScript number
            let num = Number(numStr);

            // Check if the conversion was successful
            if (isNaN(num)) throw new Error("parseExpr: invalid number format: " + numStr);

            // Add the number (as a string) to the tokens array
            tokens.push(num + '');
            // Return after parsing the number
            return;
        }

        // Parse a raw token (likely an identifier or keyword)
        let name = parseRawToken();

        // Check if the token is invalid or empty
        if (!name) throw new Error("parseExpr: invalid or empty token");

        // Skip any whitespace after the token
        skipWhitespace();

        // Check for end of input again
        if (i >= input.length) 
        {
            // Add the token to the array and return
            tokens.push(name);
            return;
        }

        // Check if the next character is an opening parenthesis (function call)
        if (input[i] === '(') 
        {
            // Special handling for certain operators
            if (["!", "?"].includes(name)) 
            {
                // Add the operator name directly
                tokens.push(name);
            } 
            else 
            {
                // Add '!' and the function name to indicate a function call
                tokens.push('!', name);
            }

            // Skip the opening parenthesis
            i++; 
            // Initialize a safety counter for loop bounds
            let safety = 0;

            // Loop to parse function arguments
            while (true) 
            {
                // Increment safety counter and check for loop limit
                if (++safety > MAX_TOKENS) throw new Error("parseExpr: function call too long");

                // Skip whitespace before the next argument
                skipWhitespace();

                // Check for unexpected end of input
                if (i >= input.length) throw new Error("Function call not closed with )");

                // Check for the closing parenthesis
                if (input[i] === ')') 
                {
                    // Skip the closing parenthesis and break the loop
                    i++;
                    break;
                }

                // Recursively parse the next argument expression
                parseExpr(depth + 1);

                // Skip whitespace after the argument
                skipWhitespace();

                // Check for a comma separating arguments
                if (input[i] === ',') 
                {
                    // Skip the comma
                    i++;
                }
            }
        } 
        // Handle other complex expressions (indexing, assignment)
        else 
        {
            // Example patterns handled:
            // a[1][2][3][4][5](55, 77, 99, 11 , 33);
            // a[1][2](55, 77, 99, 11 , 33)[3][4][5];
            // a[1][2][3][4][5] = 11;
            // a[1][2][3][4][5](55, 77, 99, 11 , 33) = 1;

            // Start building the expression tokens with the initial name
            let exprTokens = [name];

            // Loop to handle potential indexing '[]' or function calls '()'
            while (true) 
            {
                // Skip any whitespace
                skipWhitespace();

                // Check for a function call parenthesis
                if (input[i] === '(') 
                {
                    // Skip the opening parenthesis
                    i++; 
                    // Initialize an array to store argument tokens
                    let argTokens = [];
                    // Initialize a safety counter for loop bounds
                    let safety = 0;

                    // Loop to parse function arguments
                    while (true) 
                    {
                        // Increment safety counter and check for loop limit
                        if (++safety > MAX_TOKENS) throw new Error("parseExpr: function call too long");

                        // Skip whitespace before the next argument
                        skipWhitespace();

                        // Check for unexpected end of input
                        if (i >= input.length) throw new Error("Function call not closed with )");

                        // Check for the closing parenthesis
                        if (input[i] === ')') 
                        {
                            // Skip the closing parenthesis and break the argument loop
                            i++;
                            break;
                        }

                        // Recursively parse the argument expression
                        parseExpr(depth + 1);

                        // Extract the tokens generated for the argument and add them to argTokens
                        argTokens.push(...tokens.splice(tokens.length - 1));

                        // Skip whitespace after the argument
                        skipWhitespace();

                        // Check for a comma separating arguments
                        if (input[i] === ',') 
                        {
                            // Skip the comma
                            i++;
                        }
                    }

                    // Update exprTokens to represent the function call structure
                    exprTokens = ['!', ...exprTokens, ...argTokens];
                    // Continue the outer loop to check for more indexing or calls
                    continue;
                }

                // Check for array indexing brackets
                if (input[i] === '[') 
                {
                    // Skip the opening bracket
                    i++; 
                    // Skip whitespace inside the brackets
                    skipWhitespace();

                    // Recursively parse the index expression
                    parseExpr(depth + 1);

                    // Extract the token generated for the index
                    let indexToken = tokens.splice(tokens.length - 1);

                    // Skip whitespace after the index expression
                    skipWhitespace();

                    // Check for the closing bracket
                    if (input[i] !== ']') throw new Error("parseExpr: missing closing ]");

                    // Skip the closing bracket
                    i++; 

                    // Update exprTokens to represent the indexing operation
                    exprTokens = ['!', 'get', ...exprTokens, ...indexToken];
                    // Continue the outer loop to check for more indexing or calls
                    continue;
                }

                // If neither '(' nor '[', break the loop
                break;
            }

            // Skip any whitespace after the complex expression
            skipWhitespace();

            // Check for an assignment operator
            if (input[i] === '=') 
            {
                // Skip the '=' character
                i++; 
                // Skip whitespace after '='
                skipWhitespace();

                // Recursively parse the value expression being assigned
                parseExpr(depth + 1);

                // Extract the token(s) for the assigned value
                let value = tokens.splice(tokens.length - 1);

                // Add tokens representing the assignment operation
                tokens.push('!', 'set', ...value, ...exprTokens);
                // Return after handling the assignment
                return;
            }

            // If not a function call or assignment, add the accumulated expression tokens
            tokens.push(...exprTokens);
        }
    }

    // Main loop to parse the entire input string into tokens
    let safety = 0;
    while (i < input.length) 
    {
        // Increment safety counter and check for loop limit
        if (++safety > MAX_TOKENS) throw new Error("Main loop exceeded safe bounds");

        // Skip any leading whitespace or comments
        skipWhitespace();

        // Check for end of input
        if (i >= input.length) break;

        // Record the starting index for potential identifier parsing
        let start = i;
        // Parse a potential identifier token
        let name = parseRawToken();

        // Skip whitespace after the identifier
        skipWhitespace();

        // Check if the next character is an assignment operator (definition)
        if (input[i] === '=') 
        {
            // Skip the '=' character
            i++;
            // Skip whitespace after '='
            skipWhitespace();

            // Add special tokens indicating a definition context
            tokens.push("!", "define", "context", "!", "rename");

            // Parse the expression on the right-hand side of the assignment
            parseExpr();

            // Add the identifier name (prefixed with '#') as the final part of the definition
            tokens.push("#" + name);
        } 
        // If not a definition, parse it as a regular expression
        else 
        {
            // Reset the index to the start of the potential identifier
            i = start;
            // Parse the expression
            parseExpr();
        }
    }

    // Return the final array of tokens
    return tokens;
}

// Function to process labels in the tokenized input
function feraw_labelparser(original_input) 
{
    // Reconstruct the original input string from tokens to find label positions
    let unreversed_input = original_input.map(tokens => tokens.join(' ')).join(' ');

    // Split the reconstructed string by whitespace to get individual tokens
    let splited = unreversed_input.toString().split(/\s+/);

    // Reverse the tokens within each command and join with newlines (purpose unclear from name)
    let input = original_input.map(tokens => tokens.reverse().join(' '))
        .join('\n').toString();

    // Remove any empty strings from the split tokens
    splited = splited.filter(token => token.trim() !== '');

    // Initialize an array to store found labels and their positions
    let labels = [];
    // Initialize a correction counter for position adjustments
    let correction = 0;

    // Iterate through the split tokens to find labels (ending with ':')
    for (let i = 0; i < splited.length; i++)
    {
        // Get the current token
        let word = splited[i];

        // Check if the token ends with a colon (indicating a label)
        if (word.endsWith(':')) 
        {
            // Extract the label name by removing the colon
            let label = word.slice(0, -1);

            // Store the label name and its adjusted position
            labels.push([label, i - correction]);

            // Increment the correction counter
            correction++;
        }
    }

    // Remove all 'label:' occurrences from the input string
    input = input.replaceAll(/(\w+):/g, '');

    // Replace each label name in the input with its corresponding position index
    for (let label of labels) 
    {
        // Use a regular expression to replace the label name with its index
        input = input.replaceAll(new RegExp(`\\b${label[0]}\\b`, 'g'), `${label[1]}`);
    }

    // Return the processed input string with labels replaced by indices
    return input;
}

// Function to expand macro definitions and calls within the input string
function expandMacros(input) 
{
    // Create a map to store macro names and their corresponding bodies
    const macroMap = new Map();

    // --- Helper function to find the matching closing character for a given opening character ---
    function findMatching(input, start, openChar, closeChar) 
    {
        // Initialize depth counter (1 because we start after the opening character)
        let depth = 1;
        // Flag to track if currently inside a string literal
        let inString = false;
        // Variable to store the current string delimiter (' or ")
        let stringChar = '';
        // Flag to track if the next character is escaped
        let escapeNext = false;

        // Iterate through the input string starting from the character after 'start'
        for (let i = start + 1; i < input.length; i++) 
        {
            // Store the current character
            let char = input[i];

            // Handle escaped characters
            if (escapeNext) 
            {
                // Reset the escape flag and continue to the next character
                escapeNext = false;
                continue;
            }

            // Check if the current character is an escape character
            if (char === '\\') 
            {
                // Set the escape flag for the next character
                escapeNext = true;
                continue;
            }

            // Check if entering or exiting a string literal (and not already in one)
            if (!inString && (char === '"' || char === "'")) 
            {
                // Set the flag and record the string delimiter
                inString = true;
                stringChar = char;
                continue;
            } 
            // Check if exiting a string literal
            else if (inString && char === stringChar) 
            {
                // Reset the flag and clear the delimiter
                inString = false;
                stringChar = '';
                continue;
            }

            // Skip delimiters if currently inside a string
            if (inString) 
            {
                continue;
            }

            // Check for nested opening characters
            if (char === openChar) 
            {
                // Increase the nesting depth
                depth++;
            } 
            // Check for closing characters
            else if (char === closeChar) 
            {
                // Decrease the nesting depth
                depth--;

                // If depth reaches 0, the matching closing character is found
                if (depth === 0) 
                {
                    // Return the index of the matching character
                    return i;
                }
            }
        }

        // Return -1 if no matching character is found
        return -1;
    }

    // --- Step 1: Extract and Store Macro Definitions (MODIFIED to use macro(...)) ---
    // Initialize loop index and a string to store input without macro definitions
    let i = 0;
    let outputWithoutDefs = '';

    // Loop through the entire input string
    while (i < input.length) 
    {
        // --- Basic string handling for definition parsing ---
        // Check if the current character is a string delimiter
        if (input[i] === '"' || input[i] === "'") 
        {
            // Store the string delimiter
            let stringChar = input[i];
            // Add the opening delimiter to the output
            outputWithoutDefs += input[i];
            // Move to the next character
            i++;

            // Initialize a flag for escape sequence handling within the string
            let escapeNext = false;

            // Loop to copy the contents of the string literal
            while (i < input.length) 
            {
                // Handle escaped characters within the string
                if (escapeNext) 
                {
                    outputWithoutDefs += input[i];
                    escapeNext = false;
                    i++;
                    continue;
                }

                // Check for escape character within the string
                if (input[i] === '\\') 
                {
                    outputWithoutDefs += input[i];
                    escapeNext = true;
                    i++;
                    continue;
                }

                // Check for the closing string delimiter
                if (input[i] === stringChar) 
                {
                    // Add the closing delimiter to the output
                    outputWithoutDefs += input[i];
                    // Move past the closing delimiter
                    i++;
                    // Break out of the string copying loop
                    break;
                }

                // Add the current character to the output
                outputWithoutDefs += input[i];
                // Move to the next character
                i++;
            }
            // Continue to the next iteration of the main input loop
            continue;
        }

        // --- Skip whitespace and comments for definition parsing ---
        // Check for whitespace characters
        if (/\s/.test(input[i])) 
        {
            // Add the whitespace to the output
            outputWithoutDefs += input[i];
            // Move to the next character
            i++;
            // Continue to the next iteration of the main input loop
            continue;
        }

        // Check for potential comments
        if (input[i] === '/' && i + 1 < input.length) 
        {
            // Check for single-line comment
            if (input[i + 1] === '/') 
            {
                // Copy characters until a newline is found
                while (i < input.length && input[i] !== '\n') 
                {
                    outputWithoutDefs += input[i];
                    i++;
                }

                // If not at the end of input, add the newline and move past it
                if (i < input.length) 
                {
                    outputWithoutDefs += input[i];
                    i++;
                }
                // Continue to the next iteration of the main input loop
                continue;
            } 
            // Check for multi-line comment
            else if (input[i + 1] === '*') 
            {
                // Add the opening comment characters to the output
                outputWithoutDefs += input[i]; i++;
                outputWithoutDefs += input[i]; i++;

                // Copy characters until the closing comment sequence is found
                while (i < input.length) 
                {
                    // Check for the closing comment sequence
                    if (input[i] === '*' && i + 1 < input.length && input[i + 1] === '/') 
                    {
                        // Add the closing comment characters to the output
                        outputWithoutDefs += input[i]; i++;
                        outputWithoutDefs += input[i]; i++;
                        // Break out of the comment copying loop
                        break;
                    }

                    // Add the current character to the output
                    outputWithoutDefs += input[i];
                    // Move to the next character
                    i++;
                }
                // Continue to the next iteration of the main input loop
                continue;
            }
        }

        // --- MODIFIED: Attempt to Match a Macro Definition: identifier '=' 'macro' '(' ---
        // Record the potential start position of a macro definition
        let potentialStart = i;

        // Use a regular expression to match a potential macro name (identifier)
        let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(input.substring(i));

        // Check if a valid identifier name was found
        if (nameMatch) 
        {
            // Extract the macro name
            let macroName = nameMatch[1];
            // Move the index past the matched name
            i += nameMatch[0].length;

            // Skip any whitespace after the name
            while (i < input.length && /\s/.test(input[i])) i++;

            // Check if the next character is an assignment operator
            if (i < input.length && input[i] === '=') 
            {
                // Skip the '=' character
                i++; 

                // Skip any whitespace after '='
                while (i < input.length && /\s/.test(input[i])) i++;

                // Check for the 'macro' keyword
                if (i + 5 <= input.length && input.substring(i, i + 5) === 'macro') 
                {
                    // Skip the 'macro' keyword
                    i += 5; 

                    // Skip any whitespace after 'macro'
                    while (i < input.length && /\s/.test(input[i])) i++;

                    // Check if the next character is an opening parenthesis
                    if (i < input.length && input[i] === '(') 
                    {
                        // Record the start index of the macro body (after '(')
                        let bodyStart = i + 1;

                        // Find the matching closing parenthesis for the macro definition
                        let bodyEnd = findMatching(input, i, '(', ')'); 

                        // Check if a matching closing parenthesis was found
                        if (bodyEnd !== -1) 
                        {
                            // Extract the macro body (content between parentheses)
                            let macroBody = input.substring(bodyStart, bodyEnd);

                            // Store the macro definition in the map
                            macroMap.set(macroName, macroBody);

                            // Skip the entire definition including the trailing ';'
                            i = bodyEnd + 1; // Move past ')'

                            // Skip any whitespace after the closing parenthesis
                            while (i < input.length && /\s/.test(input[i])) i++;

                            // Check for the trailing semicolon
                            if (i < input.length && input[i] === ';') 
                            {
                                // Skip the semicolon
                                i++; 
                            } 
                            // else maybe warn about missing semicolon?

                            // Do NOT add this definition to outputWithoutDefs
                            // Continue processing the *rest* of the input
                            continue; 
                        } 
                        else 
                        {
                            // Log an error if the macro definition is unterminated
                            console.error("Unterminated macro definition for:", macroName);
                            // Reset the index to re-evaluate from the potential start
                            i = potentialStart;
                        }
                    } 
                    else 
                    {
                        // 'macro' not followed by '(', not a definition
                        // Reset the index to re-evaluate from the potential start
                        i = potentialStart;
                    }
                } 
                else 
                {
                    // '=' not followed by 'macro', not a definition
                    // Reset the index to re-evaluate from the potential start
                    i = potentialStart;
                }
            } 
            else 
            {
                // Name not followed by '=', not a definition
                // Reset the index to re-evaluate from the potential start
                i = potentialStart;
            }
        }

        // Add the current character to the output (it's not part of a macro definition)
        outputWithoutDefs += input[potentialStart];
        // Move the index forward by one
        i = potentialStart + 1;
    }

    // Update the input to be the string without macro definitions
    input = outputWithoutDefs;

    // --- Step 2: Expand Macro Calls (Unchanged) ---
    // Variable to store the input from the previous iteration
    let previous;

    // Loop until no more macro expansions occur (handle nested macro calls)
    do 
    {
        // Store the current input state
        previous = input;
        // Initialize a string to store the input after macro expansion
        let outputAfterExpansion = '';
        // Reset the loop index
        i = 0;

        // --- Main Expansion Loop ---
        // Loop through the input string to find and expand macro calls
        while (i < input.length) 
        {
            // --- Attempt to Match a Macro Call: identifier '(' ---
            // Use a regular expression to match a potential macro call name
            let nameMatch = /^([a-zA-Z_$][a-zA-Z0-9_$]*)/.exec(input.substring(i));

            // Check if a valid identifier name was found
            if (nameMatch) 
            {
                // Extract the potential macro call name
                let callName = nameMatch[1];
                // Calculate the index after the matched name
                let callStart = i + callName.length;

                // --- Check if it's a macro call: name '(' (skip whitespace) ---
                // Initialize a temporary index to check for '('
                let tempIndex = callStart;

                // Skip any whitespace after the name
                while (tempIndex < input.length && /\s/.test(input[tempIndex])) tempIndex++;

                // Check if the next non-whitespace character is an opening parenthesis
                if (tempIndex < input.length && input[tempIndex] === '(') 
                {
                    // Record the start index of the macro call arguments (after '(')
                    let argsStart = tempIndex + 1;

                    // Find the matching closing parenthesis for the macro call
                    let argsEnd = findMatching(input, tempIndex, '(', ')');

                    // Check if a matching closing parenthesis was found
                    if (argsEnd !== -1) 
                    {
                        // Retrieve the macro body from the map
                        const macroBody = macroMap.get(callName);

                        // Check if the macro name exists in the map
                        if (macroBody !== undefined) 
                        {
                            // Extract the arguments string (content between parentheses)
                            let argsStr = input.substring(argsStart, argsEnd);

                            // --- Split Arguments Robustly ---
                            // Define a function to split macro arguments correctly
                            function splitArgsRobust(str) 
                            {
                                // Initialize an array to store the arguments
                                let args = [];
                                // Initialize a string to build the current argument
                                let current = '';
                                // Initialize a depth counter for nested structures
                                let depth = 0;
                                // Flag to track if currently inside an argument string
                                let inArgString = false;
                                // Variable to store the current argument string delimiter
                                let argStringChar = '';
                                // Flag to track if the next character in an argument is escaped
                                let argEscapeNext = false;

                                // Iterate through each character in the arguments string
                                for (let j = 0; j < str.length; j++) 
                                {
                                    // Store the current character
                                    let argChar = str[j];

                                    // Handle escaped characters within arguments
                                    if (argEscapeNext) 
                                    {
                                        current += argChar;
                                        argEscapeNext = false;
                                        continue;
                                    }

                                    // Check for escape character within an argument
                                    if (argChar === '\\') 
                                    {
                                        current += argChar;
                                        argEscapeNext = true;
                                        continue;
                                    }

                                    // Check for entering or exiting an argument string
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

                                    // Skip delimiters if currently inside an argument string
                                    if (inArgString) 
                                    {
                                        current += argChar;
                                        continue;
                                    }

                                    // Check for opening or closing nested structures
                                    if (argChar === '(' || argChar === '[' || argChar === '{') 
                                    {
                                        // Increase nesting depth
                                        depth++;
                                    } 
                                    else if (argChar === ')' || argChar === ']' || argChar === '}') 
                                    {
                                        // Decrease nesting depth
                                        depth--;
                                    }

                                    // Check for argument separator (comma) at the top level
                                    if (argChar === ',' && depth === 0) 
                                    {
                                        // Add the completed argument (trimmed) to the array
                                        args.push(current.trim());
                                        // Reset the current argument string
                                        current = '';
                                    } 
                                    else 
                                    {
                                        // Add the character to the current argument
                                        current += argChar;
                                    }
                                }

                                // Add the final argument (trimmed) if it exists or if the string ends with a comma
                                if (current.trim() !== '' || args.length > 0 || str.endsWith(",")) 
                                {
                                    args.push(current.trim());
                                }

                                // Return the array of split arguments
                                return args;
                            }

                            // Split the arguments string into an array
                            const args = splitArgsRobust(argsStr);

                            // --- Perform Substitution on the Macro Body ---
                            // Start with the original macro body
                            let expanded = macroBody;

                            // 1. Replace $@ (all arguments joined as-is)
                            expanded = expanded.replace(/\$@/g, args.join(', '));

                            // 2. Replace numbered arguments $N from back to front to avoid conflicts
                            for (let idx = args.length - 1; idx >= 0; idx--) 
                            {
                                // Create a regular expression to match the argument placeholder
                                const regExp = new RegExp(`\\$${idx}\\b`, 'g');
                                // Replace the placeholder with the actual argument
                                expanded = expanded.replace(regExp, args[idx]);
                            }

                            // Add the expanded macro body to the output string
                            outputAfterExpansion += expanded;
                            // Move the index past the closing parenthesis of the macro call
                            i = argsEnd + 1; 
                            // Continue processing the rest of the input
                            continue; 
                        }
                    } 
                    else 
                    {
                        // Log an error if the macro call is unterminated
                        console.error("Unterminated macro call for:", callName);
                    }
                }
            }

            // Add the current character to the output if it wasn't the start of a recognized macro call
            outputAfterExpansion += input[i];
            // Move to the next character
            i++;
        }

        // Update the input string with the result of the current expansion pass
        input = outputAfterExpansion;
    } 
    // Repeat the expansion process until no changes occur (no more macros to expand)
    while (previous !== input); 

    // Return the final input string with all macros expanded
    return input;
}

// Main compilation function that orchestrates the parsing process
function feraw_compile(input) 
{
    // First, expand any macros defined in the input
    input = expandMacros(input);

    // Split the input string into individual commands using ';' as the delimiter
    // This respects string literals, comments, and nested structures
    let commands = splitOutsideStrings(input, ';');

    // Initialize an array to store the tokenized results for each command
    let result = [];

    // Iterate through each command
    for (let command of commands) 
    {
        // Check if the command is not empty
        if (command) 
        {
            // Tokenize the command and add the resulting token array to 'result'
            result.push(tokenize(command));
        }
    }

    // Process labels in the tokenized results
    let result_string = feraw_labelparser(result);

    // Return the final processed string
    return result_string;
}