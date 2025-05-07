#include <cctype>   // For character classification functions (isdigit, isspace)
#include <iostream> // For input/output operations
#include <vector>   // For dynamic array storage
#include <string>   // For string operations
using namespace std;

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
    string value;
    
    // Constructor to initialize token properties
    Token(TokenType t, string v) : type(t), value(v) {}
};

// Function prototypes
Token getNextToken(const string& input, size_t& pos);
void printTokens(const vector<Token>& tokens);

int main() {
    cout << "Enter an arithmetic expression: ";
    string input;
    getline(cin, input);  // Read the entire input line

    size_t pos = 0;             // Current position in input string
    vector<Token> tokens;       // List to store all recognized tokens

    // Tokenization loop - processes the entire input string
    while (true) {
        // Get the next token from input
        Token token = getNextToken(input, pos);
        
        // Stop when we reach end of input
        if (token.type == END_OF_INPUT) {
            break;
        }
        
        // Add the recognized token to our collection
        tokens.push_back(token);
    }

    // Display all tokens with their types and values
    printTokens(tokens);

    return 0;
}

/**
 * Prints all tokens in a formatted table
 * @param tokens The vector of tokens to display
 */
void printTokens(const vector<Token>& tokens) {
    cout << "\nToken Stream:\n";
    cout << "---------------------------------\n";
    cout << "Type        | Value\n";
    cout << "---------------------------------\n";
    
    for (const Token& token : tokens) {
        // Print token type in a fixed-width format
        switch(token.type) {
            case NUMBER:      cout << "NUMBER    "; break;
            case LEFT_PAREN:  cout << "L_PAREN   "; break;
            case RIGHT_PAREN: cout << "R_PAREN   "; break;
            case EXPONENT:    cout << "EXPONENT  "; break;
            case MULTIPLY:    cout << "MULTIPLY  "; break;
            case DIVIDE:      cout << "DIVIDE    "; break;
            case MODULUS:     cout << "MODULUS   "; break;
            case PLUS:       cout << "PLUS      "; break;
            case MINUS:      cout << "MINUS     "; break;
            default:         cout << "UNKNOWN   ";
        }
        
        // Print the token's value
        cout << "| " << token.value << endl;
    }
    cout << "---------------------------------\n";
}

/**
 * The core tokenizer function that extracts tokens from input string
 * @param input The string to tokenize
 * @param pos Current position in input (reference, will be updated)
 * @return The next Token found in the input
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
    switch(current) {
        case '(': 
            pos++; 
            return Token(LEFT_PAREN, "(");
        case ')': 
            pos++; 
            return Token(RIGHT_PAREN, ")");
        case '^': 
            pos++; 
            return Token(EXPONENT, "^");
        case '*': 
            pos++; 
            return Token(MULTIPLY, "*");
        case '/': 
            pos++; 
            return Token(DIVIDE, "/");
        case '%': 
            pos++; 
            return Token(MODULUS, "%");
        case '+': 
            pos++; 
            return Token(PLUS, "+");
        case '-': 
            // Special handling to distinguish between subtraction and negative numbers
            if (pos + 1 < input.length() && isdigit(input[pos+1])) {
                // This is a negative number (not subtraction)
                string num = "-";
                pos++;
                // Collect all digits
                while (pos < input.length() && isdigit(input[pos])) {
                    num += input[pos++];
                }
                // Check for decimal point
                if (pos < input.length() && input[pos] == '.') {
                    num += input[pos++];
                    while (pos < input.length() && isdigit(input[pos])) {
                        num += input[pos++];
                    }
                }
                return Token(NUMBER, num);
            }
            // Otherwise it's a subtraction operator
            pos++; 
            return Token(MINUS, "-");
    }

    // Phase 3: Handle numeric literals
    if (isdigit(current)) {
        string num;
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

    // Phase 4: Handle unknown tokens (anything not recognized above)
    string unknown(1, input[pos++]);
    return Token(UNKNOWN, unknown);
}