# feraw

  feraw has been discontinued, but check its successor: https://github.com/jardimdanificado/rap

  feraw is a bruter code generator i did for my personal use to generate more easily bruter code with a more familiar syntax, it allows you to write a very little abstracted minimal stack-oriented "c-like" code and generates a bruter code or C with embedded bruter code from it;

  feraw is currently written in javascript, and it is a single file `feraw.js`, with no deps at all, while bruter code is completely predictable, feraw is not, and have several issues that i might not fix ever, so *ALWAYS* check if the generated bruter code is something you expect;

  (*not my proudest code with the best practices, but it sometimes works*)

# features and issues
  some of the features of feraw are:
  - feraw introduces a stdlib, almost 100% written in C, so it is can be used in any bruter environment you setup;
  - strings and lists as first class citizens, you can create, modify and free them direcly like a array;
  - strings and character delimiters like C;
  - it has a minimal preprocessor, with macros and labels, which have some issues;
  - the preprocessor also include inline bruter (`inline(code whatever !)`) and inline C (`cc{any c code}`), these 100% safe and tested, with no issues found so far;
  - feraw can generate both bruter code and C code with embedded bruter code and libs it might need;

  some of the issues are:
  - no error handling at all, if you make a mistake you will receive a segfault or a non-sense/out-of-context message.
  - no optimizations at all, the generated code will be probably be efficient, but we cannot say the same for the feraw.js itself, its a crap.
  - macros and labels doesnt care if the word is inside a string or a comment, it will replace it anyway.
  - there is no function in the conventional way, you can use labels, macros or create a new code(a list basically) and call it just like a function, they will have the same context, but they will be different codes;
  - feraw.js is a complete mess, sketchy at best, because thats what it is meant to be, a sketch language that doesnt take itself seriously, with the only purpose of generating sketches of bruter code.
  - we dont have math/bitwise/logical or any other regular operators you expect from a serious language, you have to use functions like `add(a, b)`, `and(a, b)`, `or(a, b)`, `not(a)`, etc.
  
# Usage

  pass a string to feraw_compile and it will return a string containing a bruter-code, that simple.

# Syntax

  feraw syntax is somewhat inspired by C, but almost everything is a function call, with assignments and list & string indexing and such.

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
