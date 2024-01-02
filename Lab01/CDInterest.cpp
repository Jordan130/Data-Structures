/*
  Filename   : Lab1.cpp
  Author     : Jordan Rios
  Course     : CSCI 362
  Date       : 1/23/2023
  Assignment : CDInterest
  Description: This program calculate's the interest earned on a certificate of deposit (CD) over a specified period.
*/

/***************************************************************/
// System includes

#include <iostream>

/***************************************************************/
// Using declarations

using std::cin;
using std::cout;

/***************************************************************/

// Prompts the user what this program does.
void 
printIntro()
{
  cout << "This program will calculate the interest earned \n on CD over a period of several years.\n\n";
}

// This function will take a balance and calcuate the interest of that balance based on the rate that was passed into it.
double
calculateInterest (double balance, double rate)
{
  double interest = (balance * rate) / 100;
  return interest;
}

// This is a helper function for printTable that prints each row.
void 
printRow (int rowNum, double balance, double interest)
{
 printf ("%-4d%12.2f%13.2f%16.2f\n", rowNum, balance, interest, balance + interest);
}

// This function prints the CD interest table.
void 
printTable (int numRows, double balance, double rate)
{
  printf ("%-4s%12s%13s%16s\n", "Year", "Balance", "Interest", "New Balance");
  printf ("%-4s%12s%13s%16s\n", "----", "-------", "--------", "-----------");
  
  for (int year = 1; year <= numRows; ++year)
  {
    double interest = calculateInterest (balance, rate);
    interest = (int) (interest * 100) / 100.0; 
    printRow (year, balance, interest);
    balance = balance + interest;
  }
}

// The main function asks for user input and calls the other functions.
int 
main ()
{
  double balance;
  double rate;
  int years;
  printIntro ();
  cout << "Please enter the initial balance: ";
  cin >> balance;
  cout << "Please enter the interest rate  : ";
  cin >> rate;
  cout << "Please enter the number of years: ";
  cin >> years;
  cout << "\n";
  printTable (years, balance, rate);
  return 0;
}
