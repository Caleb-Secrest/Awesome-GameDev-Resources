#include <iostream>
#include <string>

struct Life {
    std::string* worldGrid;
    int column;
    int row;

  Life() : worldGrid(nullptr), column(0), row(0) {}

  ~Life() {
    delete[] worldGrid;
  }

    void SetWorld(std::string* grid, int col, int r) {
        column = col;
        row = r;
        worldGrid = new std::string[row];
        for (int i = 0; i < row; i++) {
            worldGrid[i] = grid[i];
        }
    }

    int CheckNeightbors(int x, int y) {
        int liveNeighbors = 0;
        int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},{ 0, -1},{ 0, 1}, { 1, -1}, { 1, 0}, { 1, 1} };

        for (auto& dir : directions) {
            int nx = (x + dir[0] + row) % row;
            int ny = (y + dir[1] + column) % column;
            if (worldGrid[nx][ny] == '#') {
                liveNeighbors++;
            }
        }
        return liveNeighbors;
    }

    void Update() {
        std::string* newGrid = new std::string[row];
        for (int i = 0; i < row; i++) {
            newGrid[i] = worldGrid[i];
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                int liveNeighbors = CheckNeightbors(i, j);

                if (worldGrid[i][j] == '#') {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newGrid[i][j] = '.';
                    }
                } else {
                    if (liveNeighbors == 3) {
                        newGrid[i][j] = '#';
                    }
                }
            }
        }

        delete[] worldGrid;
        worldGrid = newGrid;
    }
};

int main() {
    Life life;

    int column, row, turns;
    std::cin >> column >> row >> turns;

    std::string* orgGrid = new std::string[row];

    for (int i = 0; i < row; i++) {
        std::cin >> orgGrid[i];
    }

    life.SetWorld(orgGrid, column, row);

    delete[] orgGrid;

    for (int t = 0; t < turns; t++) {
        life.Update();
    }

    for (int i = 0; i < row; i++) {
        std::cout << life.worldGrid[i] << std::endl;
    }

    return 0;
}
