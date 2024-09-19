#include "hashtable.h"

HashTable::HashTable()
{
    for(int i = 0; i < 50; i++)
    {
        buckets[i] = nullptr;
    }
}

//character is give, want to get code for it; if key (i.e. ch) not found, return an empty string
std::string HashTable::get(char ch) const
{
    std::string code; // code is ""
    //h is the index that we want to insert, generating hash code based on character
    int h = hash_code(ch);

    //getting the array index of the specifc bucket
    h = h % 50;

    //check if neg, make it pos
    if (h < 0)
    {
        h = -h;
    }

    Node* temp = buckets[h];

    while(temp != nullptr)
    {
        //once found out that key of temp (i.e. temp->ch) equals input key (i.e. ch), return value of temp (i.e. temp->code)
        if(temp->ch == ch)
        {
            code = temp->code;

            break;
        }
        //if not found, increment temp to point to next node
        temp = temp->next;
    }

    return code;
}

//seperate chaining used when inserting and searching
void HashTable::insert(char ch, const std::string& code)
{
    //h is the index that we want to insert, generating hash code based on character
    int h = hash_code(ch);

    //getting the array index of the specifc bucket
    h = h % 50;

    //check if neg, make it pos (just incase the hash code fucntion returns a negative number)
    if (h < 0)
    {
        h = -h;
    }

    //creates a new node and inserts it at the beginning on the linked list at buckets[h]
    //buckets[h] points to a head of a linked list

    //a temp node is created, with the data of ch, code, and the next of the new node is equal buckets of h
    Node* temp = new Node(ch, code, buckets[h]);

    //buckets[h] refers to second node, we want it to refer to 1st node, which is temp
    buckets[h] = temp;

}

// Destructor to deallocate hash table, or delete linked lists
HashTable::~HashTable()
{
    for (int i = 0; i < 50; i++)
    {
        //each bucket of i is a pointer to a head of a linked list
        Node* temp = buckets[i];
        
        //erasing head of linked list again and again
        while(buckets[i] != nullptr)
        {
            buckets[i] = buckets[i]->next;
            delete temp;
            temp = buckets[i];
        }
    }
}

//the key in this hash table is a character
//hashcode function applied to the key generates a uniformly distributed number
int HashTable::hash_code(char ch) const
{
    // Knuth's multiplicative method
    //generate a hash code in the hash table, produce an index for insertion and search 
    int h = ch * 2654435761;
    //% (2 << 16);

    return h;
}
