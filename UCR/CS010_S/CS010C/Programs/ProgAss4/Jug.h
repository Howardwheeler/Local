#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::queue;
using std::ifstream; //zybooks uses these
using std::istreambuf_iterator; //zybooks uses these

struct Node{ //node struct
    int jugA, jugB, cost;
    string steps;
    Node() : jugA(0), jugB(0), cost(0) {} //makes the node with starting values
    Node(int jugA, int jugB, int cost, const string steps) : jugA(jugA), jugB(jugB), cost(cost), steps(steps) {} //makes a new node with updated jug values

    bool operator==(const Node& other) const { return jugA == other.jugA && jugB == other.jugB; } //comparison bool operator that compares a node's jug A and jug B values with a const Node&'s values
};

struct pathQueue{ //queue of nodes struct
    queue<Node> jugQueue;
};

class Jug{ //jug class
    const int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
    queue<pathQueue> storageQueue; //queue for storing jugQueues
    vector<Node> visitedStates; //notes down visited states
public:
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
    ~Jug();
    Jug(const Jug& cpy) = delete;
    Jug& operator=(const Jug& rhs) = delete;

    int solve(string& solution); //function in main call, solves path
    void shortestPath(); //helper function that finds shortest path to N, basically breadth first search
private:
    bool isValidInput() const; //helper checks if input is valid
    bool isVisited(const Node newNode) const; //helper checks if the state has been visited
    void possibleTasks(const Node stackTop, pathQueue newPath); //switch case for multiple possible jug steps
};