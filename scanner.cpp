#include <cctype>   // For isdigit() and isspace() functions
#include <iostream> // For input/output operations
#include <vector>   // For storing tokens
using namespace std;

// Enum defining all possible token types
enum TokenType {
    NUMBER,     // Numeric literals (e.g., 123, -45, +67)
    OPERATOR,   // Arithmetic operators (+, -, *, /)
    UNKNOWN,    // Unrecognized character sequences
    END_OF_INPUT // End of input marker
};

// Structure representing a lexical token
struct Token {
    TokenType type;  // The type/category of the token
    string value;    // The actual text the token represents
    
    // Constructor to initialize token properties
    Token(TokenType typeOfToken, const string& valueOfToken) 
        : type(typeOfToken), value(valueOfToken) {}
};

// Function prototype - gets the next token from input
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input);  // Read the entire input line

    size_t position = 0;         // Current position in input string
    vector<Token> tokens;        // List to store all tokens

    // Main tokenization loop
    while (true) {
        Token token = getNextToken(input, position);
        if (token.type == END_OF_INPUT) {
            break;  // Exit when we've processed all input
        }
        tokens.push_back(token);  // Add token to our collection
    }

    // Display all tokens with their types and values
    for (const Token& token : tokens) {
        cout << "Token(Type: ";
        switch (token.type) {
            case NUMBER:
                cout << "NUMBER";
                break;
            case OPERATOR:
                cout << "OPERATOR";
                break;
            case UNKNOWN:
                cout << "UNKNOWN";
                break;
            default:
                cout << "OTHER";  // Shouldn't occur normally
        }
        cout << ", Value: \"" << token.value << "\")\n";
    }

    return 0;
}

/* 
 * Tokenizer function - extracts and returns the next token from input
 * starting at position pos (which it updates)
 */
Token getNextToken(const string& input, size_t& pos) {
    // Skip any whitespace characters
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check if we've reached end of input
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    // First check for operators (+, -, *, /)
    if (input[pos] == '+' || input[pos] == '-' || 
        input[pos] == '*' || input[pos] == '/') {
        char op = input[pos];
        pos++;
        return Token(OPERATOR, string(1, op));
    }

    // Check for numbers (with optional sign)
    // Either starts with digit, or sign followed by digit
    if (isdigit(input[pos]) || 
        ((input[pos] == '+' || input[pos] == '-') && 
         pos + 1 < input.length() && isdigit(input[pos+1]))) {
        
        string number;
        // Include sign if present
        if (input[pos] == '+' || input[pos] == '-') {
            number += input[pos];
            pos++;
        }
        
        // Collect all consecutive digits
        while (pos < input.length() && isdigit(input[pos])) {
            number += input[pos];
            pos++;
        }
        return Token(NUMBER, number);
    }

    // Handle unknown tokens (anything not whitespace, operator, or number)
    string unknown;
    while (pos < input.length() && !isspace(input[pos]) &&
           input[pos] != '+' && input[pos] != '-' &&
           input[pos] != '*' && input[pos] != '/') {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}