#include "bruter.h"

function(feraw_condition_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a == b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_condition_not_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a != b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_condition_greater_than)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a > b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_condition_less_than)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a < b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

init(condition)
{
    bruter_push_pointer(context, feraw_condition_equals, "equals", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_condition_not_equals, "not_equals", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_condition_greater_than, "greater", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_condition_less_than, "less", BRUTER_TYPE_FUNCTION);
}