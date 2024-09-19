#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

//declare hash table class, since it is a friend class of the node class
class HashTable;

//node class is used in the hashtable, stores the character and its code, and a pointer to the next node
class Node
{
private:

    Node(char ch, std::string code, Node* next)
    {
        this->ch = ch;
        this->code = code;
        this->next = next;
    }
   char ch;
   std::string code;
   Node* next;
//has access to the Node constructor, so can generate node object
friend class HashTable;
};

//The hash table data structure, that maps a character to its code, used for encoding operation
class HashTable
{
public:
   /**
      Constructs a hash table.
   */
  //default constructors of hash table creates an empty table of size 50
   HashTable();

   // //copy constructor is deleted, to prevent copy
   // HashTable(const HashTable&) = delete;

   // //assignment operator is deleted, to prevent copy
   // HashTable& operator=(const HashTable&) = delete;

   // Receives the char key and returns the code, by using the hash function
   // @param ch key
   // @return code, or an empty string if the key doesn't exist
  std::string get(char ch) const;

   // Receives char key and code pair, then inserts them into the hash table
   // @param ch key
   // @param code val
   void insert(char ch, const std::string& code);

    // Destructor for the hashtable, to prevent possible memory leaks
    ~HashTable();

private:
   Node* buckets[50]; //An array of pointers to nodes, more specifcially, head pointers

   // This function generates a hash code based on the key
   // @param ch key
   // @return hash code
   int hash_code(char ch) const;
};

#endif
