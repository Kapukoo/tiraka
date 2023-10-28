/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printReverse(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
    list<int>::const_reverse_iterator ptr;

    for (ptr = lst.rbegin(); ptr != lst.rend(); ptr++){
        cout << *ptr << " ";
    }

    cout << endl;
}
