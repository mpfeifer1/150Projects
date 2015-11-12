// Preprocessor Commands
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <string>

using namespace std;

// Function Prototypes
int  extractPointSize(char line[1001]);
void sortByCost();
void readFontData(ifstream& fin, char fontName[1001][1001], int fontData[256][2], int index);
void readInputFile(ifstream& fin, char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int index[1001]);
int  getTonerUsed(char print[1001][1001], int fontSize[1001], int fontData[256][2], int index);
void printUsage(char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]);
void cleanFont(char font[1001]);
int  getTonerCost(char c, int fontData[256][2]);

int main(int argc, char* argv[]) {
    // Variable Initilization
    char print      [1001][1001]    = {'\0'}; // String to print
    char fontName   [1001][1001]    = {'\0'}; // Name of font to use
    int  fontSize   [1001]          = {0};    // Size of font
    int  toner      [1001]          = {0};    // Total toner necessary
    int  index      [1001]          = {0};    // Index of record
    int  fontData   [256][2]        = {0};    // Column 1 is ascii value as an int, column 2 is the cost in toner units
    int n = 3, i = 0, j = 0;                  // i and j are counters, n is the number of necessary arguments

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

    // Read in all necessary fonts
    for(int i = 0; index[i] != 0; i++) {
        readFontData(fin, fontName, fontData, i);
        toner[i] = getTonerUsed(print, fontSize, fontData ,i);
    }

    printUsage(print, fontName, fontSize, toner, index);

    return 0;
}

int extractPointSize(char line[1001]) {
    // Calculates length of the font
    int j = strlen(line) - 1;
    int fontLen = 0;
    while(isdigit(line[j - 1])) {
        j--;
        fontLen++;
    }

    // Create new array for the font
    const char *fontArray = &line[strlen(line) - (fontLen + 1)];

    // Remove font size from the end of the font name
    line[strlen(line) - strlen(fontArray) - 1] = '\0';

    // Returns font size as an integer
    return atoi(fontArray);
}

void sortByCost();

void readFontData(ifstream& fin, char fontName[1001][1001], int fontData[256][2], int index) {
    // Cleans out old font data
    for(int i = 0; i < 256; i++) {
        fontData[i][0] = 0;
        fontData[i][1] = 0;
    }

    // Get filename for font
    cleanFont(fontName[index]);
    char tempFontName[1001] = "font_data/";
    strcat(tempFontName, fontName[index]);
    strcat(tempFontName, ".tnr");
    fin.open(tempFontName);
    if(!fin) {
        cout << "File not opened" << endl;
    }

    // Read in data to font file
    int i = 0;
    char input[1001] = "";
    while(fin >> input && fin.peek() != EOF) {
        fontData[i][0] = (int)input[0]; // The [0] converts the string (which will always be one char) to a character
        fin >> input;
        fontData[i][1] = atoi(input);
        i++;
    }

    // Clean up
    fin.close();
}

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
        fontSize[i] = extractPointSize(inputChar);

        // Get font name
        strcpy(fontName[i], inputChar);

        // Get second line
        fin.getline(inputChar, 1001, '\n');
        strcpy(print[i], inputChar);

        // Increment record counter
        i++;
    }

}

int getTonerUsed(char print[1001][1001], int fontSize[1001], int fontData[256][2], int index) {
    int tempSize = fontSize[index];
    double toner = 0;
    // Loops through every char in the string
    for(int i = 0; i < 1000 && print[i] != '\0'; i++) {
        // Add the font toner cost of the selected char * (font size / 12) to get actual font cost
        toner += getTonerCost(print[index][i], fontData) * (tempSize / 12.0);
    }
    return (int)toner;
}

void printUsage(char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]) {
    // Loops through every index printing
    for(int i = 0; index[i] > 0; i++) {
        cout << "Record: " << index[i] << "   Font: " << fontName[i] << "   Size: " << fontSize[i] << endl;
        cout << "Toner required: " << toner[i] << endl;
        cout << "String: " << print[i] << endl;
        cout << endl;
    }
}

void cleanFont(char font[1001]) {
    // Loop through all characters
    for(int i = 0; i < 1000 && font[i] != '\0'; i++) {
        // Make lowercase
        font[i] = tolower(font[i]);
        // Change spaces to underscores
        if(font[i] == ' ') {
            font[i] = '_';
        }
    }
}

int getTonerCost(char c, int fontData[256][2]) {
    // Loop through all characters
    for(int i = 0; i < 256; i++) {
        // If a match is found, return the associated cost
        if((int)c == fontData[i][0]) {
            return fontData[i][1];
        }
    }
    // Otherwise, return default of 0
    return 0;
}
