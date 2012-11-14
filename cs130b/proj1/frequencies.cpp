/* 
 * File:   main.cpp
 * Author: Taylor
 *
 * Created on April 11, 2011, 9:00 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int *table;
    char next;
    int got;
    table = new int[255];
    

    for(int i=0; i<256; i++)
        table[i] = 0;
    cin.get(next);
    while(cin.good())
    {
        got = int (next);
        table[got] = table[got] + 1;
        cin.get(next);
    }
    for(int i=0; i<256; i++)
    {
        if(table[i]!= 0)
            cout<< i<< "\t"  << table[i]<< "\n";
    }
    return 0;
}

