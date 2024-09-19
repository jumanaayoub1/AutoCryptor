#include "binary_tree.h"

BinaryTree::BinaryTree()
{
    root = new BinNode(' '); 
}

char BinaryTree::get(std::string code) const
{
    //creating pointer to point to root of tree, using that pointer to travel the tree
    BinNode* curr = root;

    for(int i = 0; i < code.length(); i++)
    {
        //we run the for loop based on the codes length, and if curr returns nullptr, means that code doesnt exist in the tree
        //that means search wasn't successful, return whitespace
        if (curr == nullptr)
        {
            return ' ';
        }

        //the traversal process is to visit the left child if the code is zero, or visit the right child if the code is one
        //if code at index i is zero, visit left child
        if(code[i] == '0')
        {
            curr = curr->left;
        }
        else

        //otherwise, visit the right child
        {
            curr =curr->right;
        }
    }

    //the current is pointing to the corresponding character of the code passed into the function
    //returning corresponding character to the code
    return curr->ch;
}

void BinaryTree::insert(char ch, std::string code)
{
    //creating a new node using the input data
    BinNode* inserted = new BinNode(ch);
    int i = 0;

    //creating pointer to point to binary tree, points to root and travels the binary tree
    BinNode* curr = root;

    //travel the tree using the code to the location of insertion
    // Traversal strategy
    while(i < code.length() - 1)
    {
        if(code[i] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
        i++;
    }

    //if the last character of the code is 0, insert that code to the left of the binary tree
    if(code[i] == '0')
    {
        curr->left = inserted;
    }

    //otherwise, insert to the right of the binary tree
    else
    {
        curr->right = inserted;
    }
}

//destructor, cleaning the root to erase the entire tree
BinaryTree::~BinaryTree()
{
    clean(root);
}

//recursive function deletes a node and all its children
void BinaryTree::clean(BinNode* node)
{
    //if there's nothing to delete
    if(node == nullptr)
    {
        return;
    }
    //we only delete a node if left and right are already deallocated
    //visit the left and right node of the node passed in, and clean them
    clean(node->left);
    clean(node->right);
    
    //and then after deallocating the left and right nodes, delete that node that was pointing to them 
    delete node;

}
