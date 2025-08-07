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

    for (char* p = str; *p; p++) 
    {
        if (*p == '\x13') *p = '#'; // Replace ASCII 19 with #
        else if (*p == '\x14') *p = '\n'; // Replace ASCII 20 with newline
        else if (*p == '\x15') *p = '\r'; // Replace ASCII 21 with carriage return
        else if (*p == '\x16') *p = '\t'; // Replace ASCII 22 with tab
        else if (*p == '\x17') *p = ' '; // Replace ASCII 23 with space
        else if (*p == '\x18') *p = ':'; // Replace ASCII 24 with colon
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

function(feraw_strncpy)
{
    char* src = bruter_pop_pointer(stack);
    char* dest = bruter_pop_pointer(stack);
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

init(string)
{
    bruter_push_pointer(context, feraw_strdup, "strdup", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strcat, "strcat", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strncpy, "strncpy", BRUTER_TYPE_FUNCTION);
    bruter_push_pointer(context, feraw_strcmp, "strcmp", BRUTER_TYPE_FUNCTION);
    
}