# Language Documentation

## Overview
This document describes a simplified C-like language implemented by a custom interpreter. It details the lexical and syntactical aspects, data types, control flow, functions, and variable handling.


## Lexical Aspects of Language

### Tokens
The language uses several token types:

- **Identifiers**: Follow the regex pattern `[_, letter][letter, number, _]*`.
- **Literals**: For `int`, `double`, `string`, and `char`.
- **Operators**: Includes assignment, comparison, arithmetic, and logical operators.
- **Braces and Parentheses**: Used for grouping and block definitions.
- **Keywords**: Reserved words for language constructs and data types. [List of keywords](#list-of-keywords)

- **Misc Tokens**: Such as arrows, semicolons, commas, and colons.
- **EndOfFile**: Signifies the end of the source file.
- **Error**: Represents an erroneous token.

### Comments
- **Single-Line Comments**: Begin with `//`.
- **Multi-Line Comments**: Enclosed within `/*` and `*/`.

## Syntactical Aspects of Language

### Functions
- **Declaration**: `func functionName(type parameter1, type parameter2) -> returnType;`
- **Definition**: `func functionName(type parameter1, type parameter2) -> returnType { /* code */ }`
- **Calling**: `functionName(value1, value2);`

### Variables
- **Declaration**: `var type variableName;`
- **Definition**: `var type variableName = value;`

### Control Flow
- **if-else Statement**: `if (condition) { /* code */ } else { /* code */ }`
- **while Loop**: `while (condition) { /* code */ }`



## Semantical Aspects of Language

### Type System
- The language implements a strict type system.
- Type compatibility and conversions are enforced at compile-time.
- Supported types include `bool`, `int`, `double`, `string`, `char`.
- Implicit type conversions are limited to avoid ambiguity.

### Variable Scope and Lifetime
- Variables declared inside a function are local to that function.
- Variables declared outside of any function have global scope.
- The lifetime of a variable corresponds to the scope in which it is declared.

### Function Semantics
- Functions must be declared before use.
- Function parameters and return types are strictly enforced.
- Overloading and default parameters are not supported in the initial implementation.

### Control Flow Semantics
- `if` and `while` statements require boolean expressions as conditions.
- Non-boolean expressions used in conditions will result in semantic errors.

### Expression Evaluation
- Expressions follow conventional C-like precedence and associativity rules.
- The language supports basic arithmetic and comparison operations.
- Compound expressions and complex evaluations are limited in the initial implementation.

### Error Handling and Reporting
- Semantic errors include type mismatches, undeclared variables, and scope violations.
- Errors are reported with descriptive messages to aid debugging.


## Data Types
Supported primitive data types include:
- **`bool`**: Represents a Boolean value, true or false.
- **`char`**: Represents a single character.
- **`int`**: Represents an integer number.
- **`double`**: Represents a double-precision floating-point number.
- **`string`**: Represents a sequence of characters as a value-type string.

## Error Handling
Errors will be indicated with relevant error messages. A standardized structure for error reporting is in place.

## Example Code

```c
// Function definition and main function example
func add(int a, int b) -> int {
    return a + b;
}

func main() -> int {
    int result = add(5, 3);
    return 0;
}
```
## List of keywords

- bool
- break
- char
- continue
- do
- double
- else
- false
- for
- func
- if
- int
- return
- string
- true
- var
- void 
- while
