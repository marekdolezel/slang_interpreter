# Design decisions of slang interpreter
This document details the implementation of a simple interpreter for `Slang`, a language that is a subset of C with some minor deviations. 
The language supports the following data-types from C: bool, char, int, double. Note that float data-types and pointers are not supported.
One difference from standard C is support for built-in string value-type (this is internally implemented by `std::string`)

## Overall structure of the interpreter
- Lexical analyzer (`Lexer.cpp`)
- Topdown parser (`Parser.cpp`)
- Interpreter (`Interpreter.cpp`)

## Language design
### Lexemes

- The following value-type data-types are supported:
  - **`bool`**: Represents a Boolean value, true or false.
  - **`char`**: Represents a single character.
  - **`int`**: Represents an integer number.
  - **`double`**: Represents a double-precision floating-point number.
  - **`string`**: Represents a sequence of characters as a value-type string.


- Control flow structures:
  - **`if`**: Used for conditional branching. Executes a block of code if a specified condition is true.
  - **`while`**: A looping construct that repeatedly executes a block of code as long as a given condition remains true.
  - **`for`**: A looping construct that allows initialization, a loop condition, and an iteration expression, all in one statement.
  - **`func`**: Used to define a function with a specific name, parameters, and a block of executable code.

- Standard binary operators:
  - **`+`**: Addition operator to sum two numeric values.
  - **`-`**: Subtraction operator to subtract one numeric value from another.
  - **`*`**: Multiplication operator to multiply two numeric values.
  - **`/`**: Division operator to divide one numeric value by another.

- Comparisong and assignment operators:
  - **`=`**: Assignment operator, assigns the value on the right to the variable on the left.
  - **`==`**: Equality comparison operator, checks if two values are equal.
  - **`>`**: Greater-than operator, checks if the value on the left is greater than the one on the right.
  - **`>=`**: Greater-than-or-equal operator, checks if the value on the left is greater than or equal to the one on the right.
  - **`<`**: Less-than operator, checks if the value on the left is less than the one on the right.
  - **`<=`**: Less-than-or-equal operator, checks if the value on the left is less than or equal to the one on the right.
  - **`!=`**: Not-equal operator, checks if two values are not equal.

- Additional:
  - **`{`**: Left brace, used to mark the beginning of a code block.
  - **`}`**: Right brace, used to mark the end of a code block.
  - **`(`**: Left parenthesis, used to group expressions or denote the start of a parameter list in functions.
  - **`)`**: Right parenthesis, used to close a grouping of expressions or a parameter list in functions.
  - **`;`**: Semicolon, used as a statement terminator.
  - **`,`**: Comma, used to separate items in a list, such as parameters in function calls or declarations.
