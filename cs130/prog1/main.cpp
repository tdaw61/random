/* 
 * File:   main.cpp
 * Author: Taylor
 *
 * Created on February 5, 2011, 6:06 PM
 *
 * main class is responsible for creating the Quash and then checking the
 * input stream for commands, then sending that command to the Quash.
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
//#include "HashTable.cpp"
//#include "prog.h"
#include "Quash.cpp"


using namespace std;

int main()
{
    Quash a;
    string which;
    string noob = "insert";
    string look = "lookup";
    string del  = "delete";
    string min =  "deleteMin";
    string printer = "print";
    string ender = "EOF";
    int value;

    while(which != "EOF")
    {
    cin >> which;
    if(which.compare(ender) == 0)
    {
        exit(1);
    }
    //if(stricmp("insert",which) == 0)
    else if (which.compare(noob) == 0)
    {
        cin >> value;
        a.insert(value);
    }
    //else if(stricmp("delete", which) == 0)
    else if(which.compare(del) == 0)
    {
        cin >> value;
        a.deleter(value);
    }
    //else if(stricmp("lookup", which) == 0)
    else if(which.compare(look) == 0)
    {
        cin >> value;
        a.lookup(value);
    }
    //else if(stricmp("print", which) == 0)
    else if(which.compare(printer) == 0)
    {
        a.print();
    }
    //else if(stricmp("deleteMin", which ) == 0)
    else if(which.compare(min) == 0)
    {
        a.deleteMin();
    }
    

    };
  return 0;
}


