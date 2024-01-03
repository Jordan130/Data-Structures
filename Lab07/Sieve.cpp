/*
 Name: Jordan Rios
 Course: CSCI 362
 Date: 3/29/23
 Assignment: THE SIEVE OF ERATOSTHENES
 Description: This program removes primes from a range of 2 - N and finds the time it takes to do so.
 */

/***************************************************************/
// System includes

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <math.h>

/***************************************************************/
// Local includes

#include "Timer.hpp"

/***************************************************************/
// Using declarations

using std::set;
using std::vector;
using std::string;
using std::cout;
using std::endl;

/***************************************************************/

set<unsigned>
sieveSet (unsigned N) {
    set<unsigned> primes;
    for (unsigned i = 2; i <= N; ++i){
        primes.insert(i);
    }
    unsigned increment;
    for(unsigned number = 2; number < N; number++){
        increment = number;
        while(increment < N) { 
            increment += number;
            if(increment <= N) {
                auto p = primes.find(increment);
                if(p != primes.end()) {
                    primes.erase(p);
                }
            }
        }
    }
    return primes;
};

set<unsigned>
sieveVector (unsigned N) {
    vector<bool> primes (N + 1, true);
    primes[0] = false;
    primes[1] = false;
    for(unsigned incr = 2; incr <= sqrt(N); ++incr){
        auto iter = primes.begin() + incr;
        while(iter != primes.end()){
            for(unsigned i = 1; i <= incr; ++i){
                ++iter;
                if(iter == primes.end()) {
                    break;
                }
            }
            if(*iter) {
                *iter = false;
            }
        }
    }
    set<unsigned> s;
    for(size_t i = 0; i < primes.size(); i++){
        if(primes[i] == true){
            s.insert(i);
        }
    }
    return s;
}

int main(int argc, char const *argv[])
{
   string s (argv[1]);
   string n (argv[2]);
   unsigned N = stoi(n);
   if(s == "vector"){
    Timer <std::chrono::steady_clock> time1;
    double finalTime;
    time1.start();
    set<unsigned> newSet = sieveVector(N);
    time1.stop();
    finalTime = time1.getElapsedMs();
    cout << "Pi[" << N << "] = " << newSet.size() << " (using a vector)" << endl;
    cout << "Time: " << finalTime << " ms" << endl;
   }
   else if(s == "set"){
    Timer <std::chrono::steady_clock> time1;
    double finalTime;
    time1.start();
    set<unsigned> newVector = sieveSet(N);
    time1.stop();
    finalTime = time1.getElapsedMs();
    cout << "Pi[" << N << "] = " << newVector.size() << " (using a set)" << endl;
    cout << "Time: " << finalTime << " ms" << endl;
   }
}
/*
N       10,000,000    20,000,000   40,000,000
=============================================
set        124104       300425      658236
vector     318835       903598      65275e6

With my implementation of sieve, I found that my set out preforms my vector.

In the vector function I have a nested loop and the time it takes to run through all of the numbers
and insert and iterate can take up a lot of time. Therefore, I would say its time complexity would be O(n^2)

In the set method I used the find() function and this did a lot of the work here. Using the find here
would make this run in O(nlogn) and make's sense why it does so much better than the vector.
*/
