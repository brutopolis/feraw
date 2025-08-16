#include <bruter.h>
#include <math.h>
#include <time.h>

function(feraw_add)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BRUTER_TYPE_FLOAT:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.f + b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_float(stack, a.value.f + b.value.i, NULL, BRUTER_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.i + b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_int(stack, a.value.i + b.value.i, NULL, BRUTER_TYPE_ANY);
                    break;
            }
            break;
    }
}

function(feraw_sub)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BRUTER_TYPE_FLOAT:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.f - b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_float(stack, a.value.f - b.value.i, NULL, BRUTER_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.i - b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_int(stack, a.value.i - b.value.i, NULL, BRUTER_TYPE_ANY);
                    break;
            }
            break;
    }
}

function(feraw_mul)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BRUTER_TYPE_FLOAT:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.f * b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_float(stack, a.value.f * b.value.i, NULL, BRUTER_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.i * b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_int(stack, a.value.i * b.value.i, NULL, BRUTER_TYPE_ANY);
                    break;
            }
            break;
    }
}

function(feraw_div)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BRUTER_TYPE_FLOAT:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    if (b.value.f == 0.0)
                    {
                        fprintf(stderr, "ERROR: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    bruter_push_float(stack, a.value.f / b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    if (b.value.i == 0)
                    {
                        fprintf(stderr, "ERROR: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    bruter_push_float(stack, a.value.f / b.value.i, NULL, BRUTER_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BRUTER_TYPE_FLOAT:
                    if (b.value.f == 0.0)
                    {
                        fprintf(stderr, "ERROR: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    bruter_push_float(stack, a.value.i / b.value.f, NULL, BRUTER_TYPE_FLOAT);
                    break;
                default:
                    if (b.value.i == 0)
                    {
                        fprintf(stderr, "ERROR: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    bruter_push_int(stack, a.value.i / b.value.i, NULL, BRUTER_TYPE_ANY);
                    break;
            }
            break;
    }
}

function(feraw_mod)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Modulus operator not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    if (b.value.i == 0)
    {
        fprintf(stderr, "ERROR: Division by zero in modulus operation\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i % b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_pow)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        bruter_push_float(stack, pow(a.value.f, b.value.f), NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        bruter_push_int(stack, (BruterInt)pow((double)a.value.i, (double)b.value.i), NULL, BRUTER_TYPE_ANY);
    }
}

function(feraw_sqrt)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type != BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Square root function requires a float argument\n");
        exit(EXIT_FAILURE);
    }
    if (a.value.f < 0.0)
    {
        fprintf(stderr, "ERROR: Cannot compute square root of negative number\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_float(stack, sqrt(a.value.f), NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_abs)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT)
    {
        bruter_push_float(stack, fabs(a.value.f), NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        bruter_push_int(stack, a.value.i < 0 ? -a.value.i : a.value.i, NULL, BRUTER_TYPE_ANY);
    }
}

function(feraw_min)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        double val_a = (a.type == BRUTER_TYPE_FLOAT) ? a.value.f : (double)a.value.i;
        double val_b = (b.type == BRUTER_TYPE_FLOAT) ? b.value.f : (double)b.value.i;
        bruter_push_float(stack, fmin(val_a, val_b), NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        bruter_push_int(stack, (a.value.i < b.value.i) ? a.value.i : b.value.i, NULL, BRUTER_TYPE_ANY);
    }
}

function(feraw_max)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        double val_a = (a.type == BRUTER_TYPE_FLOAT) ? a.value.f : (double)a.value.i;
        double val_b = (b.type == BRUTER_TYPE_FLOAT) ? b.value.f : (double)b.value.i;
        bruter_push_float(stack, fmax(val_a, val_b), NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        bruter_push_int(stack, (a.value.i > b.value.i) ? a.value.i : b.value.i, NULL, BRUTER_TYPE_ANY);
    }
}

function(feraw_sin)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type != BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Sine function requires a float argument\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_float(stack, sin(a.value.f), NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_cos)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type != BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Cosine function requires a float argument\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_float(stack, cos(a.value.f), NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_tan)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type != BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Tangent function requires a float argument\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_float(stack, tan(a.value.f), NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_inc)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT)
    {
        a.value.f += 1.0;
        bruter_push_float(stack, a.value.f, NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        a.value.i += 1;
        bruter_push_int(stack, a.value.i, NULL, BRUTER_TYPE_ANY);
    }
}

function(feraw_dec)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT)
    {
        a.value.f -= 1.0;
        bruter_push_float(stack, a.value.f, NULL, BRUTER_TYPE_FLOAT);
    }
    else
    {
        a.value.i -= 1;
        bruter_push_int(stack, a.value.i, NULL, BRUTER_TYPE_ANY);
    }
}

// random functions

function(feraw_seed)
{
    BruterMeta seed_meta = bruter_pop_meta(stack);
    unsigned int seed;
    if (seed_meta.type == BRUTER_TYPE_FLOAT)
    {
        seed = (unsigned int)seed_meta.value.f;
    }
    else
    {
        seed = (unsigned int)seed_meta.value.i;
    }
    srand(seed);
}

function(feraw_rand)
{
    BruterFloat result = rand();
    bruter_push_float(stack, result, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_random)
{
    BruterMeta min_meta = bruter_pop_meta(stack);
    BruterMeta max_meta = bruter_pop_meta(stack);
    if (min_meta.type == BRUTER_TYPE_FLOAT || max_meta.type == BRUTER_TYPE_FLOAT)
    {
        BruterFloat min = 0, max = 0;
        switch (min_meta.type)
        {
            case BRUTER_TYPE_FLOAT:
                min = min_meta.value.f;
                break;
            default:
                min = (BruterFloat)min_meta.value.i;
                break;
        }

        switch (max_meta.type)
        {
            case BRUTER_TYPE_FLOAT:
                max = max_meta.value.f;
                break;
            default:
                max = (BruterFloat)max_meta.value.i;
                break;
        }

        BruterFloat result = fmod(rand(), (max - min + 1) + min);
        bruter_push_float(stack, result, NULL, BRUTER_TYPE_FLOAT);
    }
    else // definively int
    {
        BruterInt min, max;
        min = min_meta.value.i;
        max = min_meta.value.i;
        BruterInt result = rand() % (max - min + 1) + min;
        bruter_push_int(stack, result, NULL, BRUTER_TYPE_ANY);
    }
}

// rouding functions

function(feraw_floor)
{
    BruterFloat value = bruter_pop_float(stack);
    bruter_push_int(stack, (BruterInt)floor(value), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ceil)
{
    BruterFloat value = bruter_pop_float(stack);
    bruter_push_int(stack, (BruterInt)ceil(value), NULL, BRUTER_TYPE_ANY);
}

function(feraw_round)
{
    BruterFloat value = bruter_pop_float(stack);
    bruter_push_int(stack, (BruterInt)round(value), NULL, BRUTER_TYPE_ANY);
}

function(feraw_trunc)
{
    BruterFloat value = bruter_pop_float(stack);
    bruter_push_int(stack, (BruterInt)trunc(value), NULL, BRUTER_TYPE_ANY);
}

// bitwise operations
function(feraw_bit_and)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise AND operator not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i & b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_bit_or)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise OR operator not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i | b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_bit_xor)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise XOR operator not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i ^ b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_bit_not)
{
    BruterMeta a = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise NOT operator not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, ~a.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_lshift)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise shift operators not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i << b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_rshift)
{
    BruterMeta a = bruter_pop_meta(stack);
    BruterMeta b = bruter_pop_meta(stack);
    if (a.type == BRUTER_TYPE_FLOAT || b.type == BRUTER_TYPE_FLOAT)
    {
        fprintf(stderr, "ERROR: Bitwise shift operators not supported for float types\n");
        exit(EXIT_FAILURE);
    }
    bruter_push_int(stack, a.value.i >> b.value.i, NULL, BRUTER_TYPE_ANY);
}

