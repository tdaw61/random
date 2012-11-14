#include <iostream>
#include <cstdlib>
#include <fstream>
#include <bitset>

using namespace std;


int main(int argc, char** argv)
{
	ifstream myfile("code");
	unsigned char building;
	int got;
	int ascii;
	int change;
	int dec;
	string leaving = "";
	unsigned char next;
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
		next = cin.get();
		//cout <<"next " <<  next << endl;
		//cout << "table entry " << table[int(next)] << endl;
		if(cin.good())
			text += table[int(next)] ;
	}
 	//cout<< text <<endl;
	int current = 0;
	unsigned char lit;
	int size = text.length();
	while(size-current>= 8)
	{
		for(int i =0; i <= 7; i++)
		{
			building = text.at(current + i); 	   
			entext += building;
		}
		//cout<<"this is entext " << entext << endl;
                dec = bitset<32>(entext).to_ulong();
                //dec = int (dec);
		//cout<< "this is the decimal of entext " << dec << endl;
        	lit = (unsigned char ) dec;
		//cout<< "this is lit " << lit << endl;
                leaving += lit;
		current += 8;
		entext = "";
	}
	cout<< leaving; 	
}
