#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:" << endl << endl;
  getline(cin, title);
  Playlist P;

  P.PrintMenu(title);//prints menu from Playlist.cpp
  
  return 0;
}
