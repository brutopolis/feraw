#include "rawer.h"

// functions
// functions
// functions
// functions

function(rawer_print)
{
    BruterMetaValue value = bruter_pop_meta(stack);
    switch (value.type)
    {
        case BR_TYPE_FLOAT:
            printf("%f\n", value.value.f);
            break;
        case BR_TYPE_BUFFER:
            printf("%s\n", (char*)value.value.p);
            break;
        case BR_TYPE_LIST:
            for (BruterInt i = 0; i < ((BruterList*)value.value.p)->size; i++)
            {
                BruterMetaValue item = bruter_get_meta((BruterList*)value.value.p, i);
                switch (item.type)
                {
                    case BR_TYPE_FLOAT:
                        printf("%f ", item.value.f);
                        break;
                    case BR_TYPE_BUFFER:
                        printf("%s ", (char*)item.value.p);
                        break;
                    case BR_TYPE_LIST:
                        printf("[List] ");
                        break;
                    default:
                        printf("%ld ", item.value.i);
                        break;
                }
            }
            printf("\n");
            break;
        default:
            printf("%ld\n", value.value.i);
            break;
    }
}

function(rawer_add)
{
    BruterMetaValue a = bruter_pop_meta(stack);
    BruterMetaValue b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BR_TYPE_FLOAT:
            switch (b.type)
            {
                case BR_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.f + b.value.f, NULL, BR_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_float(stack, a.value.f + b.value.i, NULL, BR_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BR_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.i + b.value.f, NULL, BR_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_int(stack, a.value.i + b.value.i, NULL, 0);
                    break;
            }
            break;
    }
}

function(rawer_sub)
{
    BruterMetaValue a = bruter_pop_meta(stack);
    BruterMetaValue b = bruter_pop_meta(stack);
    switch (a.type)
    {
        case BR_TYPE_FLOAT:
            switch (b.type)
            {
                case BR_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.f - b.value.f, NULL, BR_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_float(stack, a.value.f - b.value.i, NULL, BR_TYPE_FLOAT);
                    break;
            }
            break;
        default:
            switch (b.type)
            {
                case BR_TYPE_FLOAT:
                    bruter_push_float(stack, a.value.i - b.value.f, NULL, BR_TYPE_FLOAT);
                    break;
                default:
                    bruter_push_int(stack, a.value.i - b.value.i, NULL, 0);
                    break;
            }
            break;
    }
}

function(rawer_register)
{
    BruterList *context = bruter_pop_pointer(stack);
    BruterMetaValue meta = bruter_pop_meta(stack);
    bruter_push_meta(context, meta);
}

function(rawer_rename)
{
    char* new_key = bruter_pop_pointer(stack);
    BruterMetaValue value = bruter_pop_meta(stack);

    if (value.key != NULL)
    {
        free(value.key); // Free the old key if it was allocated
    }
    value.key = new_key;
    bruter_push_meta(stack, value);
}

function(rawer_retype)
{
    BruterInt new_type = bruter_pop_int(stack);
    BruterMetaValue value = bruter_pop_meta(stack);
    value.type = new_type; // Update the type of the value
    bruter_push_meta(stack, value);
}

function(rawer_clear)
{
    clear_context(stack);
}

function(rawer_list)
{
    BruterInt size = bruter_pop_int(stack);
    BruterList *list = bruter_new(8, true, true);
    for (BruterInt i = 0; i < size; i++)
    {
        BruterMetaValue value = bruter_pop_meta(stack);
        bruter_push_meta(list, value);
    }
    bruter_push_pointer(stack, list, NULL, BR_TYPE_LIST);
}

function(rawer_list_pop)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt amount = bruter_pop_int(stack);
    for (BruterInt i = 0; i < amount && list->size > 0; i++)
    {
        bruter_push_meta(stack, bruter_pop_meta(list));
    }
}

function(rawer_list_push)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMetaValue value = bruter_pop_meta(stack);
    bruter_push_meta(list, value);
}

