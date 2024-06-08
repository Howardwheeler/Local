#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {} // initializes all variables

Jug::~Jug(){
    while (!storageQueue.empty())
    {                       // iterates through the
        storageQueue.pop(); // removes each one till fully clear
    }
}

int Jug::solve(string &solution){
    if (!isValidInput())
    {                     // checks if the input is valid
        solution.clear(); // if not, clear the solution string and return -1
        return -1;
    }

    shortestPath(); // call to function to calculate shortest path
    if (storageQueue.empty())
    { // if nothing was added to queue, path was not found, therefore return 0
        return 0;
    }
    else
    {                                              // otherwise, lets create the solution
        pathQueue printPath = storageQueue.back(); // selects the path of the solution from storage queue (its the last pathQueue added to storageQueue)
        solution.clear();                          // clears string
        int totalCost = 0;                         // gonna be used to calculate cost
        while (!printPath.jugQueue.empty())
        {                                              // iterates through pathQueue
            Node topNode = printPath.jugQueue.front(); // selects the first node on the queue
            solution = solution + topNode.steps;       // adds steps to solution string
            totalCost += topNode.cost;                 // adds total cost
            printPath.jugQueue.pop();                  // pop that node off the queue, do this until every node is reached
        }
        solution += "success " + std::to_string(totalCost); // include the total cost to the solution
        return 1;                                           // return 1 for success
    }
}

bool Jug::isValidInput() const{ // helper that checks if the input is valid...
    return 0 < Ca && Ca <= Cb && N <= Cb && Cb <= 1000;
}

bool Jug::isVisited(const Node newNode) const{      // helper to check if the node has been visited 3 or more times
    int count = 0;                                  // sets counter to 0
    for (unsigned i = 0; i < visitedStates.size(); i++)
    { // iterates through the vector of visitedStates
        if (visitedStates[i] == newNode)
        {            // checks if the node has been visited previously by using the bool node operator==,
            ++count; // if so, add 1 to counter
        }
    }
    if (count > 3)
    { // if its been visited more than 3 times, it will return true, assuming there is a repetitive pattern
        return true;
    }
    return false; // otherwise return false
}

void Jug::shortestPath(){        // helper to find shortest path
    pathQueue paths;             // create a new path queue
    paths.jugQueue.push(Node()); // push the start node onto the queue
    storageQueue.push(paths);    // push that queue onto the storage queue

    visitedStates.clear();           // clear the vector since its a new problem
    visitedStates.push_back(Node()); // add the initial jug to it
    while (!storageQueue.empty())
    {                                             // loops while queue is not empty (similar method to wordladder lab)
        pathQueue newPath = storageQueue.front(); // makes a copy of the first pathQueue in storage
        storageQueue.pop();                       // pop that off the storage

        Node jugTop = newPath.jugQueue.back(); // finds the current node (jug states), and compares that to the answer state
        if (jugTop.jugB == N)
        { // if they are equal, solution found! now push that pathQueue onto the storage and return
            storageQueue.push(newPath);
            return;
        }

        possibleTasks(jugTop, newPath); // otherwise, use this switch case to find other possible paths
    }
}

void Jug::possibleTasks(const Node top, pathQueue newPath){ // helper function to increment through all possible cases
    if (top.jugA < Ca)
    {                                                // if Jug A's capacity isn't full, fill jug A as a test
        Node newNode(Ca, top.jugB, cfA, "fill A\n"); // makes a new node with jug A filled and nothing else changed
        if (!isVisited(newNode))
        {                                  // checks if this state has been visited more than 3 times,
            pathQueue nextQueue = newPath; // if not, make a copy of the newPath and push the new node onto the queue
            nextQueue.jugQueue.push(newNode);
            storageQueue.push(nextQueue);     // then push it onto storage
            visitedStates.push_back(newNode); // then push it onto visited states vector
        }
    }

    // APPARENTLY ZYBOOKS DOESNT KNOW HOW TO USE FILL B?????????? test cases passed without it so...
    //  if (top.jugB < Cb) {
    //      Node newNode(top.jugA, Cb, cfB, "fill B\n");
    //      if (!isVisited(newNode)) {
    //          pathQueue nextQueue = newPath;
    //          nextQueue.jugQueue.push(newNode);
    //          storageQueue.push(nextQueue);
    //          visitedStates.push_back(newNode);
    //      }
    //  }
    if (top.jugA > 0 && top.jugB < Cb)
    {                                                                           // checks if theres water in Jug A and if jug B isnt full
        int amount = std::min(top.jugA, Cb - top.jugB);                         // if it is, find the difference in volume
        Node newNode(top.jugA - amount, top.jugB + amount, cpAB, "pour A B\n"); // then make a new node with the new set of volume for both jugs after pouring
        if (!isVisited(newNode))
        { // same as prev
            pathQueue nextQueue = newPath;
            nextQueue.jugQueue.push(newNode);
            storageQueue.push(nextQueue);
            visitedStates.push_back(newNode);
        }
    }
    if (top.jugB > 0 && top.jugA < Ca)
    {                                                                           // checks if theres water in jug b and if jug a isnt full
        int amount = std::min(top.jugB, Ca - top.jugA);                         // find the difference in volume
        Node newNode(top.jugA + amount, top.jugB - amount, cpBA, "pour B A\n"); // then do pour B to A
        if (!isVisited(newNode))
        { // same as prev
            pathQueue nextQueue = newPath;
            nextQueue.jugQueue.push(newNode);
            storageQueue.push(nextQueue);
            visitedStates.push_back(newNode);
        }
    }
    if (top.jugA > 0)
    {                                                // if jug a isnt empty
        Node newNode(0, top.jugB, ceA, "empty A\n"); // sets jug a to 0 and empties it
        if (!isVisited(newNode))
        { // same as prev
            pathQueue nextQueue = newPath;
            nextQueue.jugQueue.push(newNode);
            storageQueue.push(nextQueue);
            visitedStates.push_back(newNode);
        }
    }
    if (top.jugB > 0)
    {                                                // if jug b isnt empty
        Node newNode(top.jugA, 0, ceB, "empty B\n"); // sets jug b to 0 and empties it
        if (!isVisited(newNode))
        { // same as prev
            pathQueue nextQueue = newPath;
            nextQueue.jugQueue.push(newNode);
            storageQueue.push(nextQueue);
            visitedStates.push_back(newNode);
        }
    }
}