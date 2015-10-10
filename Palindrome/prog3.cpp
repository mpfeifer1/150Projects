#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool   recognizer        (string palindrome);
string decorruptionator  (string palindrome);
bool   detective         (string palindrome);
string cipher            (string palindrome);
string decipher          (string palindrome);

string toStandard        (string palindrome);
string getInput          ();

string getNextLetter     (char letter);
string getPreviousLetter (char letter);

int main() {
    bool quit = false;
    char choice;
    string phrase;

    do {
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

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                cout << "Enter a string: ";
                phrase = getInput();
                if(recognizer(phrase)) {
                    cout << phrase << " is a palindrome" << endl;

                } else {
                    cout << phrase << " is not a palindrome" << endl;
                }
                break;
            case '2':
                cout << "Entered 2" << endl;
                break;
            case '3':
                cout << "Entered 3" << endl;
                break;
            case '4':
                cout << "Enter a string: ";
                phrase = getInput();
                if(recognizer(phrase)) {
                    cout << "Palindrome cipher complete: " << cipher(toStandard(phrase)) << endl;
                } else {
                    cout << phrase << " is not a palindrome" << endl;
                }
                break;
            case '5':
                cout << "Enter a string: ";
                phrase = getInput();
                cout << "Palindromic decipher compxlete: " << decipher(toStandard(phrase)) << endl;
                break;

                break;
            case '6':
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }

        cout << endl;
    } while(!quit);
}

bool recognizer(string palindrome) {
    palindrome = toStandard(palindrome);
    for(int i = 0; i < palindrome.length() / 2; i++) {
        if(palindrome[i] != palindrome[palindrome.length() - 1 - i]) {
            return false;
        }
    }
    return true;
}

string decorruptionator(string palindrome) {
    // Find all odd letters, and two center letters. Check if (temporarily) removing any one makes it a palindrome
}

bool detective(string palindrome) {
    // Count all letters, if all are even (except one), return true
}

string cipher(string palindrome) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < palindrome.length(); i += 2) {
            palindrome.replace(i, 1, getPreviousLetter(palindrome.at(i)));
        }
    }
    return palindrome;
}

string decipher(string palindrome) {
    int rotations;
    cout << "Enter rotation distance (1-25): ";
    cin >> rotations;
    for(int j = 0; j < rotations; j++) {
        for(int i = 0; i < palindrome.length(); i += 2) {
            palindrome.replace(i, 1, getNextLetter(palindrome.at(i)));
        }
    }
    return palindrome;

}

string toStandard(string palindrome) {
    palindrome.erase(remove_if(palindrome.begin(), palindrome.end(), ::isspace), palindrome.end());
    palindrome.erase(remove_if(palindrome.begin(), palindrome.end(), ::ispunct), palindrome.end());
    transform(palindrome.begin(), palindrome.end(), palindrome.begin(), ::tolower);
    return palindrome;
}

string getInput() {
    string input;
    cin.ignore();
    getline(cin, input);
    return input;
}

string getNextLetter(char letter) {
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
        default:
            cout << "getNextLetter hit default" << endl;
            return "a";
    }
}

string getPreviousLetter(char letter) {
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
        default:
            cout << "getPreviousLetter hit default" << endl;
            return "z";
    }

}
