#include "manager.h"
#include <fstream>
#include <string>
#include <iostream>

void greet()
{
    std::cout << "Hello, this program will take in a text file and encodes the plain text or decodes the encoded text, based on the cipher file." << std::endl;
}

//gets the user input if they want to continue, with input validation
std::string getYesNoAnswer(std::string message)
{

    std::string answer;    
    std::cout << message;
    //std::getline(std::cin, answer);
    std::cin >> answer;

    //input validation
    while(std::cin.fail() || (answer != "yes" && answer !="no"))
    {
        std:: cin.clear();
        std:: cin.ignore(10000,'\n');
        std:: cout<<"Please enter again: yes or no: ";
        std:: cin>>answer;
    }
    return answer;
}


int loadCipher(std::string path, char chars[100], std::string codes[100], HashTable &table, BinaryTree &tree)
{
    //path, the name of the file, is associated with an ifstream 
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Error, file not open!" << std::endl;
        return -1;
    }

    std::string input;
    int size = 0;

    //while we get the input (characters and codes) from the file
    while(file >> input) //reads characters 
    {
        char ch = input[0]; //set the ch to the first index of the input
        file >> input; //reads code
        std::string code = input; //sets the code to the input
        chars[size] = ch; //sets the characetr array indexes to the charactes read in
        codes[size] = code; //sets the codes array indexes to the codes read in
        //inserts the characters and codes to the table and tree
        table.insert(ch, code); 
        tree.insert(ch, code);
        size++;
    }

    file.close();
    return size;
}

//if theres extra input in text file, and then inserts them in tree, table, and chars and codes arrays
int checkExtraCode(std::string inputPath, int size, char chars[100], std::string codes[100], HashTable &table, BinaryTree &tree)
{
    std::ifstream file(inputPath);
    //if the text file is not found
    if(!file.is_open())
    {
        std::cout << "Error, file not open!" << std::endl;
        //if we return -1, the size of the cipher will be -1, so it'll get erased, so we return the size, and the cipher remains unchanged
        return size;
    }

    std::string input;


    while(file >> input)
    {
        for(int i = 0; i < input.length(); i++)
        {
            char ch = input[i];
            //if character ch isnt found in the table, means its not in cipher file, since if it was in cipher, that means it would be in the table
            if(table.get(ch).empty())
            {
                //generating a new code for it
                bool applied = false;
                //applied is used to show if the code is generated
                //code stores the last code in cipher
                std::string code = codes[size - 1]; 
                //iterate starting from right hand side, and 1 to the code
                for(int j = code.length() - 1; j >= 0; j--)
                {
                    //if index j is 0, change it to one, and the code is ready
                    if(code[j] == '0')
                    {
                        //if index j is one, the code ..
                        code[j] = '1';
                        applied = true;
                        break;
                    }
                    else
                    {
                        code[j] = '0';
                    }
                }

                if(!applied)
                {
                    code = "1" + code;
                }

                //size is the last character index
                chars[size] = ch;
                codes[size] = code;
                table.insert(ch, code);
                tree.insert(ch, code);

                size++;
            }
        }
    }

    file.close();
    return size;
}

void encode(std::string inputPath, const HashTable &table)
{
    std::string outputPath = "encoded_output.txt";

    std::ifstream inFile(inputPath);
    if(!inFile.is_open())
    {
        std::cout << "Error, input file not open!" << std::endl;
        return;
    }

    std::ofstream outFile(outputPath);
    if(!outFile.is_open())
    {
        std::cout << "Error, output file not open!" << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while(std::getline(inFile, line))
    {
        outFile << line << std::endl;
    }
    outFile << std::endl;

    inFile.close();
    inFile.open(inputPath);

    while(std::getline(inFile, line))
    {
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] != ' ')
            {
                std::string code = table.get(line[i]);
                outFile << code;
            }
            outFile << ' ';
        }
        outFile << std::endl;
    }
    outFile.close();
    inFile.close();

}

void decode(std::string inputPath, const BinaryTree &tree)
{
    std::string outputPath = "decoded_output.txt";

    std::ifstream inFile(inputPath);
    if(!inFile.is_open())
    {
        std::cout << "Error, input file not open!" << std::endl;
        return;
    }

    std::ofstream outFile(outputPath);
    if(!outFile.is_open())
    {
        std::cout << "Error, output file not open!" << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while(std::getline(inFile, line))
    {
        outFile << line << std::endl;
    }
    outFile << std::endl;

    inFile.close();
    inFile.open(inputPath);

    std::string code;
    while(inFile >> code)
    {
        char ch = tree.get(code);
        outFile << ch;

        char next = inFile.peek();
        if(next == '\n')
        {
            outFile << '\n';
        }
        if(next != EOF)
        {
            inFile.get(); // Gets rid of \n or whitespace
            if(inFile.peek() == ' ')
            {
                inFile.get();
                outFile << ' ';
            }
        }
    }

    outFile.close();
    inFile.close();
}

bool isEncoded(std::string inputPath)
{
    std::ifstream inFile(inputPath);
    if(!inFile.is_open())
    {
        std::cout << "Error, input file not open!" << std::endl;
        //return false;
        //if file is not found, assume it is the path of the encoded file, because if it is false, it executes 2 functions instead of 1
        return true;
    }

    while(inFile.peek() != EOF)
    {
        char ch = inFile.get();
        //valid characters of the encoded file, so this means if its not encoded, we return false
        if(ch != '0' && ch != '1' && ch != ' ' && ch != '\n'  && ch != '\r' && ch != EOF)
        {
            return false;
        }
    }

    return true;
}

void writeCipher(int size, char chars[100], std::string codes[100])
{
    std::ofstream file("cipher.txt");
    for(int i = 0; i < size; i++)
    {
        file << chars[i] << ' ' << codes[i] << std::endl;
    }
    file.close();
}
