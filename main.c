#include "rawer.h"

//<functions>
init(std);
init(condition);

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        fprintf(stderr, "ERROR: No input file provided\n");
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    BruterList *context = bruter_new(8, true, true);

    //<functions_init>
    init_std(context); // Initialize the standard functions
    init_condition(context); // Initialize the standard condition functions

    char* filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "ERROR: Could not open file '%s'\n", filename);
        return EXIT_FAILURE;
    }
    // read the entire file into a string
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *input_str = malloc(length + 1);
    if (!input_str)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for input string\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    fread(input_str, 1, length, file);
    input_str[length] = '\0'; // null-terminate the string
    fclose(file);
    BruterList *result = parse(context, input_str);
    bruter_free(result); // Free the result list
    free(input_str); // Free the input string after use

    bruter_free(context); // Free the context after use
    return EXIT_SUCCESS;
}
