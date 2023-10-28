#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    vector<int> v;
    int size = vec.size();
    
    for (int i = 0; i < size; i=i+2)
    { v.push_back( vec[i] ); }

    vec = v;
    v.clear();

}

