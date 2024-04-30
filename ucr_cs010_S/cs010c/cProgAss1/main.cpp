#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node { 
    string payload; //constructs a structure of node with data as "payload" and a next pointer
    Node* next;
};

Node* newNode(string payload) { //constructor function makes newnode with payload as data
   Node* newNode = new Node;
   newNode->payload = payload;
   newNode->next = nullptr; 
   return newNode; //returns the newnode into the heap
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr; //loads new pointer head and tail that is pointing to nullptr, therefore making the list empty
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) { //takes in input from vector "names" n amount of times to load in player names
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); // initialize head first if list is empty
            prev = head;
        } else {        //if list is not empty, it adds new players to the list to the end of the list using prev node (it works as a tail node)
            prev->next = newNode(name);
            prev = prev->next;
        }
    }

    if (prev != nullptr) { //makes prev ... aka tail... point back to head so that it makes the list come back to itself
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start; //points new node curr to head aka start
    while (curr != nullptr) {
        cout << curr->payload << endl; //iterates through the list from head until curr's next pointer equals head, which basically means it iterated through the whole list
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
         prev = curr; //the while loop loops until there is 1 node in the list
         curr = curr->next; //the for loop loops until it finds the kth node and sets curr to that node and prev to the node before that
        }

        prev->next = curr->next;// delete kth node
        delete curr;
        curr = prev->next; //sets curr's node position to the next player in line
    }

    return curr; //return last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; /*max*/ // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k; //takes in input for number of names and number of skips initially
    for(int i = 1; i <= n; i++)
    {
       cin >> name;
       if(name == ".") {break;} //iterates until the user types "."
       names.push_back(name);
    } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl; //prinnts out final player that is alive
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

