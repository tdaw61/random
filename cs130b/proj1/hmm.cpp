#include <fstream>
#include <iostream>
#include <cstdlib>


using namespace std;


string binary( char given )
{
  unsigned char bit = 0x80 ;
  unsigned char bitbyte ;
  string answer = "";
  for ( int i = 0 ;i < 8 ;i++ )
  {
        bitbyte = given & bit;

        if ( bitbyte == 0 )
        {
                answer += "0";
        }
        else
        {
                answer += "1";
        }

        bit = bit >> 1 ;
  }
        return answer;
}

int main()
{
	char what = 'a';
	string binarys;
	binarys = binary(what);
	cout<< binarys;
	return 0;
}
