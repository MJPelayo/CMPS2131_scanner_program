#include <cctype>   // For character classification functions (isdigit, isspace)
#include <iostream> // For input/output operations (cin, cout)
#include <vector>   // For using dynamic arrays (vector)
using namespace std; // Use the standard namespace to avoid std:: prefixes

// Define token types for the lexer
enum TokenType {
    DIGIT,         // Represents a numeric digit (0-9)
    UNKNOWN,       // Represents an unrecognized character
    END_OF_INPUT   // Signals the end of the input string
};

// Token structure to store type and literal value
struct Token {
    TokenType type; // Type of the token (DIGIT, UNKNOWN, etc.)
    string value;   // The actual character(s) the token represents
};

// Forward declaration of the tokenizer function
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input); // Read entire line of input

    size_t position = 0;         // Tracks current position in the input string
    vector<Token> tokens;        // Stores all parsed tokens

    // Tokenization loop
    while (true) {
        Token token = getNextToken(input, position);
        if (token.type == END_OF_INPUT) {
            break; // Stop when end of input is reached
        }
        tokens.push_back(token); // Add valid token to the list
    }

    // Print all tokens with their types and values
    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];
        cout << "Token(Type: ";
        
        // Print token type in human-readable form
        switch (token.type) {
            case DIGIT: 
                cout << "DIGIT";
                break;
            case UNKNOWN: 
                cout << "UNKNOWN";
                break;
            default: 
                cout << "OTHER"; // Should never occur with current TokenType
        }
        cout << ", Value: \"" << token.value << "\")\n";
    }

    return 0;
}

// Tokenizer function - extracts next token from input starting at pos
Token getNextToken(const string& input, size_t& pos) {
    // Skip any whitespace characters
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check for end of input after skipping whitespace
    if (pos >= input.length()) {
        return { END_OF_INPUT, "" }; // Return special end token
    }

    // Check if current character is a digit
    if (isdigit(input[pos])) {
        string digit(1, input[pos]); // Convert char to string
        pos++; // Move to next character
        return { DIGIT, digit }; // Return digit token
    }

    // If character is neither whitespace nor digit, return as unknown
    return { UNKNOWN, string(1, input[pos++]) };
}