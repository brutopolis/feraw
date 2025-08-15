#include "bruter.h"

function(feraw_strdup)
{
    char* str = bruter_pop_pointer(stack);
    if (str == NULL)
    {
        bruter_push_pointer(stack, NULL, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    char* new_str = strdup(str);
    if (new_str == NULL)
    {
        printf("BRUTER_ERROR: failed to duplicate string\n");
        exit(EXIT_FAILURE);
    }

    bruter_push_pointer(stack, new_str, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_strcat)
{
    char* str1 = bruter_pop_pointer(stack);
    char* str2 = bruter_pop_pointer(stack);
    
    if (str1 == NULL || str2 == NULL)
    {
        bruter_push_pointer(stack, NULL, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    char* new_str = (char*)malloc(len1 + len2 + 1);
    if (new_str == NULL)
    {
        printf("BRUTER_ERROR: failed to allocate memory for concatenated string\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(new_str, str1);
    strcat(new_str, str2);
    
    bruter_push_pointer(stack, new_str, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_strcpy)
{
    char* dest = bruter_pop_pointer(stack);
    char* src = bruter_pop_pointer(stack);
    
    if (src == NULL || dest == NULL)
    {
        bruter_push_pointer(stack, NULL, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    strcpy(dest, src);
    bruter_push_pointer(stack, dest, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_strncpy)
{
    char* dest = bruter_pop_pointer(stack);
    char* src = bruter_pop_pointer(stack);
    BruterInt n = bruter_pop_int(stack);
    
    if (src == NULL || dest == NULL)
    {
        bruter_push_pointer(stack, NULL, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    strncpy(dest, src, n);
    dest[n] = '\0'; // Ensure null termination
    
    bruter_push_pointer(stack, dest, NULL, BRUTER_TYPE_BUFFER);
}

function (feraw_strcmp)
{
    char* str1 = bruter_pop_pointer(stack);
    char* str2 = bruter_pop_pointer(stack);
    
    if (str1 == NULL || str2 == NULL)
    {
        bruter_push_int(stack, 0, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    int result = strcmp(str1, str2);
    bruter_push_int(stack, result, NULL, BRUTER_TYPE_ANY);
}

function(feraw_strlen)
{
    char* str = bruter_pop_pointer(stack);
    
    if (str == NULL)
    {
        bruter_push_int(stack, 0, NULL, BRUTER_TYPE_ANY);
        return;
    }
    
    BruterInt length = strlen(str);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(feraw_strchr)
{
    char* str = bruter_pop_pointer(stack);
    char c = (char)bruter_pop_int(stack);

    char* result = strchr(str, c);
    bruter_push_pointer(stack, result, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_strstr)
{
    char* str1 = bruter_pop_pointer(stack);
    char* str2 = (char)bruter_pop_int(stack);

    char* result = strstr(str1, str2);
    bruter_push_pointer(stack, result, NULL, BRUTER_TYPE_BUFFER);
}

init(string)
{
    bruter_push_pointer(context, feraw_strdup, "strdup", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strcat, "strcat", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strcpy, "strcpy", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strncpy, "strncpy", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strcmp, "strcmp", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strlen, "strlen", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strchr, "strchr", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strlen, "strlen", BRUTER_TYPE_FUNCTION);

}