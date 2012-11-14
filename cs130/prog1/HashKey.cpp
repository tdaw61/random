/* 
 * File:   HashKey.cpp
 * Author: Taylor
 * 
 * Created on February 7, 2011, 8:00 PM
 *
 */
//#include "HashKey.h"

/*This class makes the HashKey and assigns the key, value, and boolean for if it has been deleted*/
class HashKey{
public:
        int key;
      int value;
      bool del;

    HashKey(int key, int value) {
        this->del = false;
            this->key = key;
            this->value = value;
      }
      int getKey() {
            return key;
      }
      int getValue() {
            return value;
      }
      void setHash(int value, int key) {
            this->value = value;
            this->key = key;
      }
      void setdeleted(int x)
      {
          if(x == 1)
              this->del = true;
          else
              this->del = false;
      }
      bool getdelete()
      {
          return del;
      }
      ~HashKey()
      {
          
      }
 };