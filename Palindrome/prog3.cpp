/*************************************************************************//**
 * @file
 *
 * @mainpage prog3 - Palindromes-R-Us
 *
 * @section course_section Course Information
 *
 * @author Michael Pfeifer
 *
 * @date 10/23/2015
 *
 * @par Professor:
 *         Val Manes
 *
 * @par Course:
 *         Computer Science - CSC150 - 3:00 PM
 *
 * @par Location:
 *         Clasroom Building - 110
 *
 * @section program_section Program Information
 *
 * @details This program has 5 different options. It will detect whether a string is a palindrome, can fix a palindrome with an extra character inside, can detect if a palindrome is scrambled up, and can cipher/decipher palindromes
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Standard compilation
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe
   or
   g++ prog3.cpp
   ./a.out
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------------
   Oct  9, 2015  Made menu, toStandard, getInput, started cipher
   Oct 10, 2015  Finished cipher and decipher, debugged methods
   Oct 11, 2015  Finished decorruptionator, started detective
   Oct 12, 2015  Completed detective, debugged more methods
   Oct 13, 2015  Completed project, added Doxygen documentation
   Oct 22, 2015  Converted everthing to c-style stings. Thanks for that BTW
   Oct 23, 2015  Finished the project. For real this time.
   Oct 27, 2015  Added more comments
   Nov  1, 2015  Rewrote cipher and decipher
   Nov  4, 2015  Refactored to ASCII values, optimized toStandard
   Nov  5, 2015  Fixed weird edge cases, like spaces in cipher and ASCII overflow in decipher
   @endverbatim
 *
 *****************************************************************************/


// Preprocessor
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

// Prototypes
bool recognizer         (char palindrome[], int length);
void decorruptionator   (char palindrome[], int length);
bool detective          (char palindrome[], int length);
void cipher             (char palindrome[], int length);
void decipher           (char palindrome[], int length);

int  toStandard         (char palindrome[], int length);
int  getInput           (char palindrome[]);
int  remove             (char palindrome[], int length, int index);

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function outputs a main menu screen, and branches out to the various palindrome methods.
 *
 * @returns     0               - program ran successful.
 *
 *****************************************************************************/
