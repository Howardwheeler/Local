#include <iostream>
#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode(){ //setting every variable to "none" and 0 when declaring a Node with no input.
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
}

PlaylistNode::PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength){ //sets a node with new variables equal to the parameters
    this->uniqueID = uniqueID;
    this->songName = songName;
    this->artistName = artistName;
    this->songLength = songLength;
}

void PlaylistNode::InsertAfter(PlaylistNode* newNode){ //places new node after the selected node
    newNode->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = newNode;
}

void PlaylistNode::SetNext(PlaylistNode* newNode){ // sets new node after selected node
    this->nextNodePtr = newNode;
}

const void PlaylistNode::PrintPlaylistNode() const{ //prints out the information on the playlist node
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

void Playlist::AddSong(){ //sets new playlist variables and takes in input from user to add a new node, then does push_back.
    string newid;
    string newSong;
    string newArtist;
    int newLength;
    cout << "ADD SONG" << endl;
    cin.ignore();
    cout << "Enter song's unique ID:" << endl;
    getline(cin, newid);
    cout << "Enter song's name:" << endl;
    getline(cin, newSong);
    cout << "Enter artist's name:" << endl;
    getline(cin, newArtist);
    cout << "Enter song's length (in seconds):" << endl << endl;
    cin >> newLength;
    PlaylistNode* newNode = new PlaylistNode(newid, newSong, newArtist, newLength); //makes new node
    if(head == nullptr) //places it at the end of the list
    {
        head = newNode;
        tail = head;
    }
    else{
        tail->nextNodePtr = newNode;
        tail = newNode;
    }
  }

void Playlist::RemoveSong(){ //removes a node at the designated location,, cin the location of the node from input
    string removeID;
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin.ignore();
    getline(cin, removeID);
    PlaylistNode* checkNode = head;
    if(head == nullptr) // checks if playlist is empty
    {
        cout << "Playlist is empty." << endl;
        return;
    }
    if(head->GetID() == removeID) //a separate if statement for removing the song if its the first node
    {
        PlaylistNode* removal = head;
        head = head->nextNodePtr;
        cout << "\"" << head->GetSongName() << "\" removed." << endl;
        delete removal;
        return;
    }
    while (checkNode->nextNodePtr != nullptr) //loops through the playlist and deletes the song.
    {
      if(checkNode->nextNodePtr->GetID() == removeID)
      {
        PlaylistNode* removal = checkNode->nextNodePtr;
        checkNode->nextNodePtr = removal->nextNodePtr;
        cout << "\"" << removal->GetSongName() << "\" removed." << endl << endl;
        delete removal;
        return;
      }
      checkNode = checkNode->nextNodePtr;
    }
}

void Playlist::ChangePositionSong(){ //takes a node from a random posititon and then moves it to the spot of the new position
    int currentID;
    int newID;
    bool newID_is_head = false;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> currentID;
    cout << "Enter new position for song:" << endl; //takes in input from user
    cin >> newID;
    PlaylistNode* pre_selected = nullptr;
    PlaylistNode* selected = head;
    PlaylistNode* new_selection = head;
    if(currentID == newID)
    {
        return;
    }
    if(newID < 1)
    {
        newID = 1;
    }
    if(newID > nodeSize()) //cheks if newID is a valid ID
    {
        newID = nodeSize();
    }
    while(selected != nullptr && nodePosition(selected->GetID()) != currentID) //finds location for currentID and newID using pointers
    {
        pre_selected = selected;
        selected = selected->nextNodePtr;
    }
    if(1 == newID)//tests if newID is pointed to head, if so, it moves to the edge case if statement on line 148
    {
        newID_is_head = true;
    }
    else{
        while(new_selection != nullptr && nodePosition(new_selection->nextNodePtr->GetID()) != newID)
        {
            new_selection = new_selection->nextNodePtr;
        }
    }
    if(selected == head) //testing edge cases for if currentID and newID is head or tail,, then changes position
    {
        head = head->nextNodePtr;
    }
    else if(selected == tail)
    {
        tail = pre_selected;
        pre_selected->nextNodePtr = nullptr;
    }
    else{
        pre_selected->nextNodePtr = selected->nextNodePtr;
    }
    if(newID_is_head == true)
    {
        selected->nextNodePtr = head;
        head = selected;
    }
    else if(new_selection == tail)
    {
        selected->nextNodePtr = nullptr;
        tail->nextNodePtr = selected;
        tail = selected;
    }
    else{
        if(currentID < newID)
        {
            new_selection = new_selection->nextNodePtr;
        }
        selected->nextNodePtr = new_selection->nextNodePtr;
        new_selection->nextNodePtr = selected;
    }
    cout << "\"" << selected->GetSongName() << "\" moved to position " << newID << endl << endl;
}

void Playlist::OutputSongsByArtist() const{ //output playlist if they match artist name
    string artistName;
    PlaylistNode* currNode = head;
    int count = 1;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cin.ignore();
    cout << endl;
    getline(cin, artistName);
    while(currNode != nullptr)
    {
        if(currNode->GetArtistName() == artistName) //checks if artist name exists in the playlist, then prints node if it exists
        {
            cout << count << "." << endl;
            currNode->PrintPlaylistNode();
            cout << endl;
        }
        ++count;
        currNode = currNode->nextNodePtr;
    }
}

void Playlist::OutputTotalTime() const{ //calculates the total song length and adds them together
    int totalTime = 0;
    PlaylistNode* currNode = head;
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    while(currNode != nullptr) //iterates through the loop and adds the songlength to itself
    {
        totalTime += currNode->GetSongLength();
        currNode = currNode->nextNodePtr;
    }
    cout << "Total time: " << totalTime << " seconds" << endl << endl;
}

void Playlist::OutputFullPlaylist(const string& title) const{ //this outputs the whole playlist in order, numbered in each
    PlaylistNode* countNode = head;
    int count = 1;
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    if(countNode == nullptr) //checks if playlist is empty
    {
      cout << "Playlist is empty" << endl << endl;
      return;
    }
    while(countNode != nullptr) //iterates through the list and prints out info of each node in order
    {
        cout << count << "." << endl;
        countNode->PrintPlaylistNode();
        cout << endl;
        count++;
        countNode = countNode->nextNodePtr;
    }
}

int Playlist::nodeSize() const{ //helper function to count how many nodes exist in the list
    PlaylistNode* countNode = head;
    int count = 0;
    while(countNode != nullptr)
    {
        count++;
        countNode = countNode->nextNodePtr;
    }
    return count;
}

int Playlist::nodePosition(const string& id) const{ //helper function to count where the selected node is. aka which number is the selected node
    PlaylistNode* countNode = head;
    int position = 0;
    while(countNode != nullptr)
    {
        position++;
        if(countNode->GetID() == id)
        {
            break;
        }
        else{
            countNode = countNode->nextNodePtr;
        }
    }
    return position;
}