function(rawer_list_shift)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt amount = bruter_pop_int(stack);
    for (BruterInt i = 0; i < amount && list->size > 0; i++)
    {
        bruter_push_meta(stack, bruter_shift_meta(list));
    }
}

function(rawer_list_unshift)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMetaValue value = bruter_pop_meta(stack);
    bruter_unshift_meta(list, value);
}

function(rawer_list_insert)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);
    BruterMetaValue value = bruter_pop_meta(stack);

    if (index < 0 || index > list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list insertion\n");
        exit(EXIT_FAILURE);
    }

    bruter_insert_meta(list, index, value);
}

function(rawer_list_remove)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);

    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list removal\n");
        exit(EXIT_FAILURE);
    }

    bruter_remove_meta(list, index);
}

function(rawer_list_get)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);

    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list access\n");
        exit(EXIT_FAILURE);
    }

    bruter_push_meta(stack, bruter_get_meta(list, index));
}

function(rawer_list_set)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);
    BruterMetaValue value = bruter_pop_meta(stack);

    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list set\n");
        exit(EXIT_FAILURE);
    }

    bruter_set_meta(list, index, value);
}

function(rawer_list_find)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMetaValue value = bruter_pop_meta(stack);
    BruterInt found_index = -1;

    for (BruterInt i = 0; i < list->size; i++)
    {
        if (list->types[i] == value.type && list->data[i].i == value.value.i)
        {
            found_index = i;
            break;
        }
    }

    bruter_push_int(stack, found_index, NULL, BR_TYPE_ANY);
}

function(rawer_list_find_key)
{
    BruterList* list = bruter_pop_pointer(stack);
    char* key = bruter_pop_pointer(stack);
    BruterInt found_index = -1;

    for (BruterInt i = 0; i < list->size; i++)
    {
        if (list->keys[i] != NULL && strcmp(list->keys[i], key) == 0)
        {
            found_index = i;
            break;
        }
    }

    bruter_push_int(stack, found_index, NULL, BR_TYPE_ANY);
}

function(rawer_dup)
{
    BruterMetaValue value = bruter_pop_meta(stack);
    bruter_push_meta(stack, value); // Push the value back to the stack
    bruter_push_meta(stack, value); // Duplicate it
}

function(rawer_buffer)
{
    BruterInt size = bruter_pop_int(stack);
    char* str = (char*)malloc(size);
    if (str == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed for buffer\n");
        exit(EXIT_FAILURE);
    }

    for (BruterInt i = 0; i < size; i++)
    {
        str[i] = (char)bruter_pop_int(stack);
    }

    bruter_push_pointer(stack, str, NULL, BR_TYPE_BUFFER);
}

init(std)
{
    BruterInt found = bruter_find_key(context, "context");
    if (found == -1)
    {
        bruter_push_pointer(context, context, "context", BR_TYPE_ANY);
    }

    bruter_push_pointer(context, rawer_print, "print", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_add, "add", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_sub, "sub", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_rename, "rename", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_retype, "retype", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_register, "register", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_clear, "clear", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list, "list", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_pop, "pop", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_push, "push", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_shift, "shift", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_unshift, "unshift", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_insert, "insert", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_remove, "remove", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_get, "get", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_set, "set", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_find, "where", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_list_find_key, "find", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_dup, "dup", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_buffer, "buffer", BR_TYPE_FUNCTION);

    bruter_push_int(context, BR_TYPE_NULL, "Null", BR_TYPE_ANY);
    bruter_push_int(context, BR_TYPE_ANY, "Any", BR_TYPE_ANY);
    bruter_push_int(context, BR_TYPE_FLOAT, "Float", BR_TYPE_ANY);
    bruter_push_int(context, BR_TYPE_BUFFER, "Buffer", BR_TYPE_ANY);
    bruter_push_int(context, BR_TYPE_LIST, "List", BR_TYPE_ANY);
    bruter_push_int(context, BR_TYPE_FUNCTION, "Function", BR_TYPE_ANY);
}