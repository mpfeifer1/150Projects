/*************************************************************************//**
 * @file
 *
 * @mainpage prog3 - Palindromes-R-Us
 *
 * @section course_section Course Information
 *
 * @author Michael Pfeifer
 *
 * @date 10/13/2015
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
   @endverbatim
 *
 *****************************************************************************/


// Preprocessor
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// Prototypes
bool recognizer         (char palindrome[], int length);
void decorruptionator   (char palindrome[], int length);
bool detective          (char palindrome[], int length);
void cipher             (char palindrome[], int length);
void decipher           (char palindrome[], int length);

void toStandard         (char palindrome[], int length);
int  getInput           (char palindrome[]);

char getNextLetter      (char letter);
char getPreviousLetter  (char letter);


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
    char choice;
    char phrase[81] = {'\0'};
    int length;

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
                if(recognizer(phrase, length)) {
                    cout << phrase << " is already a palindrome" << endl;
                } else {
                    decorruptionator(phrase, length);
                    if(phrase != "") {
                        cout << "The decorrupted palindrome is " << phrase << endl;
                    } else {
                        cout << "This palindrome can't be decorrupted" << endl;
                    }
                }
                break;

            case '3': // Detective
                cout << "Enter a string: ";
                length = getInput(phrase);
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

            default: // Bad Input
                cout << "Invalid option" << endl;
                break;
        }
        cout << endl;
    } while(!quit);
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function determines wheter a string is a palindrome
 *
 * @param[in]   palindrome  - the string to test
 *
 * @returns     true        - the input was a palindrome
 * @returns     false       - the input was not a palindrome
 *
 *****************************************************************************/
bool recognizer(char palindrome[], int length) {
    toStandard(palindrome, length);
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
 * @param[in]   palindrome  - the string to test
 *
 * @returns     ""          - the input cannot be made into a palindrome
 * @returns     [string]    - the input can be a palindrome, string contains a potential palindrome
 *
 *****************************************************************************/
void decorruptionator(char palindrome[], int length) {
    //char original[] = palindrome; // So that palindrome.erase doesn't wreck the origonal copy
    for(int i = 0; i <= length; i++) {
        //palindrome = original;
        //if(recognizer(palindrome.erase(i, 1), length)) { // Tests if the string is a palindrome without the Ith character
            // return palindrome;
            //break;
        //}
    }
    // return "";
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function determines wheter a string is a scrambled up palindrome
 *
 * @param[in]   palindrome  - the string to test
 *
 * @returns     true        - the input can be a palindrome
 * @returns     false       - the input can not be a palindrome
 *
 *****************************************************************************/
bool detective(char palindrome[], int length) {
    // Count all letters, if all are even (except one), return true
    int oddCount = 0;
    char index = 'a';
    for(int counter; counter < 26; counter++) {
        // Count instances of letter
        int instances = 0;
        for(int i = 0; i < length; i++) {
            if(index == palindrome[i]) {
                instances++;
            }
        }
        // Determine if there's an odd number of the character in the palindrome
        if(instances % 2 == 1) {
            oddCount++;
        }
        index = getNextLetter(index);
    }
    return oddCount < 2; // True if 0 or 1 odd number of character
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function scrambles a palindrome using a cipher
 *
 * @param[in]   palindrome  - the string to scramble
 *
 * @returns     [string]    - the scrambled palindrome
 *
 *****************************************************************************/
void cipher(char palindrome[], int length) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < length; i += 2) { // Counts by two to modify every other character
            // Replaces i with the previous character j times
            palindrome[i] = getPreviousLetter(palindrome[i]);
        }
    }
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function unscrambles a palindrome using a decipher
 *
 * @param[in]   palindrome  - the string to descramble
 *
 * @returns     [string]    - the unscrambled palindrome
 *
 *****************************************************************************/
void decipher(char palindrome[], int length) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < length; i += 2) { // Counts by two to modify every other character
            // Replaces i with the next character j times
            palindrome[i] = getNextLetter(palindrome[i]);
        }
    }
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function standardizes all input
 *
 * @param[in]   palindrome  - the palindrome to clean up
 *
 * @returns     [string]    - the new palindrome
 *
 *****************************************************************************/
void toStandard(char palindrome[], int length) {
    // Erases spaces, punctuation, and makes lowercase
    // palindrome = remove(begin(palindrome), end(palindrome), ::isspace());
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function gets a line of input from the user
 *
 * @returns     [string]    - the line from the user, as a string
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
 * This function gets the next letter in the alphabet
 *
 * @param[in]   letter      - the initial letter
 *
 * @returns     [char]      - the following letter
 * @returns     a           - error case
 *
 *****************************************************************************/
char getNextLetter(char letter) {
    // Hard-coded next letter
    switch(letter) {
        case 'a':
            return 'b';
        case 'b':
            return 'c';
        case 'c':
            return 'd';
        case 'd':
            return 'e';
        case 'e':
            return 'f';
        case 'f':
            return 'g';
        case 'g':
            return 'h';
        case 'h':
            return 'i';
        case 'i':
            return 'j';
        case 'j':
            return 'k';
        case 'k':
            return 'l';
        case 'l':
            return 'm';
        case 'm':
            return 'n';
        case 'n':
            return 'o';
        case 'o':
            return 'p';
        case 'p':
            return 'q';
        case 'q':
            return 'r';
        case 'r':
            return 's';
        case 's':
            return 't';
        case 't':
            return 'u';
        case 'u':
            return 'v';
        case 'v':
            return 'w';
        case 'w':
            return 'x';
        case 'x':
            return 'y';
        case 'y':
            return 'z';
        case 'z':
            return 'a';
        default: // Error case
            cout << "getNextLetter hit default" << endl;
            return 'a';
    }
}


/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function gets the previous letter in the alphabet
 *
 * @param[in]   letter      - the initial letter
 *
 * @returns     [char]      - the previous letter
 * @returns     z           - error case
 *
 *****************************************************************************/
char getPreviousLetter(char letter) {
    // Hard-coded previous letter
    switch(letter) {
        case 'a':
            return 'z';
        case 'b':
            return 'a';
        case 'c':
            return 'b';
        case 'd':
            return 'c';
        case 'e':
            return 'd';
        case 'f':
            return 'e';
        case 'g':
            return 'f';
        case 'h':
            return 'g';
        case 'i':
            return 'h';
        case 'j':
            return 'i';
        case 'k':
            return 'j';
        case 'l':
            return 'k';
        case 'm':
            return 'l';
        case 'n':
            return 'm';
        case 'o':
            return 'n';
        case 'p':
            return 'o';
        case 'q':
            return 'p';
        case 'r':
            return 'q';
        case 's':
            return 'r';
        case 't':
            return 's';
        case 'u':
            return 't';
        case 'v':
            return 'u';
        case 'w':
            return 'v';
        case 'x':
            return 'w';
        case 'y':
            return 'x';
        case 'z':
            return 'y';
        default: // Error case
            cout << "getPreviousLetter hit default" << endl;
            return 'z';
    }

}
