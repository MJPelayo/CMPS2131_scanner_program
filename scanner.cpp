#include <cctype>   // For character handling (isdigit, isspace)
#include <iostream> // For I/O operations (cin, cout)
#include <vector>   // For storing tokens
using namespace std;

// Token types the lexer can recognize
enum TokenType {
    NUMBER,        // Signed or unsigned numeric value
    UNKNOWN,       // Unrecognized character sequence
    END_OF_INPUT   // End of input marker
};

// Structure representing a lexical token
struct Token {
    TokenType type;  // Classification of token
    string value;    // Actual text of token
    
    // Constructor for clean token creation
    Token(TokenType typeOfToken, const string& valueOfToken) {
        type = typeOfToken;
        value = valueOfToken;
    }
};

// Function prototype for tokenizer
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input);  // Read full input line

    size_t position = 0;         // Current parsing position
    vector<Token> tokens;        // Collection of parsed tokens

    // Main tokenization loop
    while (true) {
        Token token = getNextToken(input, position);
        if (token.type == END_OF_INPUT) {
            break;  // Stop when input exhausted
        }
        tokens.push_back(token);  // Store valid token
    }

    // Display all tokens with classification
    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];
        cout << "Token(Type: ";
        
        // Print human-readable token type
        switch (token.type) {
            case NUMBER: 
                cout << "NUMBER";
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

// Tokenizer function - extracts next token from input
Token getNextToken(const string& input, size_t& pos) {
    // Skip leading whitespace
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check for end of input
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    // Handle numbers (with optional sign)
    if (input[pos] == '+' || input[pos] == '-' || isdigit(input[pos])) {
        string number;
        
        // Capture optional sign
        if (input[pos] == '+' || input[pos] == '-') {
            number += input[pos];
            pos++;
            // Validate sign is followed by digit
            if (pos >= input.length() || !isdigit(input[pos])) {
                return Token(UNKNOWN, number);  // Lone sign is unknown
            }
        }
        
        // Capture all consecutive digits
        while (pos < input.length() && isdigit(input[pos])) {
            number += input[pos];
            pos++;
        }
        return Token(NUMBER, number);
    }

    // Handle unknown tokens (non-whitespace, non-number sequences)
    string unknown;
    while (pos < input.length() && !isspace(input[pos])) {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}