#include "AStar.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed for random number generation

    int X, Y;
    cout << "Enter grid dimensions they must be an odd number so you can have a (0,0) origin in the center (X Y): ";
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

    // User chooses a corner
    cout << "Choose your destination corner (1: top-left, 2: top-right, 3: bottom-left, 4: bottom-right): ";
    int choice;
    cin >> choice;

    int goalX, goalY;
    switch (choice) {
        case 1: goalX = 0; goalY = 0; break;
        case 2: goalX = X - 1; goalY = 0; break;
        case 3: goalX = 0; goalY = Y - 1; break;
        case 4: goalX = X - 1; goalY = Y - 1; break;
        default: cout << "Invalid choice. Exiting." << endl; return 1;
    }

    // Assuming the starting point is (0, 0)
    AStar aStar(grid);
    if (!aStar.findPath(0, 0, goalX, goalY)) {
        cout << "No path found." << endl;
    }

    return 0;
}
