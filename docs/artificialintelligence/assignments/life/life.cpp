#include <iostream>
#include <string>

// Life Function Algorithm
struct Life {
  std::string* worldGrid;
  int column;
  int row;

  // Constructor
  Life() : worldGrid(nullptr), column(0), row(0) {}

  // Deconstructor
  ~Life() {
    delete[] worldGrid;
  }

  //Sets default variables for Life Struct
  void SetWorld(std::string* grid, int col, int r) {
    column = col;
    row = r;
    worldGrid = new std::string[row];
    for (int i = 0; i < row; i++) {
      worldGrid[i] = grid[i];
    }
  }

  // Checks the eight neighbors to see how many are alive and returns that number
  int CheckNeightbors(int x, int y) {
    int liveNeighbors = 0;
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},{ 0, -1},{ 0, 1}, { 1, -1}, { 1, 0}, { 1, 1} };

    // Checks to see if each neighbor is alive and keeps track of the total
    for (auto& dir : directions) {
      int nx = (x + dir[0] + row) % row;
      int ny = (y + dir[1] + column) % column;
      if (worldGrid[nx][ny] == '#') {
        liveNeighbors++;
      }
    }
    return liveNeighbors;
  }

  // Updates the grid by one turn and changes each cell acordingly based on living neighbors
  void Update() {
    std::string* newGrid = new std::string[row];
    for (int i = 0; i < row; i++) {
      newGrid[i] = worldGrid[i];
    }

    // Runs through each cell to see if it needs to be turned alive, dead, or left alone
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        int liveNeighbors = CheckNeightbors(i, j);

        // Checks to see if a living cell needs to be killed
        if (worldGrid[i][j] == '#') {
          if (liveNeighbors < 2 || liveNeighbors > 3) {
            newGrid[i][j] = '.';
          }
        } else { // Checks to see if a dead cell needs to revived
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

  // Sets grid from the users input
  for (int i = 0; i < row; i++) {
    std::cin >> orgGrid[i];
  }

  // Gives the grid to the life function
  life.SetWorld(orgGrid, column, row);

  // Clears grid for memory purposes
  delete[] orgGrid;

  // Simulates life by the numer of turns the user gave
  for (int t = 0; t < turns; t++) {
    life.Update();
  }

  // Prints out the new grid with updated cells
  for (int i = 0; i < row; i++) {
    std::cout << life.worldGrid[i] << std::endl;
  }

  return 0;
}
