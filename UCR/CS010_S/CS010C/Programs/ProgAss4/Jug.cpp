#include "Jug.h"

using std::queue;
using std::min;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {
    visited = new bool[(Cb + 1) * (N + 1)];
}

Jug::~Jug() {
    delete[] visited;
}

// Method to solve the jug problem
int Jug::solve(string& solution) {
    // Check if inputs are valid
    if (!isValidInput()) return -1; // Invalid inputs
    
    // Initialize visited array
    for (int i = 0; i <= Cb; ++i) {
        for (int j = 0; j <= N; ++j) {
            visited[i * (N + 1) + j] = false;
        }
    }

    // Solve using BFS
    int result = BFS(solution);
    if (result == 1) {
        return 1; // Solution found
    } else {
        return 0; // No solution found
    }
}

// Helper function to check if inputs are valid
bool Jug::isValidInput() {
    return (Ca > 0 && Cb >= Ca && N <= Cb && N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0);
}

int Jug::BFS(string& solution) {
    queue<Node> q;
    q.push(Node(0, 0, 0, "")); 
    while (!q.empty()) {
        Node curr = q.front();
        q.pop();
        if (curr.B == N) {
            solution = curr.steps + "success " + std::to_string(curr.cost) + "\n"; // Update solution string
            return 1; 
        }
        
        generateNextStates(curr, q, curr.steps);
    }
    return 0; 
}

// Helper function to generate next states
void Jug::generateNextStates(Node& node, queue<Node>& q, const string& currSteps) {
    // Fill A
    if (node.A < Ca) {
        q.push(Node(Ca, node.B, node.cost + cfA, currSteps + "fill A\n"));
    }
    // Fill B
    if (node.B < Cb) {
        q.push(Node(node.A, Cb, node.cost + cfB, currSteps + "fill B\n"));
    }
    // Empty A
    if (node.A > 0) {
        q.push(Node(0, node.B, node.cost + ceA, currSteps + "empty A\n"));
    }
    // Empty B
    if (node.B > 0) {
        q.push(Node(node.A, 0, node.cost + ceB, currSteps + "empty B\n"));
    }
    // Pour A to B
    if (node.A > 0 && node.B < Cb) {
        int pour = min(node.A, Cb - node.B);
        q.push(Node(node.A - pour, node.B + pour, node.cost + cpAB, currSteps + "pour A B\n"));
    }
    // Pour B to A
    if (node.B > 0 && node.A < Ca) {
        int pour = min(node.B, Ca - node.A);
        q.push(Node(node.A + pour, node.B - pour, node.cost + cpBA, currSteps + "pour B A\n"));
    }
}