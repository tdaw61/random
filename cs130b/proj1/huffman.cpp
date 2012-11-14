#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <iomanip>

using namespace std;

class node {
public:
    int ascii;
    int freq;
    string code;
    bool leaf;
    node* left;
    node* right;
    int freqa;
    int freqb;
    int printed;
    node( int x, int y)
    {
        ascii = x;
        freq = y;
	code = "";
	leaf = true;
	printed = 0;
    }
    node( node * a, node * b)
    {
	code = "";
	freqa = a->getFreq();
	freqb = b->getFreq();
        freq = freqa + freqb;
	left = a;
	right = b;
	leaf = false;
	printed = 0;
	
    }
    
    void setPrinted (int x) { printed = x;}
    void setCode(string x){ code = x; }
    string getCode() { return code;}
    node* getleft(){ return left;}
    node* getright(){ return right; }
    int getAscii() { return ascii; }
    int getFreq() { return freq; }
    bool getLeaf() {return leaf; }
    int getPrinted() {return printed; }
};
void build(node * n)
{
   //cout<< "i am here" ;
   if(n->getleft() != 0)
   {
	n->getleft()->setCode(n->getCode() + "0");
	build(n->getleft());
   }
   if(n->getright() != 0)
   {
	n->getright()->setCode(n->getCode() + "1");
	build(n->getright());
   }
}
int countNodes(node * n)
{
   if(n == NULL)
     return 0;
   else {
     int count = 1;
	count += countNodes(n->left);
	count += countNodes(n->right);
	return count;
    }
}
void print(node * n)
{

   if(n->getleft() != 0)
	print(n->getleft());
   if((n->getLeaf()) && (n->getPrinted() == 0)){
	cout<< n->getAscii() << "\t" << n->getCode() << endl;
	n->setPrinted(1);
    }
   if(n->getright() != 0)    
        print(n->getright());
  
}
class Comparison {
public:
    bool operator()(node* first, node* second)
    {
       if (first->getFreq() > second->getFreq()) return true;
       else return false;
    }
};

int main()
{

    int asc;
    int fre;
    node * a;
    node * b;
    priority_queue<node*, vector<node*>, Comparison> heap;
    while(cin.good())
    {
	cin>>asc;
	cin>>fre;
	if(cin.good())
		heap.push(new node(asc, fre));
    }
    while(heap.size() > 1)
    {
        a = heap.top();
	heap.pop();
	b = heap.top();
	heap.pop();
	heap.push(new node( a, b));
     }
    node * last = heap.top();
    build(last);
    print(last);
}
