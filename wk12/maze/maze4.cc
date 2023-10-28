#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.
std::vector<Node> mmm;

bool test(Node &node){
    for (auto x : mmm){
        if ( &x == &node ){
            return true;
        }
    }
    return false;

}


/**
 * @brief Find the shortest path from startNode to endNode using Djikstra's algorithm, where all path distances are 1
 * @param startNode  The node to start the search from
 * @param endNode  The node to end the search at
 * @param path  The path from startNode to endNode. If no path is found or if startNode is the same as endNode, path should be empty. The path should be in the order of the nodes visited, starting with startNode and ending with endNode
 * @return bool True if a path was found, false otherwise
 */

bool findShortestPath(Node &startNode, Node &endNode, std::vector<std::pair<int, int>>& path) {
    unsigned int index = 0;

    mmm.push_back(startNode);
    startNode.color = 1;

    while(true){

        if ( index >= mmm.size() ){
            return false;
        }

        Node current = mmm[index];
        //path.push_back( {startNode.x, startNode.y} );
        //startNode.color = 1;

        if ( current.up != nullptr ){ // ylä
            if ( current.up == &endNode){
                mmm.push_back(endNode);
                current.up->color = 1;
                //break;
            }
            if (!test( *current.up)){
                mmm.push_back(*current.up);
                current.up->color = 1;
            }


        }
        if ( current.down != nullptr ){ // ala
            if ( current.down == &endNode){
                mmm.push_back(endNode);
                current.down->color = 1;
                //break;
            }
            if (!test( *current.down) ){
                mmm.push_back(*current.down);
                current.down->color = 1;
            }

        }

        if ( current.left != nullptr ){ // vasen
            if ( current.left == &endNode){
                mmm.push_back(endNode);
                current.left->color = 1;
                //break;
            }
            if (!test( *current.left) ){
                mmm.push_back(*current.left);
                current.left->color = 1;
            }

        }

        if ( current.right != nullptr ){ // oikee
            if ( current.right == &endNode){
                mmm.push_back(endNode);
                current.right->color = 1;
                //break;
            }
            if (!test( *current.right) ){
                mmm.push_back(*current.right);
                current.right->color = 1;
            }

        }

        index += 1;
    }

    for (auto x : mmm){
        std::cout << "coord" << x.x << " " << x.y << std::endl;
        path.push_back( {x.x, x.y} );
    }
    return true;
    // End of student code
}
