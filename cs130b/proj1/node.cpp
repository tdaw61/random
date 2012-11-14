class node{
 
 public:
  
   int freq;
   int ascii;
   int code;
   node()
   {
       freq = 0;
       ascii = 0;
       code = 0;
   }
   node(int x, int y)
   {
       freq = x;
       ascii = y;
   }

   void setCode(int x)
   {
      code = x;
   }
}
