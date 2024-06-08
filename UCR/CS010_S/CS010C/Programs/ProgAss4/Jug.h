#pragma once

#include <iostream>
#include <string>
#include <queue>

using std::string;

struct Node {
    int jugA, jugB, cost;
    std::string steps;
    Node(int a, int b, int c, const std::string& s) : jugA(a), jugB(b), cost(c), steps(s) {}
};

class Jug {
    int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
    bool* visited;
public:
    // Constructor to initialize the Jug object
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);

    // Destructor
    ~Jug();

    // Method to solve the jug problem
    // Returns:
    // -1 if invalid inputs
    //  0 if inputs are valid but a solution does not exist
    //  1 if solution is found and stores solution steps in solution string
    int solve(string& solution);

private:

    // Helper function to check if inputs are valid
    bool isValidInput();

    // Helper function to perform BFS and find the cheapest solution
    int BFS(string& solution);

    // Helper function to generate next states
    void generateNextStates(Node& node, std::queue<Node>& q, const std::string& currSteps);
};