// Preprocessor Commands
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <string>

using namespace std;

// Function Prototypes
int  extractPointSize();
void sortByCost();
void readFontData();
int  getTonerUsed();
void printUsage();
void strrev(char str[]);

int main(int argc, char* argv[]) {
    // Variable Initilization
    char records    [1001][1001]    = {'\0'};
    char fontName   [1001][1001]    = {'\0'};
    int  fontSize   [1001]          = {0};
    int  toner      [1001]          = {0};
    int  index      [1001]          = {0};

    char inputChar  [1001]          = {'\0'};
    int  inputInt                   = 0;

    char fontChar   [1001]          = {'\0'};
    char fontToner  [1001]          = {'\0'};

    int n = 3, i = 0, j = 0;

    if(argc < n) {
        cout << "Not enough arguments" << endl;
        return -1;
    }
    if(argc > n) {
        cout << "Too many arguments" << endl;
        return -1;
    }


    ifstream fin;
    ofstream fout;

    fin.open(argv[1]);

    if(!fin) {
        cout << "The file didn't open" << endl;
        return -1;
    }

    i = 0;
    while(fin && fin.peek() != EOF) {
        // Get first line
        fin.getline(inputChar, 1001, '\n');

        // Remove spaces
        for(j = 0; j < strlen(inputChar); j++) {
            if(inputChar[j] == ' ') {
                inputChar[j] = '_';
            }
        }

        // Get font size
        int tempFont = 0;
        i = strlen(inputChar) - 1;
        int fontLen = 0;
        while(isdigit(inputChar[i - 1])) {
            i--;
            fontLen++;
        }
        const char *fontArray = &inputChar[strlen(inputChar) - (fontLen + 1)];
        tempFont = atoi(fontArray);
        cout << "Font Size: " << tempFont << endl;

        // Get font name
        inputChar[strlen(inputChar) - strlen(fontArray) - 1] = '\0';
        cout << "Font name: " << inputChar << endl;

        // Get second line
        fin.getline(inputChar, 1001, '\n');
        strcpy(records[i], inputChar);

        cout << endl;

        i++;
    }

    return 0;
}
