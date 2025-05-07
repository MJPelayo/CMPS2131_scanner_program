#include <cctype>   // For character classification functions (isdigit, isspace)
#include <iostream> // For input/output operations (cin, cout)
#include <vector>   // For dynamic array storage of tokens
using namespace std;

// Enum defining all possible token types
enum TokenType {
    NUMBER,        // One or more consecutive digits (0-9)
    UNKNOWN,       // Sequence of non-digit, non-whitespace characters
    END_OF_INPUT   // Signals the end of the input string
};

// Structure representing a lexical token
struct Token {
    TokenType type;  // Category of the token
    string value;    // The actual characters it represents
    
    // Constructor for easy token creation
    Token(TokenType typeOfToken, const string& valueOfToken) {
        type = typeOfToken;
        value = valueOfToken;
    }
};

// Function prototype - gets the next token from input
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input);  // Read entire line including spaces

    size_t position = 0;         // Current parsing position in input
    vector<Token> tokens;        // Collection of all parsed tokens

    // Tokenization loop - processes entire input
    while (true) {
        Token token = getNextToken(input, position);
        if (token.type == END_OF_INPUT) {
            break;  // Stop when input is fully processed
        }
        tokens.push_back(token);  // Store valid token
    }

    // Display all tokens with their types and values
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
                cout << "OTHER";  // Shouldn't occur with current TokenType
        }
        cout << ", Value: \"" << token.value << "\")\n";
    }

    return 0;
}

// Tokenizer function - extracts and returns the next token
Token getNextToken(const string& input, size_t& pos) {
    // Skip any whitespace before the next token
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check for end of input after skipping whitespace
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    // Handle number tokens (one or more digits)
    if (isdigit(input[pos])) {
        string number;
        // Collect all consecutive digits
        while (pos < input.length() && isdigit(input[pos])) {
            number += input[pos];
            pos++;
        }
        return Token(NUMBER, number);
    }

    // Handle unknown tokens (non-whitespace, non-digit sequences)
    string unknown = "";
    while (pos < input.length() && !isspace(input[pos])) {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}