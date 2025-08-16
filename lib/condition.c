#include "bruter.h"

function(feraw_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a == b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_not_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a != b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_greater)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a > b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_greater_equal)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a >= b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_less)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a < b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_less_equal)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a <= b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_and)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a && b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_or)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a || b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}

function(feraw_includes)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a || b ? 1 : 0, NULL, BRUTER_TYPE_ANY);
}