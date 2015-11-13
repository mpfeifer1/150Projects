/*************************************************************************//**
 * @file
 *
 * @mainpage prog4 - Print Cost Analyzer
 *
 * @section course_section Course Information
 *
 * @author Michael Pfeifer
 *
 * @date 11/11/2015
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
 * @details This program takes in a file, and calculates the price of each
            string given using the font data files. It then sorts them from
            least to most expensive, and writes it to a new file.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Standard compilation
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe data.in ######FIND OUTPUT FILE########
   or
   g++ prog3.cpp
   ./a.out data.in ############HERE TOO##############
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------------
   Nov  9, 2015  Started main method
   Nov 10, 2015  Finished main, extracted font size, commented
   Nov 11, 2015  Completed readFontData, getTonerUsed, cleanFont, getTonerCost,
                 sorted, and Doxygen comments. Actually, essentially everything.
   @endverbatim
 *
 *****************************************************************************/

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
void sortByCost(char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]);
void readFontData(ifstream& fin, char fontName[1001][1001], int fontData[256][2], int index);
void readInputFile(ifstream& fin, char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int index[1001]);
int  getTonerUsed(char print[1001][1001], int fontSize[1001], int fontData[256][2], int index);
void printUsage(ofstream& fout, char print[1001][1001], char fontName[1001][1001], int fontSize[1001], int toner[1001], int index[1001]);
void cleanFont(char font[1001]);
int  getTonerCost(char c, int fontData[256][2]);

// Global Constants
#define MAX 1001

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function calculates the costs of strings to print
 *
 * @param[in]       data.in     - the file to read input from
 * @param[in][out]  #######     - the file to write output to
 *
 * @returns         0           - the program executed successfully
 * @returns         false       - the program threw an error
 *
 *****************************************************************************/
int main(int argc, char* argv[]) {
    // Variable Initilization
    char print      [MAX][MAX]  = {'\0'}; // String to print
    char fontName   [MAX][MAX]  = {'\0'}; // Name of font to use
    int  fontSize   [MAX]       = {0};    // Size of font
    int  toner      [MAX]       = {0};    // Total toner necessary
    int  index      [MAX]       = {0};    // Index of record
    int  fontData   [256][2]    = {0};    // Column 1 is ascii value as an int, column 2 is the cost in toner units
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
        cout << "The input file didn't open" << endl;
        return 1;
    }

    // Process data
    readInputFile(fin, print, fontName, fontSize, index);
    fin.close(); // Close first file

    // Read in all necessary fonts
    for(int i = 0; index[i] != 0; i++) {
        readFontData(fin, fontName, fontData, i);
        toner[i] = getTonerUsed(print, fontSize, fontData ,i);
    }

    // Sort and print records
    sortByCost(print, fontName, fontSize, toner, index);

    // Open output file
    fout.open(argv[2]);
    if(!fout) {
        cout << "The output file didn't open" << endl;
        return 1;
    }
    printUsage(fout, print, fontName, fontSize, toner, index);

    return 0;
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function pulls the font size out of a string
 *
 * @param[in][out]  line        - the string to extract from, is returned w/o size
 *
 * @returns         [int]       - the font size
 *
 *****************************************************************************/
