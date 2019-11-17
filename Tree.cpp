//
// Created by Nicholas David Fay on 5/27/19.
//
#include "heads/Tree.h"
#include "heads/Board.h"

BST::BST()
{
    // Inits the Binary Search Tree's source node "root" to Null
    sourceNode = nullptr;
}

//nodeID for newNode must be set as (x*10 + y)
void BST::insert(tileNode *newNode, tileNode* sourcenode) {
    //If the tile is already in the tree, then do not insert
    if(foundNode(sourceNode, newNode->nodeID)) {
        return;
    }
    if(sourcenode == nullptr) {
        sourcenode = newNode; //sets root
        sourcenode->tile = newNode->tile;
        sourcenode->leftChild = nullptr;
        sourcenode->rightChild = nullptr;
        foundNode(sourceNode, sourcenode->nodeID);
    } else {
        if(newNode->nodeID >= sourcenode->nodeID) {
            if (sourcenode->rightChild == nullptr){
                sourcenode->rightChild = newNode;
                newNode->leftChild = nullptr;
                newNode->rightChild = nullptr;
                foundNode(sourceNode, newNode->nodeID); //sets depth
            } else {
                insert(newNode, sourcenode->rightChild);
            }
        } else {
            if(sourcenode->leftChild == nullptr) {
                sourcenode->leftChild = newNode;
                newNode->leftChild = nullptr;
                newNode->rightChild = nullptr;
                foundNode(sourceNode, newNode->nodeID); //sets depth
            } else {
                insert(newNode, sourcenode->leftChild);
            }
        }
    }
}

void BST::constructDelete(tileNode *tile)
{
    //if the source node is null, we have nothing to delete
    if(tile == nullptr)
        return;
    //frees all nodes in the tree
    DeleteSubtrees(tile);
    //sets the source node back to nullptr
    sourceNode = nullptr;
}

void BST::DeleteSubtrees(tileNode *tile)
{
    if(tile) {
        //call to function with the tiles leftChild move
        // also call to function with tiles rightChild move
        // Delete left subtree of the BST
        DeleteSubtrees(tile->leftChild);
        // Delete right subtree of the BST
        DeleteSubtrees(tile->rightChild);
        //delete the tile we are looking at
        delete tile;
    }
}

void BST::traverse(tileNode *tileNode)
{

    // if the node is not a null node
    if(tileNode)
    {
        //in order traversal
        //left
        if (tileNode->leftChild != nullptr) {
            traverse(tileNode->leftChild);
        }
        //root
        cout << tileNode->name << "     " << tileNode->depth << "     ";
        //right
        if (tileNode->rightChild != nullptr) {
            traverse(tileNode->rightChild);
        }
    }
}

int BST::findMin(tileNode *node)
{
    //temp node to store ID
    struct tileNode *temp;
    temp = node;
    //loop through all the smallest numbers till you get to the greatest
    while(temp->leftChild) {
        temp = temp->leftChild;
    }
    // return the smallest node ID
    return temp->nodeID;
}

int BST::findMax(tileNode *node)
{
    //temp node to store ID
    struct tileNode *temp;
    temp = node;
    //loop through all the greatest numbers till you get to the greatest
    while(temp->rightChild) {
        temp = temp->rightChild;
    }
    //return the greatest node ID
    return temp->nodeID;
}

int BST::foundNode(tileNode *tilenode, int nodeID)
{
    int level = 0;
    tileNode *temp;
    temp = tilenode;
    // loop until null leaf
    while(temp)
    {
        //update level of the node
        level += 1;
        if(temp->nodeID == nodeID)
        {
            //this allows for the depth of each node to be set
            temp->depth = level - 1;
            // the node was found in the tree
            return 1;
        }
        // if the current nodeID is greater than the ID given
        else if(nodeID < temp->nodeID) {
            //update temp to be its left child
            temp = temp->leftChild;
        }
        //if the current nodeID is less than the ID given
        else if(nodeID > temp->nodeID ) {
            //update temp to be its right child
            temp = temp->rightChild;
        }
    }
    delete tilenode;
    //node was not found in the BST
    return 0;
}
