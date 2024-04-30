#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function

using namespace std;

// Place fileSum prototype (declaration) here
int fileSum (string filename){
   ifstream lab2part1aFS;
   int sum = 0;
   int num1;

   lab2part1aFS.open(filename);
   if(!lab2part1aFS.is_open())
   {
      cout << "Error opening " << filename << endl;
      return 0;
   }
   else{
      
      while(lab2part1aFS >> num1)
      {
         sum = sum + num1;
      }

      lab2part1aFS.close();
   
      return sum;
   }

   

}

int main() {

   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);

   if(sum == 0){

   }
   else{
      cout << "Sum: " << sum << endl;
   }
   
   return 0;
}

// Place fileSum implementation here