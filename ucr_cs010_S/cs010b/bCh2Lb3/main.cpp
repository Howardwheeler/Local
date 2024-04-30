#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   vector<int> vector;

   if(argc != 3)
   {
      cout << "File count is wrong" << endl;
      return 1;
   }

   // Assign to inputFile value of 2nd command line argument
   // Assign to outputFile value of 3rd command line argument
   inputFile = argv[1];
   outputFile = argv[2];

   // Create input stream and open input csv file.
   ifstream inFS;
   inFS.open(inputFile);

   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!inFS.is_open())
   {
      cout << "Error opening " << inputFile << endl;
      return 1;
   }

   // Read in integers from input file to vector.
   char c;
   //char previousC = ',';
   //string temp1;
   int num;
   //stringstream s;
   while (inFS >> num)
   {
      inFS >> c;
      vector.push_back(num);
      /*
      if(c != ',' && previousC == ',')
      {
         s << c;
         s >> num;
         vector.push_back(num);
         s.clear();
         previousC = c;
      }
      else if (c != ',' && previousC != ',')
      {
         string str1(1, previousC);
         string str2(1, c);
         temp1 = str1 + str2;
         s << temp1;
         s >> num;
         vector.pop_back();
         vector.push_back(num);
         s.clear();
      }
      else{
         previousC = ',';
      }*/
   }

   
   // Close input stream.
   inFS.close();

   // Get integer average of all values read in.
   int avg = 0;
   for (unsigned int i = 0; i < vector.size(); i++)
   {
      avg = avg + vector.at(i);
   }
   avg = avg / vector.size();

   // Convert each value within vector to be the difference between the original value and the average.
   for (unsigned int i = 0; i < vector.size(); i++)
   {
      vector.at(i) = vector.at(i) - avg;
   }

   // Create output stream and open/create output csv file.
   ofstream oFS;
   oFS.open(outputFile);

   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!oFS.is_open())
   {
      cout << "Error opening " << outputFile << endl;
      return 1;
   }

   // Write converted values into ouptut csv file, each integer separated by a comma.
   for (unsigned int i = 0; i < vector.size()-1; i++)
   {
      oFS << vector.at(i) << ",";
   }
   oFS << vector.at(vector.size()-1);
   
   // Close output stream.
   oFS.close();

   return 0;
}