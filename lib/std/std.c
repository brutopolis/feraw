#include "bruter.h"

function(feraw_drop)
{
    bruter_pop_pointer(stack);
}

function(feraw_eval)
{
    BruterList* context = bruter_pop_pointer(stack);
    char* code = (char*)bruter_pop_pointer(stack);
    BruterList* splited = bruter_pop_pointer(stack);
    BruterList* prog_stack = bruter_pop_pointer(stack);
    bruter_interpret(context, code, splited, prog_stack);
}
