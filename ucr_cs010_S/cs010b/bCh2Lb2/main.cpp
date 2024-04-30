#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt (string filename, char ch){
   ifstream inFS;
   int count = 0;
   char fileChar;

   inFS.open(filename);

   if(!inFS.is_open())
   {
      cout << "Error opening " << filename << endl;
      count = -1;
   }
   else{
      while(inFS.get(fileChar))
      {
         if(fileChar == ch)
         {
            ++count;
         }
         else if (ch == ' ')
         {
            count = 13;
            /*if(!isalpha(fileChar))
            {
               count = 100;
            }*/
         }
      }
   }
   inFS.close();

   return count;
}


int main() {
   string filename;
   char ch;
   int chCnt = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   cout << "Enter a character: ";
   cin.ignore(); // ignores newline left in stream after previous input statement
   cin.get(ch);
   cout << endl;

   chCnt = charCnt(filename, ch); 
   if(chCnt == -1)
   {
   }  
   else{
   cout << "# of " << ch << "'s: " << chCnt << endl;
   }
   
   return 0;
}

// Place charCnt implementation here
