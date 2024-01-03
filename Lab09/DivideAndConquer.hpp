// File: DivideAndConquer.hpp
// Author: Gary Zoppetti and Will Killian and Chad Hogg and Jordan Rios

#ifndef DIVIDE_AND_CONQUER_HPP_
#define DIVIDE_AND_CONQUER_HPP_

#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>

// NOTE: you are forbidden from using anything from <algorithm> for this assignment
//       EXCEPT for std::copy

namespace SortUtils
{

// [9]
// Given a RandomAccessRange [first, last), determine where the "midpoint"
// would be and perform the following steps:
// order *first, *mid, *std::prev(last) in such a way such that
//   *first <= *mid <= *std::prev(last)
//
// returns an iterator to mid -- a.k.a. the median
//
template<typename Iter>
Iter
median3 (Iter first, Iter last)
{
  // TODO
  int distance = std::distance (first, last);
  auto middle = first + distance / 2;
  if (*first > *middle) 
  {
    std::swap (*first, *middle);
  }
  if (*middle > *std::prev (last)) 
  {
    std::swap (*middle, *std::prev (last));
  }
  if (*first > *middle) 
  {
    std::swap (*first, *middle);
  }
  return middle;
}

// [10]
// Takes two sorted ranges [first1, last1) and [first2, last2)
// and "merges" them by copying values into the iterator starting
// at "out". Uses operator< for comparing values
//
// Returns the iterator of one-past-the-last where we wrote to out
//
template<typename Iter1, typename Iter2, typename OIter>
OIter
merge (Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, OIter out)
{
  // TODO
  //if we got to the end for both iterators, return out
  if (first1 == last1 && first2 == last2)
  {
    return out;
  }

  //If JUST first1 == last1 or the other way around, we assume that the rest of the
  //other list is sorted and we can insert it into out as is, then return out.
  if (first1 == last1) 
  {
    return std::copy (first2, last2, out); 
  } 
  else if (first2 == last2) 
  {
    return std::copy (first1, last1, out);
  }

  if (*first1 < *first2)
  {
    *out = *first1;
    ++out;
    ++first1;
  } 
  else 
  {
    *out = *first2;
    ++out;
    ++first2;
  }

  return SortUtils::merge (first1, last1, first2, last2, out);
}


// [15]
// Takes a RandomAccessRange [first, last) and partitions the data into
// three groups -- this should be accomplished in a SINGLE PASS Big-O: O(N)
//
// Group 1: all values in [first, last) < pivot
// Group 2: all values in [first, last) == pivot
// Group 3: all values in [first, last) > pivot
//
// [ ... Group 1 ... | ... Group 2 ... | ... Group 3 ... ]
//                   ^                 ^
//                   p1                p2
//
// Returns a pair of iterators pointing to "p1" and "p2" above
//
// Hint: See separate Three Way Partition explanation in handout.
//
template<typename Iter, typename Value>
std::pair<Iter, Iter>
partition (Iter first, Iter last, Value const& pivot)
{
  // TODO
  Iter low = first;
  Iter equal = first;
  Iter high = --last;

  while (equal != high) {
    //case 1: *equal < pivot
    if (*equal < pivot)
    {
      std::swap (*low, *equal);
      ++low;
      ++equal;
    } 
    // case 2: *equal > pivot
    else if (*equal > pivot) 
    {
      std::swap (*high, *equal);
      --high;
    } 
    //case 3
    else 
    {
      ++equal;
    }
  }

  if (*equal < pivot) 
  {
    std::swap (*low, *equal);
    ++low;
  } 
  else if (*equal > pivot)
  {
    std::swap (*high, *equal);
    --high;
  } 
  ++high;
  return std::make_pair(low, high);
}

// [10]
// Given a RandomAccessRange, recursively call partition on either the
// left half or right half until you have found the nth largest element
//
// A call to nth_element (v.begin(), v.end(), 0) will return the min
// A call to nth_element (v.begin(), v.end(), v.size() - 1) will return the max
// A call to nth_element (v.begin(), v.end(), v.size() / 2) will return the median
//
// Precondition:
//   std::distance (begin, end) > n
//
// Hints:
//  - n will change if you need to recurse on the right half
//  - No recursion happens if "index of" n is between "index of" p1 and p2
//    remember: p1 and p2 are the return values to partition.
//  - call median3 to get a pivot value
//  - when calling partition, remember to dereference the iterator returns by median3
//
template<typename Iter>
Iter
nth_element (Iter first, Iter last, size_t n)
{
  // TODO
  // auto [p1, p2] = SortUtils::partition (...);
  if (std::distance (first, last) < 2) 
  {
    return first;
  }
  auto const pivot = *SortUtils::median3 (first, last);
  auto [p1, p2] = SortUtils::partition (first, last, pivot);

  //case 1: if n is in range first, p1
  //recursive
  if(n < std::distance (first, p1)) 
  {
    return nth_element (first, p1, n);
  }
  //case 2: if n is in p1, p2
  // return nth iter
  else if (n < std::distance (first,p2)) 
  {
    return first + n;
  }
  //case 3: if n is in the range p2, last
  //recursive
  else 
  {
    return nth_element (p2, last, n - std::distance (first, p2));
  }
}

// [10]
// Given a RandomAccessRange, sort using merge sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - You will need a vector to act as a temporary buffer.
//   - The merge function will expect that vector to already be big enough
//     to hold all of the elements.
//
template<typename Iter>
void
merge_sort (Iter first, Iter last)
{
  const size_t N = std::distance (first, last);
  Iter middle = first + N / 2;
  using T = std::remove_reference_t<decltype (*std::declval<Iter> ())>;

  //Base
  if(N < 2) 
  {
    return;
  } 

  // Recursive
  SortUtils::merge_sort(first, middle);
  SortUtils::merge_sort(middle, last);
  std::vector<T> buf (N);
  SortUtils::merge(first, middle, middle, last, buf.begin());
  std::copy_n (buf.begin(), N, first);
}

// Provided for you -- no need to change.
template<typename Iter>
void
insertion_sort (Iter first, Iter last)
{
  for (Iter i = first; i != last; ++i)
  {
    for (Iter j = i; j != first; --j)
    {
      if (* (j - 1) > *j)
      {
        std::iter_swap (j - 1, j);
      }
      else
      {
        break;
      }
    }
  }
}


// [10]
// Given a RandomAccessRange, sort using quick sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - median3 will be called to find the pivot
//   - remember to dereference the iterator returned by median3 to get the pivot value
//   - partition should be called
//   - if there are fewer than 16 elements, use the provided insertion sort instead
//
template<typename Iter>
void
quick_sort (Iter first, Iter last)
{
  // TODO
  const auto N = std::distance (first, last);
  // T is the type of data we are sorting
  using T = std::remove_reference_t<decltype (*std::declval<Iter> ())>;

  //base
  if (N < 2) return;
  //recursive
  auto pivot = *SortUtils::median3 (first, last);
  auto [p1, p2] = SortUtils::partition (first, last, pivot);
    
  SortUtils::quick_sort (first, p1);
  SortUtils::quick_sort (p2, last);
}

} // end namespace util

#endif
