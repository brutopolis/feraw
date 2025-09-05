#include <bruter.h>

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

function(feraw_print_string)
{
    char *str = bruter_pop_pointer(stack);
    if (str == NULL)
    {
        printf("NULL");
        return;
    }
    printf("%s", str);
}

function(feraw_print_int)
{
    BruterInt value = bruter_pop_int(stack);
    printf("%ld", value);
}

function(feraw_print_float)
{
    BruterFloat value = bruter_pop_float(stack);
    printf("%f", value);
}

function(feraw_print_bool)
{
    BruterInt value = bruter_pop_int(stack);
    printf(value ? "true" : "false");
}

function(feraw_println)
{
    feraw_print(stack);
    printf("\n");
}

function(feraw_ls)
{
    // [index, type, "name"] = value;
    BruterList* list = bruter_pop_pointer(stack);
    for (BruterInt i = 0; i < list->size; i++)
    {
        printf("[%ld", i);
        if (list->types != NULL)
        {
            printf(", %d", list->types[i]);
        }

        if (list->keys != NULL)
        {
            if (list->keys[i] != NULL)
            {
                printf(", '%s'] = ", list->keys[i]);
            }
            else
            {
                printf("] = ");
            }
        }
        else
        {
            printf("] = ");
        }

        if (list->types == NULL)
        {
            printf("%ld\n", list->data[i].i);
            continue;
        }
        else 
        {
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
}

function(feraw_scan)
{
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        bruter_push_pointer(stack, strdup(buffer), NULL, BRUTER_TYPE_BUFFER);
    }
    else
    {
        bruter_push_pointer(stack, NULL, NULL, BRUTER_TYPE_BUFFER);
    }
}