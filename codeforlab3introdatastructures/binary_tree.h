#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>

//A binary tree node that contains a character as data, and a pointer to the left and right node
class BinNode
{
private:
    BinNode(char ch)
    {
        this->ch = ch;
        left = nullptr;
        right = nullptr;
    }
    //attributes of the node
    char ch;
    BinNode* left;
    BinNode* right;
    friend class BinaryTree;
};

//Binary tree data structure, used for our decoding process
//going to the left means 0, going to the right means 1
//
class BinaryTree
{
    //public interface
public:
    //default constructor, creates a tree with one node
    BinaryTree(); 

    // //deletes the copy constructor
    // BinaryTree(const BinaryTree&) = delete;

    // //deletes the assignment operator, since we dont want to copy a binary tree into another
    // BinaryTree& operator=(const BinaryTree&) = delete;

    //this function takes in a 0 or 1 code as a string, it walks over tree using the code and returns corresppnding charcter
    char get(std::string code) const;

    //this function the character and code, walks over the tree using the code, and inserts the character at the correct location
    void insert(char ch, std::string code);

    //destructor
    ~BinaryTree();


    //private data members
private:

    BinNode* root; //the root of our binary tree, an empty binary tree only has a root

    //this function cleans the subtree rooted at node
    //its a private function, since its type BinNode
    void clean(BinNode* node);
};

#endif
