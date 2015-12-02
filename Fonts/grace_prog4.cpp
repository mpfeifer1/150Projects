/*************************************************************************//**
* @file
*
* @mainpage Program 4 - Computing Toner Usage
*
* @section course_section Course Information
*
* @author Grace Andersen
*
* @date December 4, 2015
*
* @par Professor:
*         Professor Larry Pyeatt
*
* @par Course:
*         CSC 150 - M001 -  10 am
*
* @par Location:
*         McLaury - 306
*
* @section program_section Program Information
*
* @details This program uses files filed with data on how much toner
* each character that can be typed uses.  It uses this data to
* determine how much toner a string uses.  It then sorts the strings
* by the ammount of toner used.
*
* There are several functions in this program, each taking care of
* very specific things.  I used a bubble sort to sort both the contents
* of the files, and the strings by how much toner was used.
*
* I also must use searches to find all of the characters in the string
* in the data array.  This will be moderately difficult, but will
* be made much easier by the bubble sort.
*
* After I collect and compute all of the data, I will send it to a
* function that will output it all to the user.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      Nothing special needs to be done to compile this program
*
* @par Usage:
@verbatim
c:\> prog4.exe
d:\> c:\bin\prog4.exe
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug Will figure out when I run it
*
* @todo Finish the code
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Nov 11, 2015  Wrote pseudocode for all functions
Nov 14, 2015  Started writing functions
Nov 20, 2015  Wrote the extractPointSize functions
Nov 28, 2015  Worked on sorting algorithms and search algorithms
Nov 29, 2015  Finished writing and began debugging all functions
Dec  1, 2015  Got program to run and compile without errors

@endverbatim
*
*****************************************************************************/

//preprocessor commands
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>

#define _CRT_SECURE_NO_DEPRECATE

using namespace std;

//Get the point size from an input string
int extractPointSize(char input[1000][1000], int pointSize[1000]);

//Sort the "records" by cost
void sortByCost(int tonerUsed[1000], char sampleString[1000][1000], int size,
    int number[1000]);

//sorts an array of characters arr, with size n from biggest to smallest
int searchChar(char fontData[1000][2], int size, char target);

//Use the font name to read the data file
void readFontData(int line, char fontName[1000][1000], char fontData[1000][2]);

//Use the font data and string to be printed
int getTonerUsed(int fontSize, char sampleString[1000][1000], char fontData[1000][2],
    int numberStrings);

//Print a message about how to use the program
void printUsage(ofstream& fout, int number[1000], char fontName[1000][1000],
    int pointSize[1000], int tonerUsed[1000], char sampleString[1000][1000],
    int numStrings);

//reads the input file
int readInput(ifstream& fin, char input[1000][1000], char fontName[1000][1000],
    char sampleString[1000][1000], int pointSize[1000]);

char *strrev(char *str);

