#include <bitset>
#include <iostream>
#include <string>

using namespace std;

int main()
{
   string binNum;
   int dec;
   cout << "Enter binary number (max 32 digits): ";
   cin >> binNum;
   cout << "The number translated to decimal is " << bitset<32>(binNum).to_ulong()<< "\n" ;
   dec = bitset<8>(binNum).to_ulong();
   dec = int (dec);
   cout << "The number as an int is " << dec;
}
