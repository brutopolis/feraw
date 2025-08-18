#include "bruter.h"

// functions
// functions
// functions
// functions

function (feraw_print)
{
    BruterMeta value = bruter_pop_meta(stack);
    switch (value.type)
    {
        case BRUTER_TYPE_FLOAT:
            printf("%f", value.value.f);
            break;
        case BRUTER_TYPE_BUFFER:
            printf("%s", (char*)value.value.p);
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
            break;
        default:
            printf("%ld", value.value.i);
            break;
    }
}

function(feraw_println)
{
    feraw_print(stack);
    printf("\n");
}

function(feraw_type)
{
    BruterMeta value = bruter_pop_meta(stack);
    bruter_push_int(stack, value.type, NULL, BRUTER_TYPE_ANY);
}

function(feraw_key)
{
    BruterMeta value = bruter_pop_meta(stack);
    bruter_push_pointer(stack, value.key, NULL, BRUTER_TYPE_BUFFER);
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

function(feraw_pop)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(list);
    free(value.key); // Free the key if it exists
    bruter_push_meta(stack, value); // Push the popped value back to the stack
}

function(feraw_push)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    bruter_push_meta(list, value);
}

function(feraw_shift)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_shift_meta(list);
    free(value.key); // Free the key if it exists
    bruter_push_meta(stack, value); // Push the shifted value back to the stack
}

function(feraw_unshift)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterMeta value = bruter_pop_meta(stack);
    bruter_unshift_meta(list, value);
}

function(feraw_insert)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);
    BruterMeta value = bruter_pop_meta(stack);

    if (index < 0) // -1 = the last element and so on
    {
        index += list->size; // Adjust negative index to positive
    }

    bruter_insert_meta(list, index, value);
}

function(feraw_remove)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index = bruter_pop_int(stack);

    if (index < 0) // -1 = the last element and so on
    {
        index += list->size; // Adjust negative index to positive
    }

    BruterMeta removed_value = bruter_remove_meta(list, index);
    free(removed_value.key); // Free the key if it exists
    bruter_push_meta(stack, removed_value); // Push the removed value back to the stack
}

function(feraw_get)
{
    BruterMeta list_meta = bruter_pop_meta(stack);
    BruterMeta index_meta = bruter_pop_meta(stack);
    BruterInt index = index_meta.value.i;
    
    if (list_meta.type == BRUTER_TYPE_BUFFER)
    {
        char* buffer = (char*)list_meta.value.p;
        if (index_meta.type == BRUTER_TYPE_FLOAT)
        {
            index = (BruterInt)index_meta.value.f; // Convert float to integer if necessary
        }
        
        if (index < 0) // -1 = the last element and so on
        {
            index += strlen(buffer); // Adjust negative index to positive
        }

        bruter_push_int(stack, buffer[index], NULL, BRUTER_TYPE_ANY);
        return;
    }
    else
    {
        BruterList* list = (BruterList*)list_meta.value.p;
        if (index_meta.type == BRUTER_TYPE_FLOAT)
        {
            index = (BruterInt)index_meta.value.f; // Convert float to integer if necessary
        }
        else if (index_meta.type == BRUTER_TYPE_BUFFER)
        {
            index = bruter_find_key(list_meta.value.p, (char*)index_meta.value.p);
            if (index < 0)
            {
                fprintf(stderr, "ERROR: cant get, key '%s' not found in list\n", (char*)index_meta.value.p);
                exit(EXIT_FAILURE);
            }
        }

        if (index < 0) // -1 = the last element and so on
        {
            index += list->size; // Adjust negative index to positive
        }

        bruter_push_meta(stack, bruter_get_meta(list, index));
    }
}

