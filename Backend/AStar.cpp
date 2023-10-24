//
// Created by Riley Connors on 10/24/23.
//

#include "AStar.h"
#include <iostream>
#include <cmath>

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
    std::size_t operator()(const Node& node) const {
        return node.x * 31 + node.y;
    }
};

float AStar::heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

AStar::AStar(std::vector<std::vector<int>> grid) : grid(grid) {}

bool AStar::findPath(int startX, int startY, int goalX, int goalY) {
    std::priority_queue<Node, std::vector<Node>, Compare> openList;
    std::unordered_set<Node, HashFunction> closedList;

    Node start = {startX, startY, 0, 0, heuristic(startX, startY, goalX, goalY), nullptr};
    Node goal = {goalX, goalY, 0, 0, 0, nullptr};

    openList.push(start);

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current == goal) {
            std::cout << "Reached the goal! Path: ";
            Node* pathNode = &current;
            while (pathNode) {
                std::cout << "(" << pathNode->x << ", " << pathNode->y << ") ";
                pathNode = pathNode->parent;
            }
            std::cout << std::endl;
            return true;
        }

        closedList.insert(current);

        std::vector<Node> successors = {
                {current.x + 1, current.y, 0, 0, 0, &current},
                {current.x - 1, current.y, 0, 0, 0, &current},
                {current.x, current.y + 1, 0, 0, 0, &current},
                {current.x, current.y - 1, 0, 0, 0, &current}
        };

        for (Node& neighbor : successors) {
            if (grid[neighbor.y][neighbor.x] == 0) {
                continue;
            }
            if (closedList.find(neighbor) != closedList.end()) {
                continue;
            }

            neighbor.g = current.g + 1.0;
            neighbor.h = heuristic(neighbor.x, neighbor.y, goal.x, goal.y);
            neighbor.f = neighbor.g + neighbor.h;

            openList.push(neighbor);
        }
    }

    std::cout << "Failed to reach the goal." << std::endl;
    return false;
}
