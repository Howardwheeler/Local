#pragma once

#include <iostream>
#include <string>
using namespace std;

class PlaylistNode {
public:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
  PlaylistNode();
  PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength);
  PlaylistNode(const PlaylistNode &cpy) = delete;
  ~PlaylistNode() {}
  PlaylistNode & operator=(const PlaylistNode &rhs) = delete;
  void InsertAfter(PlaylistNode* newNode);
  void SetNext(PlaylistNode* newNode);
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const;
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail; 
public:
  Playlist() : head(nullptr),tail(nullptr) {}
  ~Playlist(){ //destructor for PlaylistNode
    while (head != nullptr)
    {
        PlaylistNode* remove = head;
        head = head->nextNodePtr;
        delete remove;
    }
  }
  void PrintMenu(const string& title) const{
    char input;
    Playlist P;
    while(input != 'q') {
      cout << title << " PLAYLIST MENU" << endl;
      cout << "a - Add song" << endl;
      cout << "d - Remove song" << endl;
      cout << "c - Change position of song" << endl;
      cout << "s - Output songs by specific artist" << endl;
      cout << "t - Output total time of playlist (in seconds)" << endl;
      cout << "o - Output full playlist" << endl;
      cout << "q - Quit" << endl;
      cout << endl << "Choose an option:" << endl;

      cin >> input;
      if (input == 'a') {
        cout << endl;
        P.AddSong();
      } 
      else if (input == 'd') {
        cout << endl;
        P.RemoveSong();
      } 
      else if (input == 'c') {
        P.ChangePositionSong();
      } 
      else if (input == 's') {
        cout << endl;
        P.OutputSongsByArtist();
      } 
      else if (input == 't') {
        P.OutputTotalTime();
      } 
      else if (input == 'o') {
        P.OutputFullPlaylist(title);
      }
      else if (input == 'q')
      {
        break;
      }
    }
  }
  void AddSong(/*const string& id, const string& song, const string& artist, const int length*/);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist(const string& title) const;
  int nodeSize() const;
  int nodePosition(const string& id) const;
};
