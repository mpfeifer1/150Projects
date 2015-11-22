/*************************************************************************//**
 * @file
 *
 * @mainpage prog2 - Approximation Calculator
 *
 * @section course_section Course Information
 *
 * @author Michael Pfeifer
 *
 * @date Oct. 9 2015
 *
 * @par Professor:
 *         Val Manes
 *
 * @par Course:
 *         Computer Science- CSC150 - 3:00 PM
 *
 * @par Location:
 *         Clasroom Building - 110
 *
 * @section program_section Program Information
 *
 * @details This program offers a menu to the user. The user can calculate the square root of a
   number using both the bisectional and newton method. The user can also calculate PI using the
   leibnitz method. Finally, the user can calculate the sine of a number using the Taylor Series
   approximation. The user also has the option of quitting.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      Standard compilation
 *
 * @par Usage:
   @verbatim
   c:\> prog2.exe
   or
   g++ prog2.cpp
   ./a.out
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------------
   Sep 18, 2015  Made menu, format for algorithms, declared variables
   Sep 19, 2015  Filled in all algorithms, added doxygen documentation
   Sep 28, 2015  Changed bisectional from while() to do while()
   @endverbatim
 *
 *****************************************************************************/
// Fun preprocessor stuff!
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
const double PI = M_PI;
// Function prototypes
double bisectional(double radicand);
double factorial(int fact_int);
double leibnitz(int iter);
double newtons(double radicand);
double taylor(double angle, int iter);
/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * Computes the square roots, sines, and PI
 *
 * @returns        0      - the program ran correctly
 *
 *****************************************************************************/
int main(void)
{
    // Declare variables
    bool quit = false;
    // Set up formatting
    setprecision(6);
    cout << fixed;
    //Continue program until user quits
    while(!quit) {
        // Declare variables
        char   choice;
        double angle;
        double    number;
        int    iter;
        // Set up menu
        cout << "Approximation Calculator" << endl;
        cout << "1. Compute a square root" << endl;
        cout << "2. Compute sine" << endl;
        cout << "3. Compute pi" << endl;
        cout << "4. Quit" << endl;
        // Get user input
        cout << "Enter an option: ";
        cin >> choice;
        // Make space between outputs
        cout << endl;
        // Decide what to do with input
        switch(choice) {
            // Square Root
            case '1':
                // Repeat user's choice
                cout << "Selected square root" << endl;
                // Get Input
                do {
                    cout << "Input a number: ";
                    cin >> number;
                } while(number <= 0);
                // Calculate the square root
                bisectional(number);
                newtons(number);
                cout << "System yields " << sqrt(number) << endl;
                break;
            // Sine
            case '2':
                // Repeat user's choice
                cout << "Selected sine" << endl;
                // Get input
                angle = -1; // Invalid by default
                iter = 0;
                do {
                    cout << "Input an angle in radians (0 -> 6.28): ";
                    cin >> angle;
                } while(angle <= 0 || angle > 6.28); // While angle isn't between 0 and 2pi
                do {
                    cout << "Input iterations: ";
                    cin >> iter;
                } while(iter <= 0);
                // Calculate sine
                taylor(angle, iter);
                break;
            // Pi
            case '3':
                // Repeat user's choice
                cout << "Selected pi" << endl;
                // Get input
                iter = 0;
                do {
                    cout << "Input iterations: ";
                    cin >> iter;
                } while(iter <= 0);
                // Calculate pi
                leibnitz(iter);
                break;
            // Quit
            case '4':
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            // Invalid
            default:
                cout << "Not valid input" << endl;
                break;
        }
        // This prevents instances of the program from looking merged and messy
        cout << endl;
    }
    return 0;
}
/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * Computes the square root of a number using the bisectional method
 *
 * @param[in]      radicand - value to find the square root of
 *
 * @returns        mid      - square root of the radicand
 *
 *****************************************************************************/
double bisectional(double radicand) {
    // Initialize variables
    double low = 0;
    double mid = 0;
    double high = radicand;
    double error = 1;
    int iter = 0;                     // Counter for number of iterations
    // Compute error
    do {      // Checks for error
        mid = (high + low) / 2.0;     // Sets mid to the Average of high and low
        error = radicand - mid * mid; // Calculates new error
        if(error > 0) {               // Sets low to mid
            low = mid;
        }
        if(error < 0) {               // Sets high to mid
            high = mid;
        }
        iter++;                       // Increments the counter
    } while(abs(error) > .00001);
    // Display results
    cout << "Bisection yields " << mid << " with " << iter << " iterations" << endl;;
    return mid;
}

/**************************************************************************//**
 * @author Val Manes
 *
 * @par Description:
 * Computes the factorial of a positive integer
 *
 * @param[in]      fact_int - value to find factorial of
 *
 * @returns fact - factorial of the input value
 *
 *****************************************************************************/
double factorial(int fact_int) {
    double fact = 1.0;
    int i;
    if( fact_int == 0 || fact_int == 1 ) {
        return 1.0;
    }
    for( i = 2; i <= fact_int ; i++ ) {
        fact *= i;
    }
    return fact;
}

/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * Computes the value of PI
 *
 * @param[in]      iter - the number of iterations to run
 *
 * @returns        pi   - the estimated value of pi
 *
 *****************************************************************************/
double leibnitz(int iter) {
    // Initialize Variables
    int sign = 1;
    double series = 0;
    double pi;
    // Once for each iteration,
    for(int i = 1; i <= iter; i++) {
        series += sign * (1.0 / ((2.0 * i) - 1)); // Series +- 1/(2n+1)
        sign *= -1;                               // Flip Sign
    }
    // Calculate pi
    pi = 4 * series;
    // Display results
    cout << "Leibnitz yeilds " << pi << " with " << iter << " iterations" << endl;
    cout << "System yeilds " << PI << endl;
    return pi;
}
/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * Computes the square root of a number using Newton's method
 *
 * @param[in]      radicand - value to find the square root of
 *
 * @returns        guess    - square root of the radicand
 *
 *****************************************************************************/
double newtons(double radicand) {
    // Initialize variables
    int iter = 0;
    double guess = 1;
    double change = 0;
    bool found = false;
    // Loops until answer is found
    while(!found) {                                // While not found
        change = (guess + radicand / guess) / 2.0; // Calculate change
        if(abs(change - guess) > .00001) {         // If change != guess
            guess = change;                        // Set guess to change
        }
        else {
            found = true;                          // Otherwise, it's found
        }
        iter++;
    }
    // Display results
    cout << "Newton's yields " << guess << " with " << iter << " iterations" << endl;;
    return guess;
}
/**************************************************************************//**
 * @author Michael Pfeifer
 *
 * @par Description:
 * Computes the sine of an angle (in degrees)
 *
 * @param[in]      angle    - angle to find sine of
 * @param[in]      iter     - number of iterations to run
 *
 * @returns        sine     - sine of the angle
 *
 *****************************************************************************/
double taylor(double angle, int iter) {
    // Initialize variables
    double sine = 0;     // Needs to start at 0
    int sign = 1;        // First iteration should be positive
    // Once for each iteration
    for(int i = 0; i < iter; i++) {
        sine += sign * pow(angle, 2 * i + 1) / factorial(2 * i + 1); // sine +- (X^n / n!)
        sign *= -1;                                                  // Flip Sign
    }

    // Display results
    cout << "Taylor yields " << sine << " with " << iter << " iterations" << endl;
    cout << "System yields " << sin(angle) << endl;
    return sine;
}
