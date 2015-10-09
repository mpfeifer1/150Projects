#include <iostream>
#include <string>

using namespace std;

bool   recognizer       (string palindrome);
string decorruptionator (string palindrome);
bool   detective        (string palindrome);
string cipher           (string palindrome);
string decipher         (string palindrome);

string toStandard       (string palindrome);
string getInput         ();

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
                cout << "Entered 4" << endl;
                break;
            case '5':
                cout << "Entered 5" << endl;
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
    cout << "Palindrome length is " << palindrome.length() << endl;
    for(int i = 0; i < palindrome.length() / 2; i++) {
        if(palindrome[i] != palindrome[palindrome.length() - 1 - i]) {
            return false;
        }
    }
    return true;
}

string decorruptionator(string palindrome) {

}

bool detective(string palindrome) {

}

string cipher(string palindrome) {

}

string decipher(string palindrome) {

}

string toStandard(string palindrome) {
    return "test"; // Ignore spaces, punctuation, capitalization
}

string getInput() {
    string input;
    cin.ignore();
    getline(cin, input);
    return input;
}
