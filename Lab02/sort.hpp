// Author     : Jordan Rios
// Date       : 2/6/23
// Class      : CSCI 362
// Assignment : Analyzing Sorting Algorithms
//
// Description: Sorts a user specified input that's stored into a vector and 
//              this program can sort it using different sorting algorithms. Also, 
//              it produces the number of swaps and comparisions that the algorithm the
//              user choose produced.
//
// Header file for templated sorting algorithms, specifically
// bubble sort (optimized), insertion sort, and selection sort.
// Includes a 'Statistics' datatype for aggregating counts for
// swaps and comparisons.

#ifndef SORTING_ALGORITHMS_HPP_
#define SORTING_ALGORITHMS_HPP_

#include <vector>
#include <iostream>

struct Statistics {
  // default constructs swaps and compares to zero
  std::size_t numSwaps { 0 };
  std::size_t numCompares { 0 };
};

template <typename T>
void
bubbleSort (std::vector<T>& v, Statistics& s)
{
  for (size_t i = v.size() - 1; i >= 1; --i) 
  {
      bool didSwap = false;
      for (size_t j = 0; j < i; ++j) 
      {
        s.numCompares++;
          if (v[j] > v[j + 1]) 
          {
              s.numSwaps++;
              std::swap (v[j], v[j + 1]);
              didSwap = true;
          }
      }
       if (!didSwap) break;
  }
}

template <typename T>
void
insertionSort (std::vector<T>& v, Statistics& s)
{
  for (size_t i = 1; i < v.size(); ++i) 
    {
        int k = v[i]; 
        int j = i;   

       
        while (j >= 1 && k < v[j - 1]) 
        {
          s.numCompares++;
            v[j] = v[j - 1];
            --j;
        }
        if(j >= 1){
            s.numCompares++;
        }
        v[j] = k;
    }
}

template <typename T>
void
selectionSort (std::vector<T>& v, Statistics& s)
{
   for (size_t i = 0; i < v.size() - 1; ++i) 
    {
        size_t min = i;
        for (size_t j = i + 1; j < v.size(); ++j) 
        {
            s.numCompares++;
            if (v[j] < v[min]) {
                min = j;
            }
        }
            std::swap (v[i], v[min]);
            s.numSwaps++;
    }
}
#endif