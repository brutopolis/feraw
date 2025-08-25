# feraw

  feraw is a bruter-code preprocessor, it allows you to write a very little abstracted minimal stack-oriented "c-like" code that transpiles to bruter-code.

  feraw is currently written in javascript, and it is a single file `feraw.js`, with no deps at all.

# Usage

  pass a string to feraw_compile and it will return a string containing a bruter-code, that simple.

# Syntax

  feraw syntax is inpired by C, but in a very minimal way, where almost everything is a function call, but with assignments and list & string indexing.

## Example

```
// this is a literal string, a pointer to the code itself
str = "hello world!";
str[0] = 'H'; // str is now "Hello world!"
str[6] = 'W'; // str is now "Hello World!"

// this is a allocated string
str2 = strdup(str); // str2 is now a allocated copy of str
print(str2); // prints "Hello World!"
free(str2); // free the allocated string

// this is a list
list = list(0); // create a new empty list
list[20] = "item at index 20"; // set the literal to index 20, and create all the previous indexes
pop(list); // remove the last item from the list
push(list, "new item"); // add a new item to the end of the list

// lists can also act as objects
list["key"] = "value"; // set the key "key" to "value"
print(list["key"]); // prints "value"


loopstart:


print(pop(list)); // print and remove the last item from the list

condition = equals(len(list), 0); // condition is true if list length is 0

?(condition, end); // if condition is true go to end label

?(1, loopstart); // unconditional jump to loopstart

end:

ls(stack);
free(list); // free the list and all its contents
```
