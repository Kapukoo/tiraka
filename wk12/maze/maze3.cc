#include <iterator>
#include <vector>
#include <algorithm>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.


/**
 * @brief Connect two adjacent nodes together. If the nodes are not adjacent, do nothing
 * 
 * @param fromNode  The node to connect from
 * @param toNode  The node to connect to
 */
void connectNodes(Node& node1, Node& node2) {

    //std::cout << "node 1 " << node1.y << std::endl;
    //std::cout << "node 2 " << node2.y << std::endl;

    if ( node1.y+1 == node2.y && node1.x == node2.x){ // up
        //std::cout << "up " << std::endl;
        node1.up = &node2;
        node2.down = &node1;
    }

    if ( node1.y-1 == node2.y && node1.x == node2.x){ // down
        node1.down = &node2;
        node2.up = &node1;
    }

    if ( node1.x-1 == node2.x && node1.y == node2.y){ // left
        node1.left = &node2;
        node2.right = &node1;
    }

    if ( node1.x+1 == node2.x && node1.y == node2.y){ // right
        node1.right = &node2;
        node2.left = &node1;
    }



}
