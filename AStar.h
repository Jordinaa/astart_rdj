// Jordan Taranto 10/25/2023
// Created by Riley Connors on 10/24/23.
//

#ifndef ASTART_RDJ2_ASTAR_H
#define ASTART_RDJ2_ASTAR_H


#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class AStar {
public:
    struct Node;
    struct Compare;
    struct HashFunction;

    static float heuristic(int x1, int y1, int x2, int y2);
    vector<vector<int>> grid;

    AStar(vector<vector<int>> grid);
    bool findPath(int startX, int startY, int goalX, int goalY);
};



#endif //ASTART_RDJ2_ASTAR_H
