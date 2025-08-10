# feraw

  feraw is a bruter-code preprocessor, it allows you to write a very little abstracted minimal stack-oriented "c-like" code that transpiles to bruter-code.

  feraw is currently written in javascript, and it is a single file `feraw.js`.

# Usage

  pass a string to feraw_compile and it will return a string containing a bruter-code, that simple.

# Syntax

  feraw syntax is inpired by C, but in a very minimal way, where almost everything is a function call, but with assignments and list & string indexing.

## Example

```
// this is a literal string, a pointer to the code itself
str = "hello world!";
str[0] = "H"; // str is now "Hello world!"
str[6] = "W"; // str is now "Hello World!"
```
