#include "bruter.h"

// functions
// functions
// functions
// functions

function(feraw_print)
{
    BruterMeta value = bruter_pop_meta(stack);
    switch (value.type)
    {
        case BRUTER_TYPE_FLOAT:
            printf("%f\n", value.value.f);
            break;
        case BRUTER_TYPE_BUFFER:
            printf("%s\n", (char*)value.value.p);
            break;
        case BRUTER_TYPE_LIST:
            for (BruterInt i = 0; i < ((BruterList*)value.value.p)->size; i++)
            {
                BruterMeta item = bruter_get_meta((BruterList*)value.value.p, i);
                switch (item.type)
                {
                    case BRUTER_TYPE_FLOAT:
                        printf("%f ", item.value.f);
                        break;
                    case BRUTER_TYPE_BUFFER:
                        printf("%s ", (char*)item.value.p);
                        break;
                    case BRUTER_TYPE_LIST:
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
                    bruter_push_int(stack, a.value.i + b.value.i, NULL, 0);
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
                    bruter_push_int(stack, a.value.i - b.value.i, NULL, 0);
                    break;
            }
            break;
    }
}

function(feraw_rename)
{
    BruterMeta value = bruter_pop_meta(stack);
    char* new_key = bruter_pop_pointer(stack);

    if (value.key != NULL)
    {
        free(value.key); // Free the old key if it was allocated
    }
    value.key = new_key;
    bruter_push_meta(stack, value);
}

function(feraw_retype)
{
    BruterInt new_type = bruter_pop_int(stack);
    BruterMeta value = bruter_pop_meta(stack);
    value.type = new_type; // Update the type of the value
    bruter_push_meta(stack, value);
}

function(feraw_list)
{
    BruterInt size = bruter_pop_int(stack);
    BruterList *list = bruter_new(8, true, true);
    for (BruterInt i = 0; i < size; i++)
    {
        BruterMeta value = bruter_pop_meta(stack);
        bruter_push_meta(list, value);
    }
    bruter_push_pointer(stack, list, NULL, BRUTER_TYPE_LIST);
}

function(feraw_list_pop)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_push_meta(stack, bruter_pop_meta(list));
}

function(feraw_list_push)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    bruter_push_meta(list, value);
}

function(feraw_list_shift)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_push_meta(stack, bruter_shift_meta(list));
}

function(feraw_list_unshift)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    bruter_unshift_meta(list, value);
}

function(feraw_list_insert)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);
    BruterMeta value = bruter_pop_meta(stack);

    if (index < 0 || index > list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list insertion\n");
        exit(EXIT_FAILURE);
    }

    bruter_insert_meta(list, index, value);
}

function(feraw_list_remove)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);

    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list removal\n");
        exit(EXIT_FAILURE);
    }

    BruterMeta removed_value = bruter_remove_meta(list, index);
    bruter_push_meta(stack, removed_value); // Push the removed value back to the stack
}

function(feraw_list_define)
{
    BruterList *list = bruter_pop_pointer(stack);
    BruterMeta meta = bruter_pop_meta(stack);
    bruter_define_meta(list, meta);
}

function(feraw_list_undefine)
{
    BruterList *list = bruter_pop_pointer(stack);
    char* key = bruter_pop_pointer(stack);
    bruter_push_meta(stack, bruter_undefine_meta(list, key));
}

function(feraw_list_get)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta index_meta = bruter_pop_meta(stack);
    BruterInt index = index_meta.value.i;
    if (index_meta.type == BRUTER_TYPE_FLOAT)
    {
        index = (BruterInt)index_meta.value.f; // Convert float to integer if necessary
    }
    else if (index_meta.type == BRUTER_TYPE_BUFFER)
    {
        index = bruter_find_key(list, (char*)index_meta.value.p);
    }

    if (index < 0 || index >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list access\n");
        exit(EXIT_FAILURE);
    }

    bruter_push_meta(stack, bruter_get_meta(list, index));
}

function(feraw_list_set)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta index = bruter_pop_meta(stack);
    BruterMeta value = bruter_pop_meta(stack);

    switch (index.type)
    {
        case BRUTER_TYPE_ANY:
            if (index.value.i >= list->size)
            {
                while (list->size <= index.value.i)
                {
                    bruter_push_meta(list, (BruterMeta){.value = {.i = 0}, .key = NULL, .type = BRUTER_TYPE_ANY});
                }
            }
            list->data[index.value.i] = value.value; // Directly set the value
            break;
        case BRUTER_TYPE_BUFFER:
        {
            BruterInt found_index = bruter_find_key(list, (char*)index.value.p);
            if (found_index < 0)
            {
                value.key = strdup((char*)index.value.p); // Preserve the key if not found
                bruter_push_meta(list, value); // Push the value to the list
            }
            else 
            {
                value.key = list->keys[found_index]; // Preserve the key
                list->data[found_index] = value.value; // Update the existing entry
            }
        }
        break;
    }
}

