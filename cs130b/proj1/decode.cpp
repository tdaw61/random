#include <iostream>
#include <cstdlib>
#include <fstream>
#include <bitset>

using namespace std;

string binary( char given)
{
unsigned char bit = 0x80;
unsigned char bitbyte;
string answer;

for ( int i=0; i<8; i++)
 {
	bitbyte = given & bit ;
	
	if (bitbyte == 0 )
	{
		answer += "0";
	}
	else
	{
		answer+= "1";
	}
	
	bit = bit >> 1 ;
 }
	return answer;
}
int main()
{
        ifstream myfile("code");
        char building;
        int got;
        int ascii;
        int change;
        int dec;
        char lit;
	string finally = "";
        char next;
        string code;
        string text = "";
        string entext = "";
        string table [256];
	
        for(int i = 0; i < 256; i++)
        {
                table[i] = "";
        }

        if (myfile.is_open())
        {

                while(myfile.good())
                {
                        myfile>> ascii;
                        myfile>> code;
                        table[ascii] = code;
                }
         myfile.close();
        }
        else
                cout<< "error in file \n";
        while(cin.good())
        {	
                cin.get(next);
		if(cin.good()){
                	text += binary(next);
		}
        }
        int current = 0;
	int size = text.length();
	char yup;
	string temp = "";
	while(size - current > 0)
	{
		temp += text.at(current);
		for(int i = 0;i<256;i++)
		{
			if(temp == table[i])
			{
				yup = i;
				finally += yup;
				temp = "";
			}
		}
		current++;
	}
	cout<< finally;
}
