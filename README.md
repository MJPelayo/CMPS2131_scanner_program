# CMPS2131_scanner_program

# Arithmetic Expression Tokenizer

A lexical analyzer that breaks down arithmetic expressions into their component tokens.

## start symbol for our grammar
----------------------------------------------------------------------
<s> ::= <expr> END_OF_INPUT

<expr> ::= <term> ( (PLUS | MINUS) <term> )*

<term> ::= <factor> ( (MULTIPLY | DIVIDE | MODULUS) <factor> )*

<factor> ::= <power> ( EXPONENT <factor> )?

<power> ::= (PLUS | MINUS)? <primary>

<primary> ::= NUMBER | LEFT_PAREN <expr> RIGHT_PAREN

// Expanded number productions (matching lexer behavior)
<NUMBER> ::= <integer> | <integer> '.' <unsigned_integer> | MINUS <integer> | MINUS <integer> '.' <unsigned_integer>

<integer> ::= <digit> | <digit> <integer>

<unsigned_integer> ::= <digit> | <digit> <unsigned_integer>

<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

---------------------------------------------------------------------------------------
## Features

- Recognizes numbers (integers and decimals)
- Handles all basic arithmetic operators (`+`, `-`, `*`, `/`, `%`, `^`)
- Supports parentheses for grouping
- Distinguishes between subtraction and negative numbers
- Provides clear token classification
- Well-structured, modular code

## File Structure

## Building the Project

g++ tokenizer.h tokenizer.cpp main.cpp -o calculator
./calculator


Token Types
---------------------------------------------------------------
Token Type	| Description	                    | Examples
NUMBER	    |Numeric literals	                | 42, -3.14
LEFT_PAREN	|Opening parenthesis	            | (
RIGHT_PAREN	|Closing parenthesis	            | )
EXPONENT	|Exponentiation operator	        | ^
MULTIPLY	|Multiplication operator	        | *
DIVIDE	    |Division operator	                | /
MODULUS	    |Modulus operator	                | %
PLUS	    |Addition operator	                | +
MINUS	    |Subtraction operator or negative	| -
UNKNOWN 	|Unrecognized characters            |
---------------------------------------------------------------
# Design Notes
The tokenizer follows a strict lexical analysis phase
Numbers support optional sign and decimal points
Negative numbers are distinguished from subtraction
The code is organized into clear interface and implementation
Easy to extend with additional operators or token types

# Future Enhancements
Add support for variables and functions
Implement a parser to evaluate expressions
Add support for scientific notation
Include more mathematical operators
Add error handling with line/column numbers