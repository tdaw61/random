#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class LCS {
    public:
        int** B;
        int** C;
        string x;
        string y;
        int m;
        int n;




int Length(string x, string y)
{
    this->y = y;
    this->x = x;
    m = x.length();
    n = y.length();
    int what;
    C = new int*[m+1];
    B = new int*[m+1];
    for(int i=0; i<=m; i++)
    {
        C[i]=new int[n+1];
        B[i]=new int[n+1];
    }
    for(int i = 1; i <= m; i++)//initialize outside of matrix
    {
        C [i][0] = 0;
        B [i][0] = 0;
    }
    for(int i = 1; i <= n; i++)
    {
        C [0][i] = 0;
        B [0][i] = 0;
    }
    
    for(int i = 1; i <= m; i++)//iterates through the rows
    {
        for(int j = 1; j <= n; j++)//iterates through the columns
        {
            
            if(x.at(i-1) == y.at(j-1))//checks to see if there is a match
            {
                C[i][j] = C[i-1][j-1] + 1;
                B[i][j] = 5;
            }
            else if(C[i-1][j] >= C[i][j-1])//checks for which matrix quadrant is higher
            {
                C[i][j] = C[i-1][j];
                B[i][j] = 6;
            }
            else
            {
                C[i][j] = C[i][j-1];
                B[i][j] = 7;
            }
        }
    }
    cout<< "Length: " << C[m][n]<< "   ";
    PrintLCS( m, n);
    return 0;
}
/*PrintLCS is a simple function to print out the LCS*/
int PrintLCS(int m, int n)
{
    if((m==0) || (n==0))
    {
        return 0;
    }
    if (B[m][n] == 5)
    {
      
        PrintLCS( m-1, n-1);
        cout<<x.at(m-1);
    }
    else if( B[m][n] == 6)
        PrintLCS( m-1, n);
    else
        PrintLCS( m,n-1);
 }
int getm(){return m;}
int getn(){return n;}
};




int main(int argc, char** argv) {
    string x;
    string y;
    int a;
    int b;
    int d;
    x = argv[1];
    y = argv[2];
    LCS Taylor;
    Taylor.Length(x,y);
    a = Taylor.getm();
    b = Taylor.getn();
    //LCSall what;
    //what.Length(x,y);
    cout<<"\n";
    return 0;
}


