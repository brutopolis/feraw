function splitIgnoringParensAndQuotes(input, delimiterRegex = /[ \t\n\r]+/) {
    const result = [];
    let current = '';
    let parenLevel = 0;
    let inQuotes = false;
    let i = 0;

    while (i < input.length) {
        const c = input[i];

        if (c === '"' && input[i - 1] !== '\\') {
            inQuotes = !inQuotes;
            current += c;
            i++;
        } else if (!inQuotes && c === '(') {
            parenLevel++;
            current += c;
            i++;
        } else if (!inQuotes && c === ')') {
            parenLevel = Math.max(0, parenLevel - 1);
            current += c;
            i++;
        } else if (!inQuotes && parenLevel === 0) {
            const remaining = input.slice(i);
            const match = remaining.match(delimiterRegex);
            if (match && match.index === 0) {
                if (current !== '') {
                    result.push(current);
                    current = '';
                }
                i += match[0].length;
            } else {
                current += c;
                i++;
            }
        } else {
            current += c;
            i++;
        }
    }

    if (current !== '') {
        result.push(current);
    }

    return result;
}


function rawer_preparser(input) 
{
    words = splitIgnoringParensAndQuotes(input);
    for (let i = 0; i < words.length; i++) 
    {
        word = words[i].trim();
        if (word.startsWith('"')) 
        {
            // #abc -> (61 62 63 string !)
            let str = "(";
            for (let j = 1; j < word.length - 1; j++) 
            {
                str += word.charCodeAt(j) + " ";
            }
            str += word.length + " string !)";
            words[i] = str; // Replace the word with the string representation
            
        } 
        else if (word.endsWith('!!')) 
        {
            words[i] = word.slice(0, -2); // Remove '!!' at the end
            words.splice(i + 1, 0, '!!'); // Insert '!!' after the word
            i++;
        } 
        else if (word.endsWith('!')) 
        {
            words[i] = word.slice(0, -1); // Remove '!' at the end
            words.splice(i + 1, 0, '!'); // Insert '!' after the word
            i++;
        }
    }
    words = words.filter(word => word !== ''); // Remove empty strings
    return words;
}

