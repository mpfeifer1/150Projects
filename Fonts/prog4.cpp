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
   c:\> prog3.exe data.in results.txt
   or
   g++ prog3.cpp
   ./a.out data.in results.txt
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

// Global Constants
#define MAX 1001

// Struct definitions
struct record {
    char   print[MAX];    // String to print
    char   fontName[MAX]; // Name of font
    int    fontSize;      // Size of font
    double toner;         // Amount of toner necessary
    int    index;         // Index user entered in
};

// Function Prototypes
int    extractPointSize(char line[MAX]);
void   sortByCost(record records[MAX]);
void   readFontData(ifstream& fin, record records[MAX], int fontData[256], int index);
void   readInputFile(ifstream& fin, record records[MAX]);
double getTonerUsed(record records[MAX], int fontData[256], int index);
void   printUsage(ofstream& fout, record records[MAX]);
void   cleanFont(char font[MAX]);

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function calculates the costs of strings to print
 *
 * @param[in]       data.in     - the file to read input from
 * @param[in][out]  results.txt - the file to write output to
 *
 * @returns         0           - the program executed successfully
 * @returns         false       - the program threw an error
 *
 *****************************************************************************/
int main(int argc, char* argv[]) {
    // Variable Initilization
    static record records[MAX] = {0}; // Static so the computer doesn't overflow right away
    int fontData[256] = {0}; // Costs of characters in toner, sorted by ASCII
    int n = 3, i = 0, j = 0; // i and j are counters, n is the number of necessary arguments

    // Checks number of arguments
    if(argc < n) {
        cout << "Not enough arguments" << endl;
        return 1;
    }
    if(argc > n) {
        cout << "Too many arguments" << endl;
        return 1;
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
    readInputFile(fin, records);
    fin.close(); // Close first file

    // Read in all necessary fonts and calculate toner
    for(int i = 0; records[i].index != 0; i++) {
        readFontData(fin, records, fontData, i);
        records[i].toner = getTonerUsed(records, fontData, i);
    }

    // Sort and print records
    sortByCost(records);

    // Open output file
    fout.open(argv[2]);
    if(!fout) {
        cout << "The output file didn't open" << endl;
        return 1;
    }
    printUsage(fout, records);

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
void sortByCost(record records[MAX]) {
    // Calculate total length
    int length = 0;
    while(records[length].index != 0) {
        length++;
    }

    // Insertion sort all items in array
    // TODO change to recursive quicksort
    for(int i = 1; i < length; i++) {
        for(int j = i; j > 0; j--) {
            if(records[j].toner < records[j-1].toner) {
                // Swap items
                char   tempPrint[MAX] = "";
                strcpy(tempPrint, records[j].print);
                char   tempFontName[MAX] = "";
                strcpy(tempFontName, records[j].fontName);
                int    tempFontSize = records[j].fontSize;
                double tempToner = records[j].toner;
                int    tempIndex = records[j].index;

                strcpy(records[j].print, records[j-1].print);
                strcpy(records[j].fontName, records[j-1].fontName);
                records[j].fontSize = records[j-1].fontSize;
                records[j].toner    = records[j-1].toner;
                records[j].index    = records[j-1].index;

                strcpy(records[j-1].print, tempPrint);
                strcpy(records[j-1].fontName, tempFontName);
                records[j-1].fontSize   = tempFontSize;
                records[j-1].toner      = tempToner;
                records[j-1].index      = tempIndex;
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
void readFontData(ifstream& fin, record records[MAX], int fontData[256], int index) {
    // Cleans out old font data
    for(int i = 0; i < 256; i++) {
        fontData[i] = 0;
    }

    // Get filename for font
    cleanFont(records[index].fontName);
    // Windows - I haven't actually tested this because Linux, but Prof. Manes says it's correct, soooooo
    // char tempFontName[MAX] = "font_data\\";
    // Linux
    char tempFontName[MAX] = "font_data/";
    strcat(tempFontName, records[index].fontName);
    strcat(tempFontName, ".tnr");
    fin.open(tempFontName);
    if(!fin) {
        cout << "File not opened" << endl;
    }

    // Read in data to font file
    int i = 0;
    char inputChar = ' ';
    int inputInt = 0;
    while(fin >> inputChar && fin.peek() != EOF) {
        // Gets data
        char character = inputChar;
        fin >> inputInt;
        int cost = inputInt;

        // Places data in array (based on character's ASCII value)
        fontData[(int)character] = cost;
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
void readInputFile(ifstream& fin, record records[MAX]) {
    // Define variables
    char inputChar[MAX] = {'\0'};
    int i = 0, j = 0;

    while(fin && fin.peek() != EOF) {
        // Get first line
        fin.getline(inputChar, 1001, '\n');

        // Enter record number
        records[i].index = i + 1;

        // Get font size
        records[i].fontSize = extractPointSize(inputChar);

        // Get font name
        strcpy(records[i].fontName, inputChar);

        // Get second line
        fin.getline(inputChar, MAX, '\n');
        strcpy(records[i].print, inputChar);

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
 * @returns         [double]    - the amount of toner necessary
 *
 *****************************************************************************/
double getTonerUsed(record records[MAX], int fontData[256], int index) {
    int tempSize = records[index].fontSize;
    double toner = 0;
    // Loops through every char in the string
    for(int i = 0; i < 1000 && records[i].print != '\0'; i++) {
        // Add the font toner cost of the selected char * (font size / 12) to get actual font cost
        toner += fontData[records[index].print[i]] * (tempSize / 12.0);
    }
    return toner;
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
void printUsage(ofstream& fout, record records[MAX]) {
    // Loops through every index printing
    for(int i = 0; records[i].index > 0; i++) {
        fout << "Record: " << records[i].index << "   Font: " << records[i].fontName << "   Size: " << records[i].fontSize << endl;
        fout << "Toner required: " << records[i].toner << endl;
        fout << "String: " << records[i].print << endl;
        fout << endl;
    }
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * This function makes all characers lowercase and turns spaces into underscores
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
