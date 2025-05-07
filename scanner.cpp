#include <cctype>   // For character classification functions (isdigit, isspace)
#include <iostream> // For input/output operations (cin, cout)
#include <vector>   // For dynamic array storage of tokens
using namespace std;

/**
 * TokenType enum defines all possible token categories our lexer recognizes.
 * Each arithmetic operator now has its own specific type for precise identification.
 */
enum TokenType {
    NUMBER,          // Numeric literals (e.g., "123", "-45", "+3.14")
    ADDITION,        // Specifically for the '+' operator
    SUBTRACTION,     // Specifically for the '-' operator
    MULTIPLICATION,  // Specifically for the '*' operator
    DIVISION,        // Specifically for the '/' operator
    UNKNOWN,         // Any unrecognized character sequence
    END_OF_INPUT     // Special marker indicating end of input
};

/**
 * Token structure represents a single lexical unit with:
 * - type: The classification of the token (from TokenType)
 * - value: The actual text the token represents
 */
struct Token {
    TokenType type;
    string value;
    
    // Constructor initializes token properties
    Token(TokenType typeOfToken, const string& valueOfToken) 
        : type(typeOfToken), value(valueOfToken) {}
};

// Forward declaration of tokenizer function
Token getNextToken(const string& input, size_t& pos);

int main() {
    string input;
    cout << "Enter input: ";  // Prompt user for input
    getline(cin, input);      // Read entire line including spaces

    size_t position = 0;             // Current parsing position in input
    vector<Token> tokens;            // Collection to store parsed tokens

    // Tokenization loop - processes entire input string
    while (true) {
        Token token = getNextToken(input, position);
        
        // Stop when we reach end of input
        if (token.type == END_OF_INPUT) {
            break;
        }
        
        tokens.push_back(token);  // Add valid token to our collection
    }

    // Display all tokens with their types and values
    for (const Token& token : tokens) {
        cout << "Token(Type: ";
        
        // Print human-readable token type
        switch (token.type) {
            case NUMBER:
                cout << "NUMBER";
                break;
            case ADDITION:
                cout << "ADDITION";
                break;
            case SUBTRACTION:
                cout << "SUBTRACTION";
                break;
            case MULTIPLICATION:
                cout << "MULTIPLICATION";
                break;
            case DIVISION:
                cout << "DIVISION";
                break;
            case UNKNOWN:
                cout << "UNKNOWN";
                break;
            default:
                cout << "OTHER";  // Fallback (shouldn't occur)
        }
        cout << ", Value: \"" << token.value << "\")\n";
    }

    return 0;
}

/**
 * getNextToken - The core tokenizer function that:
 * 1. Skips whitespace
 * 2. Identifies the next token at current position
 * 3. Advances the position
 * 4. Returns the token
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

    // Phase 2: Check for operators (done first to distinguish from number signs)
    switch (input[pos]) {
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
    }

    // Phase 3: Handle numeric literals (with optional sign)
    // Valid cases:
    // 1. Starts with digit (positive number)
    // 2. Starts with '+' followed by digit
    // 3. Starts with '-' followed by digit (negative number)
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

    // Phase 4: Handle unknown tokens (anything not matched above)
    string unknown;
    while (pos < input.length() && !isspace(input[pos]) &&
           input[pos] != '+' && input[pos] != '-' &&
           input[pos] != '*' && input[pos] != '/') {
        unknown += input[pos];
        pos++;
    }
    return Token(UNKNOWN, unknown);
}