#include "HashKey.cpp"
#include <cstdlib>
#include <iostream>

/*HashTable class is responsible for building a table of HashKeys and then
 implementing basic functions of a hash table such as insert, lookup, delete, and print.*/
const int TABLE_SIZE = 43;
class HashTable {

private:
      HashKey **table;

public:
      HashTable() {
            table = new HashKey*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }
      bool lookup(int key) {
            int hash = std::abs(key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getValue() != key  && table[hash]->getdelete())
                hash++;
            if (table[hash] == NULL)
            {
                //std::cout<<"item not found \n";
                return false;
            }     
            else
            {
                //std::cout<<"item found \n";
                return true;
            }
      }
      void insert(int key) {
          

          int hash;
          
          hash = std::abs((key % TABLE_SIZE));
          
          while(table[hash] != NULL && table[hash]->getdelete() == false )
          {
              if(table[hash]->getValue() == key)
              {
                  std::cout<<"item already present \n";
                  return;
              }
              else
                hash = std::abs((hash + 1));
          }
          table[hash]= new HashKey(hash, key);
          std::cout<<"item successfully added. \n";
      }

      int del(int key)
      {
          int hash;
          hash = std::abs((key % TABLE_SIZE));
          while (table[hash] != NULL && table[hash]->getValue() != key && table[hash]->getdelete())
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] == NULL)
            {
                  //std::cout<< "item not found \n";
                  return -1;
            }
            else
                table[hash]->setdeleted(1);
          return table[hash]->getValue();



      }
     void print()
     {
         for(int i = 0; i < TABLE_SIZE; i++)
         {
             if(table[i] == NULL)
                 std::cout<< " E ";
             else if( table[i]->getdelete())
                 std::cout<<" D ";
             else
                 std::cout<< " value: " <<table[i]->getValue() << "  key: " << table[i]->getKey();
         }
             
      }
      ~HashTable() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};
