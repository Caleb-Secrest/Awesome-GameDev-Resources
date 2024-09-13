#include <iostream>
#include <iomanip>

int main() {
  int column, row, turns;
  std::cin >> column >> row >> turns;

  std::string* gridSize;
  gridSize = new std::string[column * row];

  for (int i = 0; i < column * row; i++) {
    //gridSize[i] = "*";
    std::cin >> gridSize[i];
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      std::cout << gridSize[i * j];
    }
    std::cout << std::endl;
  }

  return 0;
}
