#include <cctype>   // For isdigit(), isspace() character functions
#include <iostream> // For console input/output
#include <vector>   // For storing tokens dynamically
using namespace std;

/**
 * Enum defining all token types our lexer recognizes.
 * Includes arithmetic operators, parentheses, numbers, and control tokens.
 */
enum TokenType {
    NUMBER,          // Numeric values (e.g., 42, -3.14)
    ADDITION,        // Addition operator '+'
    SUBTRACTION,     // Subtraction operator '-'
    MULTIPLICATION,  // Multiplication operator '*'
    DIVISION,        // Division operator '/'
    LEFT_PAREN,      // Opening parenthesis '('
    RIGHT_PAREN,     // Closing parenthesis ')'
    UNKNOWN,         // Unrecognized characters
    END_OF_INPUT     // End of input marker
};

/**
 * Token structure represents the smallest meaningful unit in the input.
 * Contains:
 * - type: The classification of the token (from TokenType)
 * - value: The actual text content of the token
 */
struct Token {
    TokenType type;
    string value;
    
    // Constructor to initialize token properties
    Token(TokenType typeOfToken, const string& valueOfToken) 
        : type(typeOfToken), value(valueOfToken) {}
};

// Forward declaration of the tokenizer function
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter arithmetic expression: ";
    getline(cin, input);  // Read entire input line

    size_t position = 0;         // Current parsing position
    vector<Token> tokens;        // List to store all tokens

    // Main tokenization loop
    while (true) {
        // Get next token from input
        Token token = getNextToken(input, position);
        
        // Stop when end of input is reached
        if (token.type == END_OF_INPUT) {
            break;
        }
        
        // Add valid token to our collection
        tokens.push_back(token);
    }

    // Display all tokens with their types and values
    for (const Token& token : tokens) {
        cout << "Token(Type: ";
        
        // Print human-readable token type
        switch (token.type) {
            case NUMBER: cout << "NUMBER"; break;
            case ADDITION: cout << "ADDITION"; break;
            case SUBTRACTION: cout << "SUBTRACTION"; break;
            case MULTIPLICATION: cout << "MULTIPLICATION"; break;
            case DIVISION: cout << "DIVISION"; break;
            case LEFT_PAREN: cout << "LEFT_PAREN"; break;
            case RIGHT_PAREN: cout << "RIGHT_PAREN"; break;
            case UNKNOWN: cout << "UNKNOWN"; break;
            default: cout << "OTHER";  // Shouldn't occur with current TokenType
        }
        cout << ", Value: \"" << token.value << "\")\n";
    }

    return 0;
}

/**
 * Core tokenizer function that extracts tokens from input string.
 * 
 * @param input The string to tokenize
 * @param pos Current position in input (updated as we tokenize)
 * @return The next Token found in the input
 * 
 * Processing order:
 * 1. Skips whitespace
 * 2. Checks for end of input
 * 3. Identifies single-character tokens (operators/parentheses)
 * 4. Handles numeric literals (with optional sign)
 * 5. Collects unknown tokens as fallback
 */
Token getNextToken(const string& input, size_t& pos) {
    // Phase 1: Skip all whitespace characters
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check if we've reached end of input after skipping whitespace
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    char current = input[pos];  // Current character being examined
    
    // Phase 2: Handle single-character tokens
    switch (current) {
        case '+': 
            pos++; 
            return Token(ADDITION, "+");
        case '-': 
            pos++; 
            return Token(SUBTRACTION, "-");
        case '*': 
            pos++; 
            return Token(MULTIPLICATION, "*");
        case '/': 
            pos++; 
            return Token(DIVISION, "/");
        case '(':
            pos++;
            return Token(LEFT_PAREN, "(");
        case ')':
            pos++;
            return Token(RIGHT_PAREN, ")");
    }

    // Phase 3: Handle numeric literals
    // Valid cases:
    // 1. Starts with digit (positive number)
    // 2. Starts with '+' followed by digit
    // 3. Starts with '-' followed by digit (negative number)
    if (isdigit(current) || 
        ((current == '+' || current == '-') && 
         pos + 1 < input.length() && isdigit(input[pos+1]))) {
        
        string number;
        // Include sign if present
        if (current == '+' || current == '-') {
            number += current;
            pos++;
        }
        
        // Collect all consecutive digits
        while (pos < input.length() && isdigit(input[pos])) {
            number += input[pos];
            pos++;
        }
        return Token(NUMBER, number);
    }

    // Phase 4: Handle unknown tokens
    // Any sequence not whitespace, operator, or parenthesis
    string unknown;
    while (pos < input.length() && !isspace(input[pos]) &&
           input[pos] != '+' && input[pos] != '-' &&
           input[pos] != '*' && input[pos] != '/' &&
           input[pos] != '(' && input[pos] != ')') {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}