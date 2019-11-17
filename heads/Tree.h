#include <iostream>
#include <cstdlib>
#include "Tile.h"
//
// Created by Nicholas David Fay on 5/27/19.
//
using namespace std;
#ifndef GAME_TREE_H
#define GAME_TREE_H

struct tileNode {
    // name
    string name;
    // depth of each node calculated in foundNode
    int depth;
    // tile pointer (linked tiles)
    Tile *tile;
    // left move
    int nodeID; //(10 * x) + y
    tileNode *leftChild;
    // right move
    tileNode *rightChild;
    
};

class BST {
    /**
     * find farthest left move (find min)
     * @param tileNode
     * @return move tile
     * THis function find the farthest left move that can be made
     */
    int findMin(tileNode *node);
    /**
     * find farthest right move (find max)
     * @param node
     * @return move tile
     * This function finds the farthest right move that can be made
     */
    int findMax(tileNode *node);
    /**
     * Delete Tile Tree (delete)
     * @param tile
     * This will go through and delete unnessesary trees after moves are made
     */
    void DeleteSubtrees(tileNode *tile);

//public attributes for BST
public:
    BST();
    /**
     * node found (find node)
     * @param tilenode
     * @param nodeID
     * @return 1 or 0
     * find the node in the tree if it exists, then sets the depth of the node
     */
    int foundNode(tileNode *tilenode, int nodeID);
    /**
     * Constructor for delete (constructor)
     * @param tile
     * This calls DeleteTileTree then after everything is freed in the tree
     * it will set the source node back to the nullptr
     */
    void constructDelete(tileNode *tile);


    //This is the root (source tile node) in the Tree
    tileNode *sourceNode;
    /**
     * traverse (in-order)
     * @param tileNode
     * prints the in order traversal
     */
    void traverse(tileNode *tileNode);
    /**
     * Insert TILE (TILE added to tree)
     * @param newNode
     * @param sourcenode
     * This adds the tile into the tree
     * after it is inserted it calls foundNode
     * to determine it was actually placed in the tree
     * then sets the depth of the node
     */
    void insert(tileNode *newNode, tileNode* sourcenode = nullptr);

};

#endif //GAME_TREE_H