function(feraw_set)
{
    BruterMeta list_meta = bruter_pop_meta(stack);
    BruterMeta index = bruter_pop_meta(stack);
    BruterMeta value = bruter_pop_meta(stack);
    if (list_meta.type == BRUTER_TYPE_BUFFER)
    {
        unsigned char* buffer = (unsigned char*)list_meta.value.p;
        if (index.type == BRUTER_TYPE_FLOAT)
        {
            index.value.i = (BruterInt)index.value.f; // Convert float to integer if necessary
        }
        
        if (index.value.i < 0) // -1 = the last element and so on
        {
            index.value.i += strlen((char*)buffer); // Adjust negative index to positive
        }

        buffer[index.value.i] = value.value.i; // Directly set the value in the buffer
    }
    else
    {
        BruterList* list = (BruterList*)list_meta.value.p;
        switch (index.type)
        {
            case BRUTER_TYPE_FLOAT:
                index.value.i = (BruterInt)index.value.f;
            case BRUTER_TYPE_ANY:
                if (index.value.i >= list->size)
                {
                    while (list->size <= index.value.i)
                    {
                        bruter_push_meta(list, (BruterMeta){.value = {.i = 0}, .key = NULL, .type = BRUTER_TYPE_ANY});
                    }
                }
                else if (index.value.i < 0) // -1 = the last element and so on
                {
                    index.value.i += list->size; // Adjust negative index to positive
                }
                list->data[index.value.i] = value.value; // Directly set the value
                break;
            case BRUTER_TYPE_BUFFER:
            {
                BruterInt found_index = bruter_find_key(list, (char*)index.value.p);
                if (found_index < 0)
                {
                    value.key = strdup(index.value.p);
                    bruter_push_meta(list, value); // Push the value to the list
                }
                else 
                {
                    list->data[found_index] = value.value; // Directly set the value
                    if (list->keys != NULL)
                    {
                        if (list->keys[found_index] == NULL)
                        {
                            list->keys[found_index] = index.value.p; // Set the new key
                        }
                        else
                        {
                            free(value.key); // Free the old key if it was allocated
                        }
                    }
                    if (list->types != NULL)
                    {
                        list->types[found_index] = value.type; // Set the type   
                    }
                }
            }
            break;
        }
    }
}

function(feraw_where)
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

function(feraw_find)
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

function(feraw_length)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_push_int(stack, list->size, NULL, BRUTER_TYPE_ANY);
}

function(feraw_copy)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterList* new_list = bruter_copy(list);
}

function(feraw_concat)
{
    BruterList* list1 = bruter_pop_pointer(stack);
    BruterList* list2 = bruter_pop_pointer(stack);
    bruter_concat(list1, list2);
    bruter_push_pointer(stack, list1, NULL, BRUTER_TYPE_LIST);
}

function(feraw_swap)
{
    BruterList* list = bruter_pop_pointer(stack);
    BruterInt index1 = bruter_pop_int(stack);
    BruterInt index2 = bruter_pop_int(stack);

    if (index1 < 0 || index1 >= list->size || index2 < 0 || index2 >= list->size)
    {
        fprintf(stderr, "ERROR: cannot swap, index %" PRIdPTR " or %" PRIdPTR " out of range in list of size %" PRIdPTR "\n", index1, index2, list->size);
        exit(EXIT_FAILURE);
    }

    bruter_swap(list, index1, index2);
}

function(feraw_reverse)
{
    BruterList* list = bruter_pop_pointer(stack);
    bruter_reverse(list);
}

function(feraw_alloc)
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
    else
    {
        bruter_free((BruterList*)value.value.p); // Free the list if it was allocated
    }
    // No action needed for other types, as they are not dynamically allocated
}

function(feraw_ls)
{
    // [index, type, "name"] = value;
    BruterList* list = bruter_pop_pointer(stack);
    for (BruterInt i = 0; i < list->size; i++)
    {
        if (list->keys != NULL && list->keys[i] != NULL)
        {
            printf("[%ld, %d, \"%s\"] = ", i, list->types[i], list->keys[i]);
        }
        else
        {
            printf("[%ld, %d] = ", i, list->types[i]);
        }

        switch (list->types[i])
        {
            case BRUTER_TYPE_FLOAT:
                printf("%f\n", list->data[i].f);
                break;
            case BRUTER_TYPE_BUFFER:
                printf("%s\n", (char*)list->data[i].p);
                break;
            case BRUTER_TYPE_LIST:
                printf("[List]\n");
                break;
            default:
                printf("%ld\n", list->data[i].i);
                break;
        }
    }
}

function(feraw_eval)
{
    BruterList* context = bruter_pop_pointer(stack);
    char* code = bruter_pop_pointer(stack);
    BruterList* result = bruter_parse(context, code);
    bruter_push_pointer(stack, result, NULL, BRUTER_TYPE_LIST);
}