function(feraw_list_find)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    BruterInt found_index = -1;

    for (BruterInt i = 0; i < list->size; i++)
    {
        if (list->types[i] == value.type && list->data[i].i == value.value.i)
        {
            found_index = i;
            break;
        }
    }

    bruter_push_int(stack, found_index, NULL, BRUTER_TYPE_ANY);
}

function(feraw_list_find_key)
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

    bruter_push_int(stack, found_index, NULL, BRUTER_TYPE_ANY);
}

function(feraw_list_length)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_push_int(stack, list->size, NULL, BRUTER_TYPE_ANY);
}

function(feraw_list_copy)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterList* new_list = bruter_copy(list);
}

function(feraw_list_concat)
{
    BruterList* list1 = bruter_pop_pointer(stack);
    BruterList* list2 = bruter_pop_pointer(stack);
    bruter_concat(list1, list2);
    bruter_push_pointer(stack, list1, NULL, BRUTER_TYPE_LIST);
}

function(feraw_list_swap)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index1 = bruter_pop_int(stack);
    BruterInt index2 = bruter_pop_int(stack);

    if (index1 < 0 || index1 >= list->size || index2 < 0 || index2 >= list->size)
    {
        fprintf(stderr, "ERROR: Index out of bounds for list swap\n");
        exit(EXIT_FAILURE);
    }

    bruter_swap(list, index1, index2);
}

function(feraw_list_reverse)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_reverse(list);
}

function(feraw_list_alloc)
{
    BruterList *arena = bruter_pop_pointer(stack);
    BruterInt size = bruter_pop_int(stack);
    void *ptr = bruter_alloc(arena, size);
    bruter_push_pointer(stack, ptr, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_dup)
{
    BruterMeta value = bruter_pop_meta(stack);
    bruter_push_meta(stack, value); // Push the value back to the stack
    bruter_push_meta(stack, value); // Duplicate it
}

function(feraw_buffer)
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

    bruter_push_pointer(stack, str, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_create)
{
    BruterMeta value = bruter_pop_meta(stack);
    char* key = bruter_pop_pointer(stack);
    BruterInt type = bruter_pop_int(stack);
    bruter_push_meta(stack, (BruterMeta){.value = value.value, .key = key, .type = type});
}

function(feraw_free)
{
    void *ptr = bruter_pop_pointer(stack);
    if (ptr != NULL)
    {
        free(ptr); // Free the pointer if it was allocated
    }
}

function(feraw_clear)
{
    BruterList *list = bruter_pop_pointer(stack);
    while (list->size > 0)
    {
        bruter_pop_int(list); // Pop each item from the list
    }
}

function(feraw_free)
{
    BruterMeta value = bruter_pop_meta(stack);
    if (value.type == BRUTER_TYPE_BUFFER)
    {
        free(value.value.p); // Free the buffer if it was allocated
    }
    else if (value.type == BRUTER_TYPE_LIST)
    {
        bruter_free((BruterList*)value.value.p); // Free the list if it was allocated
    }
    // No action needed for other types, as they are not dynamically allocated
}

init(std)
{
    bruter_push_pointer(context, feraw_print, "print", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_add, "add", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_sub, "sub", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_rename, "rename", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_retype, "retype", BRUTER_TYPE_FUNCTION);
    
    bruter_push_pointer(context, feraw_list, "list", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_pop, "pop", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_push, "push", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_shift, "shift", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_unshift, "unshift", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_insert, "insert", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_remove, "remove", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_define, "define", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_undefine, "undefine", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_get, "get", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_set, "set", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_find, "where", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_find_key, "find", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_length, "length", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_copy, "copy", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_concat, "concat", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_swap, "swap", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_reverse, "reverse", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_list_alloc, "alloc", BRUTER_TYPE_FUNCTION);

    bruter_push_pointer(context, feraw_dup, "dup", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_buffer, "buffer", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_create, "new", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_clear, "clear", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_free, "free", BRUTER_TYPE_FUNCTION);

    bruter_push_int(context, BRUTER_TYPE_NULL, "Null", BRUTER_TYPE_ANY);
    bruter_push_int(context, BRUTER_TYPE_ANY, "Any", BRUTER_TYPE_ANY);
    bruter_push_int(context, BRUTER_TYPE_FLOAT, "Float", BRUTER_TYPE_ANY);
    bruter_push_int(context, BRUTER_TYPE_BUFFER, "Buffer", BRUTER_TYPE_ANY);
    bruter_push_int(context, BRUTER_TYPE_LIST, "List", BRUTER_TYPE_ANY);
    bruter_push_int(context, BRUTER_TYPE_FUNCTION, "Function", BRUTER_TYPE_ANY);

    bruter_push_pointer(context, NULL, "null", BRUTER_TYPE_NULL);
}