function(feraw_time)
{
    bruter_push_int(stack, (BruterInt)time(NULL), NULL, BRUTER_TYPE_ANY);
}

function(feraw_clock)
{
    bruter_push_int(stack, (BruterInt)clock(), NULL, BRUTER_TYPE_ANY);
}

init(math)
{
    // register functions
    bruter_push_pointer(context, feraw_add, "add", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_sub, "sub", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_mul, "mul", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_div, "div", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_mod, "mod", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_pow, "pow", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_sqrt, "sqrt", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_abs, "abs", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_min, "min", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_max, "max", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_sin, "sin", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_cos, "cos", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_tan, "tan", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_inc, "inc", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_dec, "dec", BRUTER_TYPE_FUNCTION);
    
    // random functions
    bruter_push_pointer(context, feraw_seed, "seed", BRUTER_TYPE_FUNCTION);
    
    // default rand, 0 to 1 float
    bruter_push_pointer(context, feraw_rand, "rand", BRUTER_TYPE_FUNCTION);

    // flexible random, with min max range and both int and float support
    bruter_push_pointer(context, feraw_random, "random", BRUTER_TYPE_FUNCTION);
    
    // rounding functions
    bruter_push_pointer(context, feraw_floor, "floor", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_ceil, "ceil", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_round, "round", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_trunc, "trunc", BRUTER_TYPE_FUNCTION);

    // bitwise operations
    bruter_push_pointer(context, feraw_bit_and, "bitwise_and", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_bit_or, "bitwise_or", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_bit_xor, "bitwise_xor", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_bit_not, "bitwise_not", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_lshift, "lshift", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_rshift, "rshift", BRUTER_TYPE_FUNCTION);

    // time
    bruter_push_pointer(context, feraw_time, "time", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_clock, "clock", BRUTER_TYPE_FUNCTION);
}