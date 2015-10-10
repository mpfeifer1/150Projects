/*************************************************************************//**
 * @file 
 *
 * @mainpage prog1 - Unit Converter
 * 
 * @section course_section Course Information
 *
 * @author Michael Pfeifer
 * 
 * @date 09/18/2015
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
 * @details This program takes in a number of hours, and converts it to years, months, days, and hours. Then, it takes in ounces, and converts it to pounds and kilograms. Finally, it takes in a number of degrees in celcius, and converts it to fahrenheit.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      Standard compilation
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog1.exe 
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @todo Make program only accept positive integers, rather than assuming valid input
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Sep  4, 2015  Wrote a majority of the program
   Sep  5, 2015  Fixed formatting, and added Doxygen documentation
   Sep  9, 2015  Refactored code from while loops to using fmod in hours conversion, Removed hours output, put it with days
   @endverbatim
 *
 *****************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**************************************************************************//** 
 * @author Michael Pfeifer
 * 
 * @par Description: 
 * This function converts hours, ounces, and degrees. It assumes all inputs are positive integers.
 * 
 * @param[in]   counter         - Counts the total number of years, months, etc...
 * @param[in]   hours           - Number of hours user gave, assumed positive integer
 * @param[in]   hours_left      - Number of hours left after subtracting for years, months, etc...
 * @param[in]   ounces          - Number of ounces user gave, assumed positive integer
 * @param[in]   degrees_celcius - Number of degrees user gave, assumed positive integer
 * @param[in]   HOURS_IN_DAY    - Number of hours in one day
 * @param[in]   HOURS_IN_MONTH  - Number of hours in one month (Averaged)
 * @param[in]   HOURS_IN_YEAR   - Number of hours in one year
 * @param[in]   OUNCES_IN_POUND - Number of ounces in one pound
 * @param[in]   POUNDS_IN_KG    - Number of pounds in one kilogram
 * 
 * @returns     0               - program ran successful.
 * 
 *****************************************************************************/
int main() {
    //Sets up output to look nice
    cout << setprecision(4);
    cout << fixed;
    cout << showpoint;

    // Initialize variables to 0
    int counter         = 0;
    int hours           = 0;
    double hours_left   = 0;
    int ounces          = 0;
    int degrees_celcius = 0;

    // Define constants
    const double HOURS_IN_DAY       = 24;
    const double HOURS_IN_MONTH     = 30.4368 * HOURS_IN_DAY;
    const double HOURS_IN_YEAR      = 12 * HOURS_IN_MONTH;
    const double OUNCES_IN_POUND    = .0625;
    const double POUNDS_IN_KG       = .4536;

    // Prompts user for hours, sets it to hours left
    cout << "Enter Hours: ";
    cin >> hours;
    hours_left = hours;

    // Re-states number of hours
    cout << hours << " Hour(s) is:" << endl;

    // The fmod finds the hours leftover from years, and subtracts it from hours_left so it's divisible by year.
    // Then, it's divided by HOURS_IN_YEAR to calculate total. Finally, it's cast to int to look nice.
    cout << (int)((hours_left - fmod(hours_left, HOURS_IN_YEAR))
        / (HOURS_IN_YEAR)) << " Year(s)" << endl;
    // Hours left is set to fmod, which is the leftover from years
    hours_left = fmod(hours_left, (HOURS_IN_YEAR));

    // Same as above, but with month instead of year
    cout << (int)((hours_left - fmod(hours_left, HOURS_IN_MONTH))
        / (HOURS_IN_MONTH)) << " Month(s)" << endl;
    hours_left = fmod(hours_left, (HOURS_IN_MONTH));

    // Divides the remaining hours
    cout << hours_left / HOURS_IN_DAY << " Day(s)" << endl;

    cout << endl;

    // Prompts user for ounces
    cout << "Enter Ounces: ";
    cin >> ounces;

    // Re-states number of ounces, multiplies it by proper conversion factor, and prints it
    cout << ounces << " Ounce(s) is:" << endl;
    cout << (ounces * OUNCES_IN_POUND) << " Pound(s) or" << endl;
    cout << (ounces * OUNCES_IN_POUND * POUNDS_IN_KG) << " KG(s)" << endl;

    cout << endl;

    // Prompts user for degrees
    cout << "Enter Degrees Celcius: ";
    cin >> degrees_celcius;

    // Re-states number of degrees, runs it through the conversion formula, and prints it
    cout << degrees_celcius << " Degree(s) Celcius is:" << endl;
    cout << (degrees_celcius * (9.0 / 5) + 32) << " Degree(s) Fahrenheit" << endl;

    return 0;
}
