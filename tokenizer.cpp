#include "tokenizer.h"
#include <cctype>
#include <iostream>

/**
 * Token constructor implementation
 * @param t Token type
 * @param v Token value
 */
Token::Token(TokenType t, std::string v) : type(t), value(v) {}

/**
 * Helper function to get the next token from input
 * @param input The string to tokenize
 * @param pos Current position in input (reference, will be updated)
 * @return The next Token found in the input
 */
static Token getNextToken(const std::string& input, size_t& pos) {
    // Skip whitespace characters
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check for end of input
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    char current = input[pos];  // Current character being examined
    
    // Handle single-character tokens
    switch(current) {
        case '(': pos++; return Token(LEFT_PAREN, "(");
        case ')': pos++; return Token(RIGHT_PAREN, ")");
        case '^': pos++; return Token(EXPONENT, "^");
        case '*': pos++; return Token(MULTIPLY, "*");
        case '/': pos++; return Token(DIVIDE, "/");
        case '%': pos++; return Token(MODULUS, "%");
        case '+': pos++; return Token(PLUS, "+");
        case '-': 
            // Check if this is a negative number
            if (pos + 1 < input.length() && isdigit(input[pos+1])) {
                std::string num = "-";
                pos++;
                // Collect all digits
                while (pos < input.length() && isdigit(input[pos])) {
                    num += input[pos++];
                }
                // Check for decimal point
                if (pos < input.length() && input[pos] == '.') {
                    num += input[pos++];
                    // Collect digits after decimal
                    while (pos < input.length() && isdigit(input[pos])) {
                        num += input[pos++];
                    }
                }
                return Token(NUMBER, num);
            }
            // Otherwise it's a subtraction operator
            pos++; return Token(MINUS, "-");
    }

    // Handle numeric literals
    if (isdigit(current)) {
        std::string num;
        // Collect all consecutive digits
        while (pos < input.length() && isdigit(input[pos])) {
            num += input[pos++];
        }
        // Check for decimal point
        if (pos < input.length() && input[pos] == '.') {
            num += input[pos++];
            // Collect digits after decimal
            while (pos < input.length() && isdigit(input[pos])) {
                num += input[pos++];
            }
        }
        return Token(NUMBER, num);
    }

    // Handle unknown tokens
    std::string unknown(1, input[pos++]);
    return Token(UNKNOWN, unknown);
}

/**
 * Tokenize the entire input string
 * @param input The string to tokenize
 * @return Vector of tokens
 */
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t pos = 0;
    
    while (true) {
        Token token = getNextToken(input, pos);
        if (token.type == END_OF_INPUT) break;
        tokens.push_back(token);
    }
    
    return tokens;
}

/**
 * Print tokens in a formatted table
 * @param tokens The vector of tokens to display
 */
void printTokens(const std::vector<Token>& tokens) {
    std::cout << "\nToken Stream:\n";
    std::cout << "---------------------------------\n";
    std::cout << "Type        | Value\n";
    std::cout << "---------------------------------\n";
    
    for (const Token& token : tokens) {
        // Print token type in a fixed-width format
        switch(token.type) {
            case NUMBER:      std::cout << "NUMBER    "; break;
            case LEFT_PAREN:  std::cout << "L_PAREN   "; break;
            case RIGHT_PAREN: std::cout << "R_PAREN   "; break;
            case EXPONENT:    std::cout << "EXPONENT  "; break;
            case MULTIPLY:    std::cout << "MULTIPLY  "; break;
            case DIVIDE:      std::cout << "DIVIDE    "; break;
            case MODULUS:     std::cout << "MODULUS   "; break;
            case PLUS:       std::cout << "PLUS      "; break;
            case MINUS:      std::cout << "MINUS     "; break;
            default:         std::cout << "UNKNOWN   ";
        }
        
        // Print the token's value
        std::cout << "| " << token.value << std::endl;
    }
    std::cout << "---------------------------------\n";
}