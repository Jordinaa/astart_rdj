#include "AStar.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed for random number generation

    int X, Y;
    cout << "Enter grid dimensions (X Y): ";
    cin >> X >> Y;

    vector<vector<int>> grid(Y, vector<int>(X));
    // Generate random grid
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            grid[i][j] = rand() % 10 + 1; // Random numbers between 1 and 10
        }
    }
  
    // Display the grid
    cout << "Generated Grid:" << endl;
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    bool validUserInput;
    int startX, startY;
    // User chooses a starting point
    do {
        cout << "\nEnter starting point (X, Y): ";
        cin >> startX >> startY;

        if (startX < 0 || startX > X - 1 || startY < 0 || startY > Y - 1) {
            cout << "Invalid starting location, please input a coordinate within the grid\n";
            cout << "Note: The coordinates of the grid will extend from (0, 0) to one less than the size\n";
            cout << "Ex: A 10 by 10 grid will extend from (0, 0) to (9, 9)\n";
            validUserInput = false;
        }
        else
            validUserInput = true;
    } while (!validUserInput);

    int goalX, goalY;
    // User chooses a goal
    do {
        cout << "\nChoose your destination (X, Y): ";
        cin >> goalX >> goalY;

        if (goalX < 0 || goalX > X - 1 || goalY < 0 || goalY > Y - 1) {
            cout << "Invalid destination, please input a coordinate within the grid\n";
            cout << "Note: The coordinates of the grid will extend from (0, 0) to one less than the size\n";
            cout << "Ex: A 10 by 10 grid will extend from (0, 0) to (9, 9)\n";
            validUserInput = false;
        }
        else
            validUserInput = true;
    } while (!validUserInput);
    
    // Finding path
    AStar aStar(grid);
    if (!aStar.findPath(startX, startY, goalX, goalY, X - 1, Y - 1)) {
        cout << "No path found." << endl;
    }

    return 0;
}
