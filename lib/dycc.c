#include "bruter.h"
#include <libtcc.h>

static BruterList *dycc_state_list = NULL;

static const char* bruter_header = "#include \"bruter.h\"\n";

function(feraw_dycc_clear_states)
{
    while (dycc_state_list && dycc_state_list->size > 0)
    {
        TCCState *state = (TCCState *) bruter_shift(dycc_state_list).p;
        tcc_delete(state);
    }
}

function(feraw_dycc_compile)
{
    BruterList* context = bruter_pop_pointer(stack);
    char* codeblock = bruter_pop_pointer(stack);
    

    TCCState *tcc = tcc_new();
    if (tcc == NULL)
    {
        fprintf(stderr, "ERROR: Failed to initialize TCC\n");
        exit(EXIT_FAILURE);
    }

    tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);

    size_t code_size = strlen(bruter_header) + strlen(codeblock) + 2;
    char *code = malloc(code_size);
    if (code == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed for TCC code buffer\n");
        exit(EXIT_FAILURE);
    }

    strcpy(code, bruter_header);
    strcat(code, "\n");
    strcat(code, codeblock);
    if (tcc_compile_string(tcc, code) < 0)
    {
        fprintf(stderr, "ERROR: Could not compile code string\n");
        free(code);
        exit(EXIT_FAILURE);
    }
    
    if (tcc_relocate(tcc) < 0)
    {
        fprintf(stderr, "ERROR: Could not relocate compiled code\n");
        free(code);
        exit(EXIT_FAILURE);
    }

    char *token = code;
    while (*token)
    {
        token = strstr(token, "function(");
        if (!token) break;

        token += 9; // skip "function("
        char *end = strchr(token, ')');
        if (!end) break;

        char *symbol = strndup(token, end - token);
        if (symbol == NULL)
        {
            fprintf(stderr, "ERROR: Memory allocation failed for symbol name\n");
            free(code);
            exit(EXIT_FAILURE);
        }

        void *func = tcc_get_symbol(tcc, symbol);
        if (func == NULL)
        {
            fprintf(stderr, "ERROR: Could not obtain symbol '%s'\n", symbol);
            free(symbol);
            free(code);
            exit(EXIT_FAILURE);
        }

        bruter_push_pointer(dycc_state_list, tcc, NULL, BRUTER_TYPE_ANY);
        bruter_push_pointer(context, func, symbol, BRUTER_TYPE_FUNCTION);

        free(symbol);
        token = end + 1;
    }

    free(code);
}

static void _terminate_tcc_at_exit_handler()
{
    feraw_dycc_clear_states(NULL);
    if (dycc_state_list)
    {
        bruter_free(dycc_state_list);
        dycc_state_list = NULL;
    }
}