int extractPointSize(char line[MAX]) {
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

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function sorts (ascending) all records by the amount of toner needed
 *
 * @param[in][out]  print       - the string to print
 * @param[in][out]  fontName    - the name of the font
 * @param[in][out]  fontSize    - the size of the font
 * @param[in][out]  toner       - the amount of toner necessary
 * @param[in][out]  index       - the index of the record
 *
 *****************************************************************************/
void sortByCost(char print[MAX][MAX], char fontName[MAX][MAX], int fontSize[MAX], int toner[MAX], int index[MAX]) {
    // Calculate total length
    int length = 0;
    while(index[length] != 0) {
        length++;
    }

    // Insertion sort all items in array
    for(int i = 1; i < length; i++) {
        for(int j = i; j > 0; j--) {
            if(toner[j] < toner[j - 1]) {
                // Swap items
                char tempPrint[MAX]     = "";
                strcpy(tempPrint, print[j]);
                char tempFontName[MAX]  = "";
                strcpy(tempFontName, fontName[j]);
                int  tempFontSize       = fontSize[j];
                int  tempToner          = toner[j];
                int  tempIndex          = index[j];

                strcpy(print[j], print[j-1]);
                strcpy(fontName[j], fontName[j-1]);
                fontSize[j] = fontSize[j-1];
                toner[j]    = toner[j-1];
                index[j]    = index[j-1];

                strcpy(print[j-1], tempPrint);
                strcpy(fontName[j-1], tempFontName);
                fontSize[j-1]   = tempFontSize;
                toner[j-1]      = tempToner;
                index[j-1]      = tempIndex;
            } else {
                break;
            }
        }
    }
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function takes the data from the font file and saves it to an array
 *
 * @param[in]       fin         - the input stream
 * @param[in]       fontName    - the name of the font
 * @param[in][out]  fontData    - the toner needed to print any letter in a font
 * @param[in]       index       - the index of the record
 *
 *****************************************************************************/
void readFontData(ifstream& fin, char fontName[MAX][MAX], int fontData[256][2], int index) {
    // Cleans out old font data
    for(int i = 0; i < 256; i++) {
        fontData[i][0] = 0;
        fontData[i][1] = 0;
    }

    // Get filename for font
    cleanFont(fontName[index]);
    char tempFontName[MAX] = "font_data\\"; // I haven't actually tested this because linux, but Manes says it's correct, soooooo
    strcat(tempFontName, fontName[index]);
    strcat(tempFontName, ".tnr");
    fin.open(tempFontName);
    if(!fin) {
        cout << "File not opened" << endl;
    }

    // Read in data to font file
    int i = 0;
    char input[MAX] = "";
    while(fin >> input && fin.peek() != EOF) {
        fontData[i][0] = (int)input[0]; // The [0] converts the string (which will always be one char) to a character
        fin >> input;
        fontData[i][1] = atoi(input);
        i++;
    }

    // Clean up
    fin.close();
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function reads the .in file and initializes all the necessary arrays
 *
 * @param[in]       fin         - the file to pull data from
 * @param[in][out]  print       - the string to print
 * @param[in][out]  fontName    - the name of the font
 * @param[in][out]  fontSize    - the size of the font
 * @param[in][out]  index       - the index of the record
 *
 *****************************************************************************/
void readInputFile(ifstream& fin, char print[MAX][MAX], char fontName[MAX][MAX], int fontSize[MAX], int index[MAX]) {
    // Define variables
    char inputChar[MAX] = {'\0'};
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
        fin.getline(inputChar, MAX, '\n');
        strcpy(print[i], inputChar);

        // Increment record counter
        i++;
    }

}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function calculates the amount of toner needed for the given string
 *
 * @param[in]       print       - the string to print
 * @param[in]       fontSize    - the size of the font
 * @param[in]       fontData    - the information for toner in a font
 * @param[in]       index       - the index of the record
 *
 * @returns         [int]       - the amount of toner necessary
 *
 *****************************************************************************/
int getTonerUsed(char print[MAX][MAX], int fontSize[MAX], int fontData[256][2], int index) {
    int tempSize = fontSize[index];
    double toner = 0;
    // Loops through every char in the string
    for(int i = 0; i < 1000 && print[i] != '\0'; i++) {
        // Add the font toner cost of the selected char * (font size / 12) to get actual font cost
        toner += getTonerCost(print[index][i], fontData); // * (tempSize / 12.0);
    }
    return (int)toner;
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function prints all the records to a file
 *
 * @param[in][out]  fout        - the file to output to
 * @param[in]       print       - the string to print
 * @param[in]       fontName    - the name of the font
 * @param[in]       fontSize    - the size of the font
 * @param[in]       toner       - the amount of toner necessary
 * @param[in]       index       - the index of the record
 *
 *****************************************************************************/
void printUsage(ofstream& fout, char print[MAX][MAX], char fontName[MAX][MAX], int fontSize[MAX], int toner[MAX], int index[MAX]) {
    // Loops through every index printing
    for(int i = 0; index[i] > 0; i++) {
        fout << "Record: " << index[i] << "   Font: " << fontName[i] << "   Size: " << fontSize[i] << endl;
        fout << "Toner required: " << toner[i] << endl;
        fout << "String: " << print[i] << endl;
        fout << endl;
    }
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function makes all characers lowercase and turns spaces into unerscores
 *
 * @param[in][out]  font        - the font to clean
 *
 *****************************************************************************/
void cleanFont(char font[MAX]) {
    // Loop through all characters
    for(int i = 0; i < MAX - 1 && font[i] != '\0'; i++) {
        // Make lowercase
        font[i] = tolower(font[i]);
        // Change spaces to underscores
        if(font[i] == ' ') {
            font[i] = '_';
        }
    }
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function finds the cost of a character in a font
 *
 * @param[in]       c           - the character to look up
 * @param[in]       fontData    - the raw data from the font
 *
 * @returns         [int]       - the cost in toner
 *
 *****************************************************************************/
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
