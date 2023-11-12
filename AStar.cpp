// Dylan Frazier 11/11/2023
// Jordan Taranto 10/25/2023
// Created by Riley Connors on 10/24/23.
//

#include "AStar.h"
#include <iostream>
#include <cmath>

using namespace std;

struct AStar::Node {
    int x, y;
    float f, g, h;
    Node* parent;
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

struct AStar::Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f;
    }
};

struct AStar::HashFunction {
    size_t operator()(const Node& node) const {
        return node.x * 31 + node.y;
    }
};

float AStar::heuristic(int x1, int y1, int x2, int y2) {
    return (3*abs(x1 - x2)) + (3*abs(y1 - y2));
}

AStar::AStar(vector<vector<int>> grid) : grid(grid) {}

bool AStar::findPath(int startX, int startY, int goalX, int goalY, int gridSizeX, int gridSizeY) {
    priority_queue<Node, vector<Node>, Compare> openList;
    unordered_set<Node, HashFunction> closedList;

    Node start = {startX, startY, 0, 0, heuristic(startX, startY, goalX, goalY), nullptr};
    Node goal = {goalX, goalY, 0, 0, 0, nullptr};

    openList.push(start);
    vector<Node> parentTracker;
    Node current = openList.top();
    int intCounter = 0;
    int weightTotal = 0;

    while (intCounter < 3*(gridSizeX + gridSizeY)) {
        current = openList.top();
        parentTracker.push_back(current);
        weightTotal += grid[current.x][current.y];
        openList = priority_queue<Node, vector<Node>, Compare>();


        if (current == goal) {
            cout << "Reached the goal! Path: ";

            for (int i = 0; i < parentTracker.size(); i++)
            {
                cout << "(" << parentTracker[i].x << ", " << parentTracker[i].y << ") ";
            }
            cout << "\nTotal distance: " << weightTotal << " units\n";

            return true;
        }
        
        closedList.insert(current);

        vector<Node> successors;
        if (current.x + 1 >= 0 && current.x + 1 <= gridSizeX) {
            successors.push_back({ current.x + 1, current.y, 0, 0, 0, &current });
            successors.back().g = grid[current.x + 1][current.y];
        }
       
        if (current.x - 1 >= 0 && current.x - 1 <= gridSizeX) {
            successors.push_back({ current.x - 1, current.y, 0, 0, 0, &current });
            successors.back().g = grid[current.x - 1][current.y];
        }
            
        if (current.y + 1 >= 0 && current.y + 1 <= gridSizeY) {
            successors.push_back({ current.x, current.y + 1, 0, 0, 0, &current });
            successors.back().g = grid[current.x][current.y + 1];
        }

        if (current.y - 1 >= 0 && current.y - 1 <= gridSizeY) {
            successors.push_back({ current.x, current.y - 1, 0, 0, 0, &current });
            successors.back().g = grid[current.x][current.y - 1];
        }
        
        for (Node& neighbor : successors) {
            if (grid[neighbor.y][neighbor.x] == 0) {
                continue;
            }
            if (closedList.find(neighbor) != closedList.end()) {
                continue;
            }

            neighbor.h = heuristic(neighbor.x, neighbor.y, goal.x, goal.y);
            neighbor.f = neighbor.g + neighbor.h;

            openList.push(neighbor);
        }
        intCounter++;
    }

    cout << "Failed to reach the goal." << endl;
    return false;
}
