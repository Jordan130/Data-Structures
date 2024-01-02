/*
 Name: Jordan Rios
 Course: CSCI_362
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

using std::cout;
using std::cin;

// Finds the largest value in the passed vector
// Assumes nums is not empty
float
maximum (const std::vector<float>& nums)
{
	float comparer = 0.0f;
	for (int i = 0; i < nums.size (); ++i)
	{
		if (nums.at (i) > comparer){
			comparer = nums.at (i);
		}
	}
	return comparer;
}

// Finds the smallest value in the passed vector
// Assumes nums is not empty
float
minimum (const std::vector<float>& nums)
{
	float smallest_value = nums.at (0);
	for (int i = 0; i < nums.size (); ++i)
	{
		if (nums.at (i) < smallest_value){
			smallest_value = nums.at (i);
		}
	}
	return smallest_value;
}

// Finds the sum of values from the passed vector
// Should return zero if the vector is empty
float
sumOfValues (const std::vector<float>& nums)
{
	if (nums.size () == 0)
	{
		return 0.0f;
	}
	float total = 0;
	for (int i = 0; i < nums.size (); ++i)
	{
		total = total + nums.at (i);
	}
		return total;
}

// Finds the average of all values from the passed vector
// assumes nums is not empty
float
average (const std::vector<float>& nums)
{
	float average = 0;
	for (int i = 0; i < nums.size (); ++i)
	{
		average = average + nums.at (i);
	}
		return average/nums.size ();
}

// Creates and returns a new vector. Reads in count number
// of values from the user by prompting for each one
// should return an empty vector if count <= 0
std::vector<float>
populate (int count)
{
    double value;
	std::vector<float> result;
	for (int i = 0; i < count; ++i)
    {
        cout << "Enter value ==> ";
        cin >> value;
        result.push_back (value);
    }
	return result;
}