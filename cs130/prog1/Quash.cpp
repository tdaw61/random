#include <cstdlib>
#include <iostream>
#include "HashTable.cpp"
#include "prog.cpp"

/*This class will make instances of a heap and a hash table and then will go about the
 functions that are necessary of the Quash*/
class Quash
{
public:
    prog MinHeap;
    HashTable work;

    void insert(int value)
    {
            MinHeap.MinHeapInsert(value);
            work.insert(value);
    }
    void lookup(int value)
    {
        if(work.lookup(value))
        {
            std::cout<<"item found. \n";
        }
        else
        {
            std::cout<<"item not found. \n";
        }
    }
    void deleteMin()
    {
        int x = MinHeap.DeleteMin();
        work.del(x);
        //std::cout<<"this is the minDelete value: "<<x << "\n";
    }
    void deleter(int i)
    {
        int x;
        x = work.del(i);
        if(x == i)
        {
            MinHeap.deleter(x);
            std::cout<<"item successfully deleted \n";
        }
            
    }
    void print()
    {
        MinHeap.Show();
        std::cout<<" \n Now for the hash table \n";
        work.print();
    }
};
