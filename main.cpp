#include "tokenizer.h"
#include <iostream>

/**
 * Main program entry point
 * Demonstrates the tokenizer with user input
 */
int main() {
    // Prompt user for input
    std::cout << "Enter an arithmetic expression: ";
    std::string input;
    std::getline(std::cin, input);  // Read the entire input line

    // Tokenize the input string
    std::vector<Token> tokens = tokenize(input);

    // Display the resulting tokens
    printTokens(tokens);

    return 0;
}