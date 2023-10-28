#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.
std::map<std::pair<int,int>, Node*> maze;
//std::set<Node*> mz;
/**
 * @brief Create a Node object
 * 
 * @param loc  The location of the node
 * @return Node*  A pointer to the node that is created. If the node already exists, return a pointer to the existing node
 */
Node* createNode  (std::pair<int, int> loc, std::map<std::string, Node*> paths) {

    if ( maze.find(loc) == maze.end()){

        struct Node* newNode = new Node;

        newNode->x = loc.first;
        newNode->y = loc.second;

        for (auto dir : paths){
            if ( dir.first == ABOVE){
                newNode->up = dir.second;
            }
            if ( dir.first == BELOW){
                newNode->down = dir.second;
            }
            if ( dir.first == LEFT){
                newNode->left = dir.second;
            }
            if ( dir.first == RIGHT){
                newNode->right = dir.second;
            }
        }
        maze[loc] = newNode;
        return newNode;
    }
    return maze[loc];

}
