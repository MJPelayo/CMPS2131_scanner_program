#include <iostream>   // For input/output operations (cout, endl)
#include <string>     // For using the string class
#include <cctype>     // For character classification functions (isdigit)
using namespace std;  // Use the standard namespace to avoid std:: prefixes


void scanDigit(const string& input) {
    // Check if the input length is not exactly 1 (i.e., not a single character)
    if (input.length() != 1) {
        cout << "Error: Input must be a single character." << endl;
        return;  // Exit the function early if invalid
    }

    // Extract the first (and only) character from the input string
    char c = input[0];

    // Check if the character is a digit (0-9) using isdigit()
    if (isdigit(c)) {
        cout << "Valid digit: " << c << endl;  // Print success message
    } else {
        // Print error message if the character is not a digit
        cout << "Error: '" << c << "' is not a valid digit (0-9)." << endl;
    }
}