/**************************************************************************//**
* @author Grace Andersen
*
* @par Description:
* The main function calls all other functions.  It doesnt do any computing
* itself.  All it really does is read in input from the command line, and
* then call functions to do everything for it.
*
* @param[in]      argv[] - the text of an arguement input by the user
* @param[in]      argc   - keeps track of the number of arguements input
*
* @returns 0 program ran successful.
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    ifstream fin;//used to read in the input file
    ofstream fout;//used to output data to a file
    static int pointSize[1000] = { 0 };//Stores the point size of all of the fonts
    static char inputFile[1000][1000] = { 0 }; //Stores records from data.in
    static char fontName[1000][1000] = { 0 };//stores the names of all the fonts
    static char sampleString[1000][1000] = { 0 };//exact copy of the original input file
    static char fontData[1000][2] = { 0 };//Holds the data for the fonts
    int i, j;//indexing
    int numberStrings = 0;//holds the number of strings being analyzed
    int fontSize;//holds the fontsize of a specific line temporarally
    static int tonerUsed[1000] = { 0 };//Holds the ammount of toner each string uses
    static int number[1000] = { 0 };//numbers used to keep track of sorted data



    //Makes sure there are not to many command line arguements
    if (argc > 4)
    {
        cout << "Too many command line arguements";
        return 1;
    }
    //Makes sure there are enough command line arguments
    if (argc < 3) {

        cout << "Too few arguments" << endl;
        return 1;
    }

    //opens the input file and makes sure it is open
    fin.open(argv[1]);
    if (!fin)
    {
        cout << "Not a valid input file" << endl; 
        return 1;
    }

    //read the input into inputFile, and copy into sampleString.  Then 
    //in the function, remove the point size from inputFile, and put it
    //into pointSize.  Also separate out fontName.  
    numberStrings = readInput(fin, inputFile, fontName, sampleString, pointSize);
    
    //stuff that needs to be done for each string being analyzed
    for (i = 0; i < numberStrings; i++)
    {
        //cout << "THIS IS THE IMPORTANT PART" << endl;
        fontSize = pointSize[i];
        //cout << fontSize << endl;
        readFontData(i, fontName, fontData);
        //cout << "NOW THIS IS IMPORTANT" << endl;
        cout << i << endl;
        //getTonerUsed(fontSize, sampleString, fontData, numberStrings);
        tonerUsed[i] = getTonerUsed(fontSize, sampleString, fontData, numberStrings);
    }

    sortByCost(tonerUsed, sampleString, numberStrings, number);
    
    fout.open(argv[2]);
    if (!fout)
    {
        cout << "Not a valid output file" << endl;
        return 1;
    }
    printUsage(fout, number, fontName, pointSize, tonerUsed, sampleString, numberStrings);

    fout.close();
    fin.close();

    return 0;
}


/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Gets the point size of the font from an array of characters
*
* @param[in]      input[][] - the original string
* @param[in]      pointSize[][] - The array where point sizes will be stored
*
* @returns 1 if function ran succesfully
*
*****************************************************************************/
int extractPointSize(char input[1000][1000], int pointSize[1000])
{
    int i, j;
    int count = 0;

    cout << "starting point size" << endl;

    for (i = 0; i < 1000; i += 2)
    {
        for (j = 0; j < 1000; j++)
        {
            strrev(input[j]);
            if (input[j] != " ")
            {
                pointSize[i] = input[i][j];
                count++;
            }
            input[i][count] = '\0';
        }
    }

    return 1;
}

/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Sorts the input strings by the cost in toner required to print them.
*
* @param[in]
*
* @returns  nothing
*
*****************************************************************************/
void sortByCost(int tonerUsed[1000], char sampleString[1000][1000], int size,
    int number[1000])
{
    //sort the records by cost
    //sort the toner used, and move the input file at the same time. 
    int i, j;

    cout << "starting sort by cost" << endl;
    
    for (j = 0; j < size; j++)
    {
        number[j] = j;
    }
    for (i = 0; i < size; i++)
    {
        
        if (tonerUsed[i] < tonerUsed[i + 1])
        {
            swap(tonerUsed[i], tonerUsed[i + 1]);
            swap(sampleString[i], sampleString[i + 2]);
            swap(sampleString[i + 1], sampleString[i + 3]);
            swap(number[j], number[j + 1]);
        }
        
    }
}

/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Reads in the font data from a file into an array, then orders it by ascii
* value.
*
* @param line  -  which row of the array is being used now.
* @param fontName[][]  -  array that stores the font names
*
* @returns none
*****************************************************************************/
void readFontData(int line, char fontName[1000][1000], char fontData[1000][2])
{
    //use the font name to read the data file
    ifstream data_file;
    int i, j, k;
    string copy;
    
    cout << "starting read font data" << endl;

    //Make the font name
    strcat(fontName[line], ".tnr");
    data_file.open(fontName[line]);
    //check if it opens
    if (!data_file)
    {
        cout << "Incorrect data file name";
    }
    //copy file into fontData 
    for (i = 0; i < 1000; i++)
    {
        data_file >> fontData[i];
    }

    //sort font data
    for (j = 0; j < 256; j++)
    {//on separate lines, fix it.
        if (fontData[j][0] > fontData[j + 1][0])
        {
            swap(fontData[j], fontData[j + 1]);
        }
    }
}


