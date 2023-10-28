/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printHalf(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
    list<int>::const_iterator ptr;
    list<int>::const_iterator mid = lst.begin();
    int size = lst.size();
    advance(mid,size/2);

    for (ptr = lst.begin(); ptr != mid; ++ptr){
        cout << *ptr << " ";
    }

    cout << endl;
}
