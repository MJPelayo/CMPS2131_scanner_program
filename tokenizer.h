#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

/**
 * TokenType enum defines all possible token categories
 * that our lexer can recognize in arithmetic expressions.
 */
enum TokenType {
    NUMBER,        // Numeric literals (e.g., 42, 3.14, -5)
    LEFT_PAREN,    // Opening parenthesis '('
    RIGHT_PAREN,   // Closing parenthesis ')'
    EXPONENT,      // Exponentiation operator '^'
    MULTIPLY,      // Multiplication operator '*'
    DIVIDE,        // Division operator '/'
    MODULUS,       // Modulus operator '%'
    PLUS,          // Addition operator '+'
    MINUS,         // Subtraction operator '-' or negative sign
    UNKNOWN,       // Unrecognized characters
    END_OF_INPUT   // End of input marker
};

/**
 * Token structure represents a single lexical unit with:
 * - type: The classification of the token
 * - value: The actual text content of the token
 */
struct Token {
    TokenType type;
    std::string value;
    
    // Constructor to initialize token properties
    Token(TokenType t, std::string v);
};

// Function to tokenize input string
std::vector<Token> tokenize(const std::string& input);

// Function to print tokens in a formatted table
void printTokens(const std::vector<Token>& tokens);

#endif // TOKENIZER_H