/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Calculates the ammount of toner used in the string by using a search function
* and summing the values of the toner.
*
* @param[in]
*
* @returns
*
*****************************************************************************/
int getTonerUsed(int fontSize, char sampleString[1000][1000], char fontData[1000][2],
    int numberStrings)
{
    //Use the font data and string to be printed to calculate toner used
    int tonerUsed = 0;
    int i, j, size;
    char target;

    cout << "starting getTonerUsed" << endl;

    size = numberStrings;
    for (i = 1; i < numberStrings; i += 2)
    {
        for (j = 0; j < numberStrings; j++)
        {
            target = sampleString[i][j];
            cout << "Running" << endl;
            tonerUsed += searchChar(fontData, size, target);
        }
    }

    tonerUsed = fontSize / 12 * tonerUsed;
    return tonerUsed;
}


int searchChar(char fontData[1000][2], int size, char target)
{
    cout << "got here" << endl;
    int left = 0;
    int right = size - 1;
    int mid;
    int i, j;
    char characters[500];
    int integers[500];

    cout << "starting search char" << endl;

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 500; j++)
        {
            characters[j] = fontData[i][0];
        }
    }

    for (i = 1; i < 1000; i++)
    {
        for (j = 0; j < 500; j++)
        {
            integers[j] = fontData[i][1];
        }
    }

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (characters[mid] == target)
        {
            return integers[mid];
        }
        if (characters[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            left = mid - 1;
        }
    }

    return integers[mid];
}


/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Prints all of the data collected and computed over the course of this
* program.
*
* @param[in]
*
* @returns
*
*****************************************************************************/
void printUsage(ofstream& fout, int number[1000], char fontName[1000][1000], 
    int pointSize[1000], int tonerUsed[1000], char sampleString[1000][1000],
    int numStrings)
{
    //print output
    int i; 
    int j = 0;

    cout << "starting print usage" << endl;

    for (i = 0; i < numStrings; i++)
    {
        
        fout << "Record: " << number[i] << "\tFont: " << fontName[i]
            << "\tSize: " << pointSize[i] << "\nToner required: "
            << tonerUsed[i] << "\nString: " << sampleString[j];
        j += 2;
    }
}


/**************************************************************************/
/**
* @author Grace Andersen
*
* @par Description:
* Reads the input file specified by the user and parses the data.
*
* @param[in]      fin - file specified by the user
* @param[in]      input[][] - The array where the contents of the file stored
* @param[in]      fontName[][] - Stores the name of the font
* @param[in]      sampleString[][] - Temporary storage for input
* @param[in]      pointSize[][] - Stores the point size of the font
*
* @returns none
*
*****************************************************************************/
int readInput(ifstream& fin, char input[1000][1000], char fontName[1000][1000],
    char sampleString[1000][1000], int pointSize[1000])
{
    int i = 0;
    int j = 0;
    int numberStrings;

    cout << "starting read input" << endl;

    while (fin.peek() != EOF)
    {
        fin.getline(input[i], 1000);
        i++;
    }
    numberStrings = i / 2;
    for (i = 0; i < 1000; i++)//This section may need to go before the loops that get the font names.
    {
        for(j = 0; j < 1000; j++)
        {
            sampleString[i][j] = input[i][j];
        }
    }
    extractPointSize(input, pointSize);//this should remove the point size from the input string
    for (i = 0; i < 1000; i += 2)
    {
        strrev(input[i]);
    }
    for (i = 0; i < 1000; i += 2)
    {
        for (j = 0; j < 1000; j++)
        {
            if (input[i][j] = ' ')
            {
                input[i][j] = '_';
            }
            tolower(input[i][j]);
            fontName[i][j] = input[i][j];
        }
    }
    return numberStrings;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
