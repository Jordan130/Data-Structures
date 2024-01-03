////////////////////////////////////////////////////////////////////////////////
// Name: Jordan Rios
// Date: 3/21/23
// Assignment: Josephus
// Description: Killing people brutally in a circle.
//
////////////////////////////////////////////////////////////////////////////////

/***************************************************************/
// System includes
// TODO: add additional includes
#include <list>

/***************************************************************/
// Local includes

#include "Josephus.h"

/***************************************************************/
// Using declarations

using std::list;

/***************************************************************/

/* Simulate the Josephus problem modeled as a std::list.
 * This function will modify the passed list with only a
 * single survivor remaining.
 *
 * @param circle -- the linked list of people
 * @param k -- skip amount. NOTE: k > 0
 *
 * @return a list of those who are executed in chronological order
 */
/*
  The time conplexity of this function would be O(n^2) or T(N*(k-1)). The while loop with 
  a for loop inside makes this function quadratic because the while loop checks
  the circle size each time and the for loop runs k-1 times. There might be a discrepancy 
  between that number and the amount of links travsersed which could be attributed to cases where the 
  begin() == end(), and we have to add another link traverseral.
*/
template <typename T>
list<T>
execute (list<T>& circle, int k)
{
  int linksTraversed = 0;
  list<int> killed;
  auto iter = circle.begin ();
  while (circle.size () > 0)
  {
    for (int i = 1; i <= k - 1; ++i)
    {
      if(iter == prev (circle.end ()))
      {
        iter = circle.begin ();
        ++linksTraversed;
      }
      else{
        ++iter;
        ++linksTraversed;
      }
    }
      killed.push_back (*iter);
      if(iter == prev (circle.end ()))
      {
        circle.erase (iter);
        iter = circle.begin ();
        ++linksTraversed;
      }
      else
      {
        iter = circle.erase (iter);
      }
  }
  return killed;
}

/* entry point to the Josephus problem from the autograder / main
 *
 * @param n -- number of people in the circle
 * @param k -- skip amount. NOTE: k > 0
 */
int
josephus (int n, int k)
{
  // 1. make a list
  // 2. populate it with values [1, 2, 3, ... , N]
  // 3. call execute
  // 4. return the lone survivor

  // HINT: While working on this lab, you may also find
  //       it useful to print out the "kill" order.
  list<int> circle;
  for (int i = 1; i <= n; ++i)
  {
   circle.push_back (i);
  }
  list<int> newList = execute (circle, k);
  return newList.back ();
}