#include <string>
#include <iostream>
#include <fstream>
#include "hashtable.h"
#include "binary_tree.h"
#include "manager.h"

int main()
{
    //creating objects of the hash table and binary tree class
    HashTable table;
    BinaryTree tree;

    //character array to hold the number of characters read from the cipher file, needed to keep them in order and add extra characters to them in order to overwrite cipher file 
    char chars[100];

    //string array to hold the number of codes read from cipher
    //the reason I made it a string array rather than integer is because if the code was something like 0001, it will treat it as 1, which will mess up the encoding/decoding
    std::string codes[100];

    //loading the cipher file in chars, codes, table, and tree, and returning the size of the cipher file
    //all the chars go to chars array
    //all the corresponding codes go to codes array
    int size = loadCipher("cipher.txt", chars, codes, table, tree);

    greet();
    std::string answer = getYesNoAnswer("Would you like to continue with this program? ");  
    
    while(answer == "yes")
    {
        std::string inputPath;
        std::cout << "Input the name of your input file: ";
        //std::getline(std::cin, inputPath);
        std::cin >> inputPath;

        //checking if the file that the user inputs exists
        std::ifstream testFile(inputPath);
        if(!testFile.is_open())
        {
            std::cout << "Error, input file not open!" << std::endl;
            continue;
        }
        testFile.close();

        if(isEncoded(inputPath))
        {
            std::cout<<"Decoding file " << inputPath << "..." << std::endl;
            decode(inputPath, tree);
            std::cout<<"Decoding has been successfully finished, go check the file decoded_output.txt!"<<std::endl;
        }
        else
        {
            std::cout<<"Encoding file " << inputPath << "..." << std::endl;

            //checking the txt file for extra codes, and inserting them into the data structures and storing the updated size of the cipher file, to write to it later(on line 63)
            size = checkExtraCode(inputPath, size, chars, codes, table, tree);

            encode(inputPath, table);
            std::cout<<"Encoding has been successfully finished, go check the file encoded_output.txt!"<<std::endl;
        }

        //overwriting the cipher file with possible extra characters and their corresponding codes
        writeCipher(size, chars, codes);

        //ask user if they want to try the program again
        answer = getYesNoAnswer("Would you like to continue with this program? "); 
        
    }

    std::cout<<"Have a great day, bye!"; 
    return 0;
}

