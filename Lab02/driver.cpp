/*
 In general, your program should be split up into different sections

 Section 0: Top Comment Block
   Always include the following:
   - First and last name
   - Last date of modification
   - Course + Section
   - Assignment Name
   - File Description

 Section 1: Includes (must be in the following order)
   1. C++ standard library includes (e.g. <algorithm>)
   2. C library includes (e.g. <math.h> or <cmath>)
   3. System library includes (<name.h> but are not part of the C or C++ standard)
   4. User includes (ones contained in quotes -- e.g. "Timer.hpp")

 Section 2: Preprocessor Definitions
   - Anything that starts with #define (or appropriate guards around it

 Section 3: Compile-time constants, type aliases, using directives, type definitions
   - constexpr Type name = value-expr;
   - using Type = type-expr;
   - using std::cout;
   - declarations of file-scoped struct/class/union

 Section 4: Global variables -- NOTE: use sparingly and ONLY if necessary

 Section 5: Forward declarations for non-template functions
   - A forward declaration is a function without a body.
   - Any default parameters MUST be specified in the forward declaration

 Section 6: Template function implementations
   - Any functions beginning with 'template <...>'

 Section 7: main() function implementation [[[entry point of program]]]
   - main must always have the following signature:
     int main (int argc, char* argv[])

 Section 8: Implementations of non-template functions
   - Must be listed in the SAME ORDER as the forward declarations above
   - REMINDER: whenever you update the parameter types/counts, update
     them in BOTH locations. Otherwise you can get a compiler error!
*/

/*
 Name       : Jordan Rios
 Course     : CSCI 362
 Date       : 2/6/23
 Assignment : Analyzing Sorting Algorithms
 Description: Sorts a user specified input that's stored into a vector and 
              this program can sort it using different sorting algorithms. Also, 
              it produces the number of swaps and comparisions that the algorithm the
              user choose produced.
 */

/***************************************************************/
// System includes

#include <iostream>
#include <algorithm>
#include <random>

/***************************************************************/
// Local includes

#include "sort.hpp"

/***************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/***************************************************************/

// Populates a vector either accending, decending, or in a random order.
template <typename T> 
vector<T>
populate (T N, char type, int seed)
{
	vector<T> populated_vector;
  if (type == 'a')
  {
    for (size_t i = 1; i <= N; ++i)
    {
        populated_vector.push_back (i);
    }
  }
  else if (type == 'd')
  {
    for (size_t i = N; i >= 1; --i)
    {
        populated_vector.push_back (i);
    }
  }
  else
  {
    std::minstd_rand random (seed);
    for (size_t i = 1; i <= N; ++i)
    {
      populated_vector.push_back (random () % 10000);
    }
  }
	return populated_vector;
}

// Main.
int
main (int argc, char* argv[])
{
  size_t N;
  string algorithm;
  char type;
  Statistics s;
  int seed;
  string check_sorted;
  cout << "N         ==> ";
  cin >> N;
  cout << "Algorithm ==> "; 
  cin >> algorithm;
  cout << "Type      ==> ";
  cin >> type;
  if (type == 'r')
  {
    cout << "Seed      ==> ";
    cin >> seed;
  }

  vector<size_t> A = populate (N, type, seed);
  vector<size_t> ACopy (A);
  sort (ACopy.begin (), ACopy.end ());

  if (algorithm == "bubble")
  {
    bubbleSort (A, s);
  }
  else if (algorithm == "insertion")
  {
    insertionSort (A, s);
  }
  else
  {
    selectionSort (A, s);  
  }
  if (ACopy == A)
  {
    check_sorted = "yes";
  }
  else
  {
    check_sorted = "no";
  }
  printf ("\n# Compares: %0.1d\n", int (s.numCompares));
  printf ("# Swaps   : %0.1d\n", int (s.numSwaps));
  printf ("Sort ok?    %s\n", check_sorted.c_str ());
}
