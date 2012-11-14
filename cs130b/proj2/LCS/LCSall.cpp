#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class LCSall {
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
    C = new int*[m+1];
    B = new int*[m+1];
    vector<vector<int> > T[m+1][n+1];
   
    for(int i=0; i<=m; i++)
    {
        C[i]=new int[n+1];
        B[i]=new int[n+1];
    }
    for(int i = 1; i <= m; i++)//creating outside rows of matrix
    {
        C [i][0] = 0;
        B [i][0] = 0;
        //T [i][0].at(i).push_back(0);
    }
    for(int i = 1; i <= n; i++)
    {
        C [0][i] = 0;
        B [0][i] = 0;
        //T [i][0].at(i).push_back(0);
    }

    for(int i = 1; i <= m; i++)//iterates through rows
    {
        for(int j = 1; j <= n; j++)//iterates through columns
        {

            if(x.at(i-1) == y.at(j-1))//checks to see if there is a match
            {
		
		if(T[i-1][j-1].empty())//initializes vector if it is first quadrant
		{
			T[i][j].push_back( vector<int>() );
			T[i][j].front().push_back(i);
			T[i][j].front().push_back(j);
		}
		else
		{
			for(int k = 0; k < T[i-1][j-1].size(); k++)
			{
				T[i][j].push_back(T[i-1][j-1].at(k));
			}
			for(int k = 0; k < T[i][j].size(); k++)
			{
				T[i][j].at(k).push_back(i);
				T[i][j].at(k).push_back(j);
			}
		}	
                C[i][j] = C[i-1][j-1] + 1;
            }

            else if(C[i-1][j] > C[i][j-1])// if above is greater then the left
            {
                C[i][j] = C[i-1][j];
		for(int k = 0; k < T[i-1][j].size(); k++)
		{
			T[i][j].push_back(T[i-1][j].at(k));
		}
            }
            else if(C[i-1][j] < C[i][j-1])
            {
                C[i][j] = C[i][j-1];
		for(int k = 0; k < T[i][j-1].size(); k++)
		{
			T[i][j].push_back(T[i][j-1].at(k));
		}
            }
            else
            {
                C[i][j] = C[i][j-1];               
		for(int k = 0; k < T[i][j-1].size(); k++)
		{
			T[i][j].push_back(T[i][j-1].at(k));
		}
		for(int k = 0; k < T[i-1][j].size(); k++)
		{
			T[i][j].push_back(T[i-1][j].at(k));
		}
            }
        }
    }
    string first;
    string second;
    vector <string> ans;
    char num[21];
	for(int i = 0; i < T[m][n].size(); i++)//this loop takes care of making strings to print out
	{
		first =  "(<";
		int printer = 0;
		for(int j = 0; j < T[m][n].at(i).size(); j++)
		{
                    
                    sprintf(num, "%d", T[m][n].at(i).at(j) );
                    first+= num;

			
			if(printer == 0)
			{
				first+=",";
				printer++;
			}
			else if( (printer == 1) && ( j != T[m][n].at(i).size() - 1))
			{
				first+=">, <";
				printer = 0;
			}
			
		}
		first+= ">)";
                ans.push_back(first);
	}
    for(int i = 0; i < ans.size(); i++)//this loop checks for duplicates
    {
        for(int j = 0; j < ans.size(); j++)
        {
            if(i != j)
            {
                if(ans.at(j) == ans.at(i))
                    ans.erase(ans.begin()+ i);
            }
        }
    }
    for(int i = 0; i < ans.size(); i++)//this loop prints out the remaining answers.
        cout<< ans.at(i)<<"\n";
    
    
    return 0;
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

    //LCS Taylor;
    //Taylor.Length(x,y);
    //a = Taylor.getm();
    //b = Taylor.getn();
    LCSall what;
    what.Length(x,y);

    return 0;
}



