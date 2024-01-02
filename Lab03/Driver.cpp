/*
 Name: Jordan Rios
 Course: CSCI 362
 Date: 1/24/23
 Assignment: Statistician Redux
 Description: This program takes in a certain amount of values by the user and prints out the statistics of the values.
 */

/***************************************************************/
// System includes

#include <iostream>

/***************************************************************/
// Local includes

#include "Statistician.h"

/***************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;

/***************************************************************/

// Main
int
main(int argc, char* argv[])
{
    int num_of_values;
    cout << "Enter number of values ==> ";
    cin >> num_of_values;
    std::vector<float> populatedVector = populate(num_of_values);
    float sum = sumOfValues(populatedVector);
    float avg = average(populatedVector);
    float min = minimum(populatedVector);
    float max = maximum(populatedVector);
    cout << "\nThe statistics of all " << num_of_values << " values are:" << endl;
    cout << "  Sum: " << sum << endl;
    cout << "  Avg: " << avg << endl;
    cout << "  Min: " << min << endl;
    cout << "  Max: " << max << endl;
    return 0;
}
