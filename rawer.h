#ifndef RAWER_H
#define RAWER_H 1

#include <bruter.h>

#include <ctype.h>

#define RAWER_VERSION "0.0.8"

enum {
    BR_TYPE_NULL = 0,
    BR_TYPE_ANY,
    BR_TYPE_FLOAT,
    BR_TYPE_BUFFER,
    BR_TYPE_LIST,
    BR_TYPE_FUNCTION,
};

#define function(name) \
    void name(BruterList *stack)

#define init(name) \
    void init_##name(BruterList *context)

typedef void (*Function)(BruterList *stack);

static inline void clear_context(BruterList *context)
{
    for (BruterInt i = 0; i < context->size; i++)
    {
        switch (context->types[i])
        {
            case BR_TYPE_BUFFER:
                free(context->data[i].p);
                break;
            case BR_TYPE_LIST:
                bruter_free((BruterList*)context->data[i].p);
                break;
            case BR_TYPE_FUNCTION:
                // No need to free function pointers
                break;
            default:
                // For other types, no specific cleanup is needed
                break;
        }

        if (context->keys && context->keys[i])
        {
            free(context->keys[i]); // Free the key if it was allocated
            context->keys[i] = NULL; // Set to NULL to avoid dangling pointers
        }
    }
    context->size = 0; // Reset the size to 0
}

static inline BruterList* parse(BruterList *context, char* input_str)
{
    BruterList *stack = bruter_new(8, true, true);
    BruterList *splited = bruter_new(8, false, false);
    char* original_str = strdup(input_str); // Duplicate the input string to avoid modifying the original
    char* token = strtok(original_str, "\n\t\r ");
    while (token != NULL)
    {
        bruter_push_pointer(splited, token, NULL, 0);
        token = strtok(NULL, "\n\t\r ");
    }

    for (BruterInt i = 0; i < splited->size; i++)
    {
        char* token = bruter_get_pointer(splited, i);
        if (token == NULL || token[0] == '\0') continue; // Skip empty tokens
        
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) // number
        {
            if (token[0] == '0' && token[1] == 'x') // hex
            {
                bruter_push_int(stack, strtol(token+2, NULL, 16), NULL, BR_TYPE_ANY);
            }
            else if (token[0] == '0' && token[1] == 'b') // bin
            {
                bruter_push_int(stack, strtol(token+2, NULL, 2), NULL, BR_TYPE_ANY);
            }
            else if (token[0] == '0' && token[1] == 'o') // oct
            {
                bruter_push_int(stack, strtol(token+2, NULL, 8), NULL, BR_TYPE_ANY);
            }
            else if (strchr(token, '.')) // float
            {
                bruter_push_float(stack, strtof(token, NULL), NULL, BR_TYPE_FLOAT);
            }
            else // int
            {
                bruter_push_int(stack, strtol(token, NULL, 10), NULL, BR_TYPE_ANY);
            }
        }
        else if (token[0] == '!')
        {
            Function func = bruter_pop_pointer(stack);
            func(stack);
        }
        else if (token[0] == '>') // skip
        {
            i += bruter_pop_int(stack);
        }
        else if (token[0] == '<') // back
        {
            i -= bruter_pop_int(stack);
            if (i < 0) i = 0; // Prevent going out of bounds
        }
        else if (token[0] == ';') // break
        {
            i = splited->size + 1; // Break the loop
        }
        else if (token[0] == ',') // goto
        {
            BruterInt target = bruter_pop_int(stack);
            if (target < 0 || target >= splited->size)
            {
                printf("WARNING: Go to index out of bounds: %ld\n", target);
            }
            i = target - 1; // Set the word index to the target
        }
        else if (token[0] == '#') // string
        {
            char* str = strdup(token + 1);
            for (char* p = str; *p; p++) 
            {
                if (*p == '\x14') *p = '\n'; // Replace ASCII 20 with newline
                else if (*p == '\x15') *p = '\r'; // Replace ASCII 21 with carriage return
                else if (*p == '\x16') *p = '\t'; // Replace ASCII 22 with tab
                else if (*p == '\x17') *p = ' '; // Replace ASCII 23 with space
                else if (*p == '\x18') *p = ':'; // Replace ASCII 24 with colon
            }
            bruter_push_pointer(stack, str, NULL, BR_TYPE_BUFFER);
        } 
        else 
        {
            BruterInt found = bruter_find_key(context, token);
            if (found != -1)
            {
                BruterMetaValue meta = bruter_get_meta(context, found);
                meta.key = NULL; // we don't need the key here
                bruter_push_meta(stack, meta);
            }
            else
            {
                // If not found
                printf("WARNING: Variable '%s' not found in context\n", token);
                // We can still push a null value to the stack
                bruter_push_int(stack, 0, NULL, BR_TYPE_NULL);
            }
        }
    }
    bruter_free(splited); // Free the temporary list
    free(original_str); // free the original string
    return stack;
}

#endif // RAWER_H macro