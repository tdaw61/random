//#include "prog.h"
#include <iostream>

/*prog class is responsible for creating the heap in the Quash and implementing
 simple functions like insert, deletemin, delete, and show.*/
class prog{
public:

    int *Heap;
    int size;
    int count;

    prog()
    {
    //this->Heap = (int*)malloc(43*sizeof(int));
    this->Heap = new int[43];
    size = 43;
    count = -1;
    }
~prog()
{
    delete(Heap);
}
int Parent(int i)
{
    return((i-1)/2);
}
int Left(int i)
{
    return(2 * i + 1);
}
int Right(int i)
{
    return(2 * i + 2);
}
void MinHeapInsert(int key)
{
    for(int i = 0; i < 43; i++)
    {
        if (Heap[i] == key)
        {
            return;
        }
    }
            count++;
            //std::cout<< count << "\n";
            Heap[count] = key;
            PercUp(count);
}

void PercUp(int count)
{
      int parent;
      if (count != 0)
      {
            parent = Parent(count);
            if (this->Heap[parent] > this->Heap[count])
            {
                std::swap(this->Heap[parent], this->Heap[count]);
                PercUp(parent);
            }
      }
}
int DeleteMin()
{
    int min = this->Heap[0];
      if (count == -1)
            std:: cout << "Heap is empty \n";
      else
      {
            this->Heap[0] = this->Heap[count];
            this->Heap[count]= 0;
            count--;
           
            if (count > 0)
                  PercDown(0);
            std::cout<<"This is the deleted value: "<< min << "\n";
      }
    return min;
}
void deleter(int value)
{
    int i = 0;
    int parent;

    while(this->Heap[i] != value)
        i++;
   
    this->Heap[i] = this->Heap[count];
    //std::cout<<"\n"<<this->Heap[i]<<"\n";
    this->Heap[count] = NULL;
    count--;
    parent = Parent(i);
    if(this->Heap[i] == NULL){}

    else if(this->Heap[i] < parent)
        PercUp(i);
    else
        PercDown(i);

}
void PercDown(int index)
{
      int left, right, min;
      left = Left(index);
      
      right = Right(index);
      if (right >= count)
      {
            if (left >= count)
                  return;
            else
                  min = left;
      }
      else
      {
            if (this->Heap[left] <= this->Heap[right])
                  min = left;
            else
                  min = right;
      }
      if (this->Heap[count] > this->Heap[min])
      {
          std::swap(this->Heap[min], this->Heap[index]);
          PercDown(min);
      }
}
void Show()
{
    for(int i = 0; i < this->size; i++)
    {
        if(i > count)
            std::cout<<" E ";
        else
            std::cout << " " << Heap[i] << " ";
    }
}
};
