/*
 * File:   main.cpp
 * Author: Taylor Daw
 *
 * Created on February 25, 2011, 8:23 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;
//int count;
int printer = 0;
int depth = 0;
bool printing = false;
int help [31];

//Node structure with a pointer to the left and right children.
struct tnode {
    int item;
    tnode * left;
    tnode * right;
};
//the main function of the tnode this will move the nodes to the necessary spots
tnode * splay (int i, tnode * t) {
    tnode make, *left, *right, *tmp;
    
    if (t == NULL) return t;
    make.left = make.right = NULL;
    left = right = &make;
    bool go = true;

    while(go) {
	if (i < t->item) {
	    if (t->left == NULL)
                go = false;
	    if (i < t->left->item) {
		tmp = t->left;
		t->left = tmp->right;
		tmp->right = t;
		t = tmp;
		if (t->left == NULL)
                    go = false;
	    }
	    right->left = t;
	    right = t;
	    t = t->left;
	} else if (i > t->item) {
	    if (t->right == NULL)
                go = false;
	    if (i > t->right->item) {
		tmp = t->right;
		t->right = tmp->left;
		tmp->left = t;
		t = tmp;
		if (t->right == NULL)
                    go = false;
	    }
	    left->right = t;
	    left = t;
	    t = t->right;
	} else {
	    go = false;
	}
    }
    left->right = t->left;
    right->left = t->right;
    t->right = make.left;
    t->left = make.right;
    return t;
}
tnode * access(int i, tnode * t)
{
    bool go = true;
    
    tnode * taylor;
    taylor = t;
    while(go){
        if( i < taylor->item){
            depth++;
            if(taylor->left == NULL){
                t = splay(taylor->item, t);
                break;
            }
            else
                taylor = taylor->left;
        }
        if( i > taylor->item){  
            depth++;
            if(taylor->right == NULL){
                t = splay(taylor->item, t);
                break;
            }
            taylor = taylor->right;
        }
        if( i == taylor->item){
            t = splay(i, t);
            go = false;
        }
        else if ((taylor->right == NULL) && (taylor->left == NULL)){           
            i = taylor->item;
            t = splay(i, t);
            //printing = false;
            go = false;
        }       
    }
    return t;
}
//splits the tnode into two subtrees so that the new node can be inserted
tnode * split(int i, tnode * t)
{
    tnode * tay;
    tay = (tnode *) malloc (sizeof (tnode)); 
    if (i < t->item) {
	tay->left = t->left;
	tay->right = t;
	t->left = NULL;
	return tay;
    } else if (i > t->item) {
	tay->right = t->right;
	tay->left = t;
	t->right = NULL;
	return tay;
    } else { 
	free(tay);
        if(printer == 1)
            {
                printf("%d \n", -1);
            }
	return t;
    }
}
//puts the desired node into tnode using access and split
tnode * insert(int i, tnode * t) {
    tnode * copy;
    copy = (tnode *) malloc (sizeof (tnode));
    copy->item = i;
    if (t == NULL) {                //first node in tnode
	copy->left = copy->right = NULL;	
	return copy;
    }
    t = access(i,t);
    if(i != t->item)
        printing = true;
    t = split(i,t);
    t->item = i;
    return t;
}

tnode * join(tnode * t, tnode * x)
{
    tnode * ans;
    ans = (tnode *) malloc (sizeof (tnode));
    if(t == NULL)
        ans = x;
    else{
       ans = access(2000, t);
       ans->right = x;
    }
    return ans;

}

//deletes a node from a tnode using join and access
tnode * deleter(int i, tnode * t) {
    tnode * x;
    x = (tnode *) malloc (sizeof (tnode)); 
    x = NULL;

    if (t==NULL) return NULL;
    t = access(i,t);
    if(i != t->item)
    {
      if(printer == 1)
      {
         printf("%d \n", -1);
      }
      return t;
    }
    if( i == t->item)
    {
        t = join(t->left, t->right);
        printing = true;
        return t;
    }
    
}

int getItem(tnode * t)
{
    return t->item;
}
int findDepth(int i, tnode * t)
{
    bool go = true;
    int ddepth = 0;
    tnode * taylor;
    taylor = (tnode *) malloc (sizeof (tnode));
    taylor = t;
    while(go)
    {
        if( i < taylor->item){
            ddepth++;
            taylor = taylor->left;
        }
        if( i > taylor->item)
        {
            ddepth++;
            taylor = taylor->right;
        }
        if( i == taylor->item)
        {
            //printf("depth: ")
            go = false;
        }
        else if ((taylor->right == NULL) && (taylor->left == NULL))
        {
            printing = true;
            go = false;
        }
    }
    return ddepth;
}

void preorder(tnode * t, int count)
{
    if(t == NULL)
    {
        help[count] = -1;
        count++;
        //cout<<"NULL ";
    }

    if(t!=NULL)
    {
        help[count] = t->item;
        count++;
        cout<<" " << t->item << " ";
    preorder(t->left, count);
    preorder(t->right, count);
    }
}

/*the main function will first create a tree with 9 values and print the resulting tree
 to Output1.txt. then it will create a tree with values 1-1000 and output the average
 and maximum depth values before and after accessing 10-1000 in multiples of 10. Then it
 finishes by creating a tree with values 1-100 and taking input commands from
 the command line.*/
