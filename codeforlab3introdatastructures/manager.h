#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "hashtable.h"
#include "binary_tree.h"
//void greeting fucntion to print greeting statement
void greet();

//function to displays a message asking the user if they want to continue, and receives the yes or no answer
std::string getYesNoAnswer(std::string message);

//takes in the path of the cipher file, loads the data arrays, hashtable, and binary tree and returns the number of codes (Size of cipher file)
int loadCipher(std::string path, char chars[100], std::string codes[100], HashTable &table, BinaryTree &tree);

//takes in the path of the file thats not encoded, size of the cipher, data arrays, hash table and binary tree by reference 
//checks the original file for new characters, generates code for new character, and updates data arrays, hash table, and binary tree
//returns the updated size of the cipher file
int checkExtraCode(std::string inputPath, int size, char chars[100], std::string codes[100], HashTable &table, BinaryTree &tree);

//takes in the path of the file thats not encoded and hashtable by refernece
//encodes the original file, and writes original file and encoded version to a new file called encoded_output.txt
void encode(std::string inputPath, const HashTable &table);

//takes in the path of the file thats encoded and tree by refernece
//decodes the encoded file, and writes original file and decoded version to a new file called decoded_output.txt
void decode(std::string inputPath, const BinaryTree &tree);

//boolean function, takes in the path of input file, if its encoded it returns true, otherwise, returns false
bool isEncoded(std::string inputPath);

//takes in data arrays and size of cipher file, and writes data arrays to cipher file 
void writeCipher(int size, char chars[100], std::string codes[100]);

#endif
