#include <cctype>   // For character handling functions (isdigit, isspace)
#include <iostream> // For I/O operations (cin, cout)
#include <vector>   // For dynamic array storage of tokens
using namespace std;

// Enum defining the types of tokens the lexer can recognize
enum TokenType {
    DIGIT,         // Single numeric character (0-9)
    UNKNOWN,       // Sequence of non-digit characters
    END_OF_INPUT   // Special token indicating end of processing
};

// Token structure representing a lexical unit
struct Token {
    TokenType type;  // Classification of the token
    string value;    // The actual characters the token represents
    
    // Constructor for easy token creation
    Token(TokenType typeOfToken, const string& valueOfToken) {
        type = typeOfToken;
        value = valueOfToken;
    }
};

// Function prototype for the tokenizer
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input);  // Read entire line including spaces

    size_t position = 0;         // Current parsing position in input
    vector<Token> tokens;        // Storage for all parsed tokens

    // Tokenization loop - continues until end of input
    while (true) {
        Token token = getNextToken(input, position);
        if (token.type == END_OF_INPUT) {
            break;  // Exit loop when input is fully processed
        }
        tokens.push_back(token);  // Add valid token to collection
    }

    // Display all found tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];
        cout << "Token(Type: ";
        
        // Print token type in readable format
        switch (token.type) {
            case DIGIT: 
                cout << "DIGIT";
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

// Tokenizer function - extracts next token from input starting at pos
Token getNextToken(const string& input, size_t& pos) {
    // Skip any whitespace before the next token
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    // Check if we've reached end of input after skipping whitespace
    if (pos >= input.length()) {
        return Token(END_OF_INPUT, "");
    }

    // Check for single-digit tokens followed by whitespace or end
    if (isdigit(input[pos]) &&
        (pos + 1 >= input.length() || isspace(input[pos + 1]))) {
        string digit(1, input[pos]);
        pos++; 
        return Token(DIGIT, digit);
    }

    // Handle unknown tokens (sequences of non-whitespace, non-digit characters)
    string unknown = "";
    while (pos < input.length() && !isspace(input[pos])) {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}