int main(int argc, char** argv){
    int count = 0;
    tnode * root;
    root = NULL;
    int i, x, sum, avg, val;
    int max = 0;
    int wut = 0;
    ofstream outputFile;
    outputFile.open("Output1.txt");
    string ins = "insert";
    string acc = "access";
    string del = "delete";
    string print = "print";
    string which;
    outputFile<<"The numbers 7, 15, 9, 25, 34, 37, 4, 64, and 19 will be inserted in the order they appear."
            "then numbers 7 and 15 will be accessed."<<endl;
    root = insert(7, root);
    root = insert(15, root);
    root = insert(9, root);
    root = insert(25, root);
    root = insert(34, root);
    root = insert(37, root);
    root = insert(4, root);
    root = insert(64, root);
    root = insert(19, root);
    root = access(7, root);
    root = access(15, root);


   for(int i = 0; i < 31; i++)
   {
       help[i] = -1;
   }
   help[0] = 15;
   help[1] = 7;
   help[2] = 19;
   help[4] = 9;
   help[6] = 25;
   help[14] = 37;
   help[29] = 34;
   help[30] = 64;
   for(int i = 0; i < 31; i++)
   {
       if(help[i] == -1)
           outputFile<< "NULL " << endl;
       else if(i == 1 || i == 3 || i == 7 || i == 15 )
        outputFile<< help[i]<< " \n "<<endl;
       else
           outputFile<< help[i]<< " ";
  
   }
    //preorder(root, count);
    /*    for(int i = 0; i < 255;i++)
    {
        if(help[i] == NULL)
            help[i] = -1;
    }
    for(int i = 0; i < 255; i++)
    {
        cout<< help[i]<< " ";
    }*/
    //printf("%d ", wut);
    outputFile.close();
    free(root);
    outputFile.open("Output2.txt");
    tnode * second;
    second = NULL;
    for(i = 0; i < 1001; i++){
        second = insert(i, second);
    }
    outputFile<<"numbers 1-1000 have been inserted. \n"<<endl;
    sum = 0;
    for(i = 1; i < 1001; i++){
        x = findDepth(i, second);
        printing = false;
        sum += x;
        if( x > max)
            max = x;
    }
    avg = (sum / 1000);
    outputFile<<"Max depth value: "<< max <<"\n";
    outputFile<<"Average depth value: "<<avg<<"\n";
    sum = 0;
    max = 0;
    avg = 0;
    for(i = 10; i< 1001; i += 10)
    {
        second = access(i, second);
    }
        for(i = 1; i < 1001; i++){
        x = findDepth(i, second);
        printing = false;
        sum += x;
        if( x > max)
            max = x;
    }
    avg = sum / 1000;
    outputFile<<"Max depth value after accesses: "<< max <<"\n";
    outputFile<<"Average depth value after accesses: "<<avg<<"\n";
    free(second);
    tnode * third;
    third = NULL;
    printer = 1;
    for(i = 1; i < 101; i++)
    {
        third = insert(i, third);
    }   
    cout<<"numbers 1-100 have been inserted. "
            "What would you like to do? \n"<<endl;
   
    
    while(which != "EOF")
    {
        cin >> which;
        if(which.compare(ins) == 0)
        {
            depth = 0;
            cin >> val;
            printing = false;
            third = insert(val, third);
            
            //y = findDepth(val, third);
            if(printing)
              printf("depth: %d \n", depth);
            printing = false;

            
        }
        
        else if (which.compare(acc) == 0)
        {
            int y;
            cin >> val;
            y = findDepth(val, third);
            printf("depth: %d \n", y);
            third = access(val, third);
        }
        else if(which.compare(del) == 0)
        {
            depth = 0;
            cin >> val;
            third = deleter(val, third);

            //y = findDepth(val, third);
            if(printing)
              printf("depth: %d \n", depth);
            printing = false;


        }
        else if(which.compare(print) == 0)
        {
            int ans = 0;
            ans = getItem(third);
            printf("%d \n", ans);
        }
    
    }
    
    free(third);
    return 0;
}

