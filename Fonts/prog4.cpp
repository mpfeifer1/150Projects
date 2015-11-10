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
void readInputFile(ifstream& fin, char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int index[1001]);
int  getTonerUsed();
void printUsage(char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]);

int main(int argc, char* argv[]) {
    // Variable Initilization
    char print      [1001][1001]    = {'\0'}; // String to print
    char fontName   [1001][1001]    = {'\0'}; // Name of font to use
    int  fontSize   [1001]          = {0};    // Size of font
    int  toner      [1001]          = {0};    // Total toner necessary
    int  index      [1001]          = {0};    // Index of record

    int  fontData   [256][2]        = {0};    // Column 1 is ascii value as an int, column 2 is the cost in toner units

    int n = 3, i = 0, j = 0;

    // Checks number of arguments
    if(argc < n) {
        cout << "Not enough arguments" << endl;
        return -1;
    }
    if(argc > n) {
        cout << "Too many arguments" << endl;
        return -1;
    }


    // Define file streams
    ifstream fin;
    ofstream fout;

    // Open file
    fin.open(argv[1]);
    if(!fin) {
        cout << "The file didn't open" << endl;
        return -1;
    }

    // Process data
    readInputFile(fin, print, fontName, fontSize, index);
    fin.close(); // Close first file
    printUsage(print, fontName, fontSize, toner, index);

    return 0;
}

int  extractPointSize();
void sortByCost();
void readFontData();

void readInputFile(ifstream& fin, char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int index[1001]) {
    // Define variables
    char inputChar[1001] = {'\0'};
    int i = 0, j = 0;

    while(fin && fin.peek() != EOF) {
        // Get first line
        fin.getline(inputChar, 1001, '\n');

        // Enter record number
        index[i] = i + 1;

        // Get font size
        int tempFont = 0;
        j = strlen(inputChar) - 1;
        int fontLen = 0;
        while(isdigit(inputChar[j - 1])) {
            j--;
            fontLen++;
        }
        const char *fontArray = &inputChar[strlen(inputChar) - (fontLen + 1)];
        tempFont = atoi(fontArray);
        fontSize[i] = tempFont;

        // Get font name
        inputChar[strlen(inputChar) - strlen(fontArray) - 1] = '\0';
        strcpy(fontName[i], inputChar);

        // Get second line
        fin.getline(inputChar, 1001, '\n');
        strcpy(print[i], inputChar);

        // Increment record counter
        i++;
    }

}

int  getTonerUsed();

void printUsage(char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]) {
    // Loops through every index printing
    for(int i = 0; index[i] > 0; i++) {
        cout << "Record: " << index[i] << "   Font: " << fontName[i] << "   Size: " << fontSize[i] << endl;
        cout << "Toner required: " << toner[i] << endl;
        cout << "String: " << print[i] << endl;
        cout << endl;
    }
}
