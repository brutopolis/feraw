#include "bruter.h"

function(feraw_drop)
{
    bruter_pop_pointer(stack);
}

function(feraw_eval)
{
    BruterList* context = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    char* code = NULL;
    BruterList* splited = NULL;
    switch (value.type)
    {
        case BRUTER_TYPE_LIST:
            splited = (BruterList*)value.value.p;
            break;
        case BRUTER_TYPE_BUFFER:
            code = (char*)value.value.p;
            break;
        default:
            fprintf(stderr, "ERROR: cannot eval, expected buffer or any type, got %d\n", value.type);
            exit(EXIT_FAILURE);
    }
    bruter_interpret(context, code, splited, stack);
}
