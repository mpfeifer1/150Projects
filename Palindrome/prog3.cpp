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
   Oct 10, 2015  Worked on Doxygen documentation
   @endverbatim
 *
 *****************************************************************************/


// Preprocessor
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Prototypes
bool   recognizer        (string palindrome);
string decorruptionator  (string palindrome);
bool   detective         (string palindrome);
string cipher            (string palindrome);
string decipher          (string palindrome);

string toStandard        (string palindrome);
string getInput          ();

string getNextLetter     (char letter);
string getPreviousLetter (char letter);


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
    string phrase;

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
                phrase = getInput();
                if(recognizer(phrase)) {
                    cout << phrase << " is a palindrome" << endl;

                } else {
                    cout << phrase << " is not a palindrome" << endl;
                }
                break;
            case '2': // Decorruptionator
                cout << "Enter a string: ";
                phrase = getInput();
                if(recognizer(phrase)) {
                    cout << phrase << " is already a palindrome" << endl;
                } else if(decorruptionator(phrase) != "") {
                    cout << "The decorrupted palindrome is " << decorruptionator(phrase) << endl;
                } else {
                    cout << "This palindrome can't be decorrupted" << endl;;
                }
                break;
            case '3': // Detective
                cout << "Enter a string: ";
                phrase = getInput();
                if(detective(phrase)) {
                    cout << "This can be a palindrome" << endl;
                } else {
                    cout << "This can't be a palindrome" << endl;
                }
                break;
            case '4': // Cipher
                cout << "Enter a string: ";
                phrase = getInput();
                if(recognizer(phrase)) {
                    cout << "Palindrome cipher complete: " << cipher(toStandard(phrase)) << endl;
                } else {
                    cout << phrase << " is not a palindrome" << endl;
                }
                break;
            case '5': // Decipher
                cout << "Enter a string: ";
                phrase = getInput();
                cout << "Palindromic decipher complete: " << decipher(toStandard(phrase)) << endl;
                break;

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
bool recognizer(string palindrome) {
    palindrome = toStandard(palindrome);
    for(int i = 0; i < palindrome.length() / 2; i++) {
        // Tests if first equals last, 2nd equals 2nd to last, etc...
        if(palindrome[i] != palindrome[palindrome.length() - 1 - i]) {
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
string decorruptionator(string palindrome) {
    string original = palindrome; // So that palindrome.erase doesn't wreck the origonal copy
    for(int i = 0; i < palindrome.length(); i++) {
        palindrome = original;
        if(recognizer(palindrome.erase(i, 1))) { // Tests if the string is a palindrome without the Ith character
            return palindrome;
        }
    }
    return "";
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
bool detective(string palindrome) {
    // Count all letters, if all are even (except one), return true
    int oddCount = 0;
    char index = 'a';
    for(int counter; counter < 26; counter++) {
        // Count instances of letter
        int instances = 0;
        for(int i = 0; i < palindrome.length(); i++) {
            if(index == palindrome[i]) {
                instances++;
            }
        }
        // Determine if there's an odd number of the character in the palindrome
        if(instances % 2 == 1) {
            oddCount++;
        }
        index = getNextLetter(index)[0];
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
string cipher(string palindrome) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < palindrome.length(); i += 2) { // Counts by two to modify every other character
            // Replaces i with the previous character j times
            palindrome.replace(i, 1, getPreviousLetter(palindrome.at(i)));
        }
    }
    return palindrome;
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
string decipher(string palindrome) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < palindrome.length(); i += 2) { // Counts by two to modify every other character
            // Replaces i with the next character j times
            palindrome.replace(i, 1, getNextLetter(palindrome.at(i)));
        }
    }
    return palindrome;

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
string toStandard(string palindrome) {
    // Erases spaces, punctuation, and makes lowercase
    palindrome.erase(remove_if(palindrome.begin(), palindrome.end(), ::isspace), palindrome.end());
    palindrome.erase(remove_if(palindrome.begin(), palindrome.end(), ::ispunct), palindrome.end());
    transform(palindrome.begin(), palindrome.end(), palindrome.begin(), ::tolower);
    return palindrome;
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
string getInput() {
    string input;
    cin.ignore();
    getline(cin, input); // Gets the whole line instead of one word
    return input;
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
string getNextLetter(char letter) {
    // Hard-coded next letter
    switch(letter) {
        case 'a':
            return "b";
        case 'b':
            return "c";
        case 'c':
            return "d";
        case 'd':
            return "e";
        case 'e':
            return "f";
        case 'f':
            return "g";
        case 'g':
            return "h";
        case 'h':
            return "i";
        case 'i':
            return "j";
        case 'j':
            return "k";
        case 'k':
            return "l";
        case 'l':
            return "m";
        case 'm':
            return "n";
        case 'n':
            return "o";
        case 'o':
            return "p";
        case 'p':
            return "q";
        case 'q':
            return "r";
        case 'r':
            return "s";
        case 's':
            return "t";
        case 't':
            return "u";
        case 'u':
            return "v";
        case 'v':
            return "w";
        case 'w':
            return "x";
        case 'x':
            return "y";
        case 'y':
            return "z";
        case 'z':
            return "a";
        default: // Error case
            cout << "getNextLetter hit default" << endl;
            return "a";
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
string getPreviousLetter(char letter) {
    // Hard-coded previous letter
    switch(letter) {
        case 'a':
            return "z";
        case 'b':
            return "a";
        case 'c':
            return "b";
        case 'd':
            return "c";
        case 'e':
            return "d";
        case 'f':
            return "e";
        case 'g':
            return "f";
        case 'h':
            return "g";
        case 'i':
            return "h";
        case 'j':
            return "i";
        case 'k':
            return "j";
        case 'l':
            return "k";
        case 'm':
            return "l";
        case 'n':
            return "m";
        case 'o':
            return "n";
        case 'p':
            return "o";
        case 'q':
            return "p";
        case 'r':
            return "q";
        case 's':
            return "r";
        case 't':
            return "s";
        case 'u':
            return "t";
        case 'v':
            return "u";
        case 'w':
            return "v";
        case 'x':
            return "w";
        case 'y':
            return "x";
        case 'z':
            return "y";
        default: // Error case
            cout << "getPreviousLetter hit default" << endl;
            return "z";
    }

}