int main() {
    // Quit will keep the program looping until the user wants to quit
    bool quit = false;
    // Stores user input
    char choice;
    char phrase[81] = {'\0'};
    // Running length of string
    int  length;

    do {
        // Output main menu
        cout << "Welcome to Palindromes-R-Us!" << endl;
        cout << "Select an option" << endl;
        cout << endl;
        cout << "1. Palindrome Recognizer" << endl;
        cout << "2. Palindrome Decorruptionator" << endl;
        cout << "3. Palindrome Detective" << endl;
        cout << "4. Palindrome Cipher" << endl;
        cout << "5. Palindrome Decipher" << endl;
        cout << "6. Quit" << endl;
        cout << endl;

        // Get input
        cout << "Enter choice: ";
        cin >> choice;

        // Break away based on selection
        switch(choice) {

            case '1': // Recognizer
                cout << "Enter a string: ";
                length = getInput(phrase);
                if(recognizer(phrase, length)) {
                    cout << phrase << " is a palindrome" << endl;

                } else {
                    cout << phrase << " is not a palindrome" << endl;
                }
                break;

            case '2': // Decorruptionator
                cout << "Enter a string: ";
                length = getInput(phrase);
                // Detects if already palindrome
                if(recognizer(phrase, length)) {
                    cout << phrase << " is already a palindrome" << endl;
                } else { // Determines if if can be decoruppted
                    decorruptionator(phrase, length);
                    if(phrase[0] != '\0') {
                        cout << "The decorrupted palindrome is " << phrase << endl;
                    } else {
                        cout << "This palindrome can't be decorrupted" << endl;
                    }

                }
                break;

            case '3': // Detective
                cout << "Enter a string: ";
                length = getInput(phrase);
                // Detects if it's a palindrome
                if(detective(phrase, length)) {
                    cout << "This can be a palindrome" << endl;
                } else {
                    cout << "This can't be a palindrome" << endl;
                }
                break;

            case '4': // Cipher
                cout << "Enter a string: ";
                length = getInput(phrase);
                toStandard(phrase, length);
                cout << phrase << endl;
                cipher(phrase, length);
                cout << "Palindrome cipher complete: " << phrase << endl;
                break;

            case '5': // Decipher
                cout << "Enter a string: ";
                length = getInput(phrase);
                toStandard(phrase, length);
                decipher(phrase, length);
                cout << "Palindromic decipher complete: " << phrase << endl;
                break;

            case '6': // Quit
                cout << "Goodbye!" << endl;
                quit = true;
                break;

            default:  // Bad Input
                cout << "Invalid option" << endl;
                break;
        }
        cout << endl;

        for(int i = 0; i < strlen(phrase); i++) {
            phrase[i] = '\0'; // Resets string to be empty
        }

    } while(!quit);
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function determines wheter a string is a palindrome
 *
 * @param[in][out]  palindrome  - the string to test
 * @param[in]       length      - the length of the string
 *
 * @returns         true        - the input was a palindrome
 * @returns         false       - the input was not a palindrome
 *
 *****************************************************************************/
bool recognizer(char palindrome[], int length) {
    length = toStandard(palindrome, length);
    for(int i = 0; i < length / 2; i++) {
        // Tests if first equals last, 2nd equals 2nd to last, etc...
        if(palindrome[i] != palindrome[length - 1 - i]) {
            return false;
        }
    }
    return true;
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function determines wheter a string is a palindrome, with one extra character
 *
 * @param[in][out]  palindrome  - the string to test
 * @param[in]       length      - the length of the string
 *
 *****************************************************************************/
void decorruptionator(char palindrome[], int length) {
    // Backs up original string
    char original[81] = {'\0'};
    strcpy(original, palindrome);

    // Guess-and-check by removing one character from string and detecting if palindrome
    for(int i = 0; i < length; i++) {
        strcpy(palindrome, original);
        remove(palindrome, length, i);
        if(recognizer(palindrome, length - 1)) { // Tests if the string is a palindrome without the Ith character
            return;
        }
    }

    palindrome[0] = '\0'; // Sets string to "" if a palindrome isn't possible
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function determines wheter a string is a scrambled up palindrome
 *
 * @param[in]   palindrome  - the string to test
 * @param[in]   length      - the length of the string
 *
 * @returns     true        - the input can be a palindrome
 * @returns     false       - the input can not be a palindrome
 *
 *****************************************************************************/
bool detective(char palindrome[], int length) {
    // Count all letters, if all are even (except one), return true
    char alphabet[26] = {'\0'}; // Array that stores count of all letters
    int oddCount = 0, i = 0;

    for(i = 0; i < length; i++) {
        // Count instances of every letter
        alphabet[palindrome[i] - 'a']++;
    }
    for(i = 0; i < 26; i++) {
        // Counts all odd instances
        if(alphabet[i] % 2 == 1) {
            oddCount++;
        }
    }

    return oddCount < 2; // True if 0 or 1 odd number of character
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function scrambles a palindrome using a cipher
 *
 * @param[in][out]  palindrome  - the string to scramble
 * @param[in]       length      - the length of the string
 *
 *****************************************************************************/
void cipher(char palindrome[], int length) {
    // Input rotations
    int rotations;
    length = strlen(palindrome);
    do {
        cout << "Enter rotation distance (1-25): ";
        cin >> rotations;
    } while(rotations < 0 || rotations > 25);
    toStandard(palindrome, length);
    for(int i = 0; i < length; i += 2) { // Counts by two to modify every other character
        palindrome[i] -= rotations;
        while(palindrome[i] < 'a') { // Checks if too low
            palindrome[i] += 26;
        }
    }
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function unscrambles a palindrome using a decipher
 *
 * @param[in][out]  palindrome  - the string to descramble
 * @param[in]       length      - the length of the string
 *
 *****************************************************************************/
void decipher(char palindrome[], int length) {
    // Input rotations
    int rotations;
    do {
        cout << "Enter rotation distance (1-25): ";
        cin >> rotations;
    } while(rotations < 0 || rotations > 25);
    for(int i = 0; i < length; i += 2) { // Counts by two to modify every other character
        // Replaces i with the next character j times
        palindrome[i] += rotations;
        while(palindrome[i] > 'z' || palindrome[i] < 0) { // Checks if too high, or if ASCII value is negative (because setting it too high will make it negative because it only uses the standard ASCII table)
            palindrome[i] -= 26;
        }
    }
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function standardizes all input
 *
 * @param[in][out]  palindrome  - the palindrome to clean up
 * @param[in]       length      - the length of the palindrome
 *
 * @returns         [int]       - the new length of the palindrome
 *
 *****************************************************************************/
int toStandard(char palindrome[], int length) {
    // Erases spaces, punctuation, and makes lowercase
    char temp[81] = {'\0'};
    int j = 0;
    for(int i = 0; i < strlen(palindrome); i++) {
        if((palindrome[i] >= 'a' &&  palindrome[i] <= 'z') || (palindrome [i] >= 'A' && palindrome[i] <= 'Z')) {
            temp[j] = tolower(palindrome[i]);
            j++;
        }
    }
    strcpy(palindrome, temp);
    return strlen(palindrome);
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function gets a line of input from the user
 *
 * @param[in][out]  palindrome  - the string to print to
 *
 * @returns         [int]       - the length of the palindrome
 * @returns         -1          - error case
 *
 *****************************************************************************/
int getInput(char palindrome[]) {
    cin.ignore();
    cin.getline(palindrome, 80); // Gets the whole line instead of one word

    // Calculate Length
    for(int i = 0; i <= 81; i++) {
        if(palindrome[i] == '\0') {
            return i;
        }
    }

    return -1; // Error Case
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function removes an index from a string
 *
 * @param[in][out]  palindrome  - the string to remove from
 * @param[in]       length      - the length of the string
 * @param[in]       index       - the index of the character to remove
 *
 * @returns         [int]       - the new length of the string
 *
 *****************************************************************************/
int remove(char palindrome[], int length, int index) {
    // Slides all characters after index to the left one
    int i = 0;
    for(i = index; i < length; i++) {
        palindrome[i] = palindrome[i + 1];
    }
    palindrome[i] = '\0';
    return length - 1;
}
