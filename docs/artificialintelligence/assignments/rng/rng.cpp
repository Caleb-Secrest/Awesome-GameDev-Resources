#include <fstream>
#include <iostream>
#include <istream>
#include <random>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
unsigned int mersenneTwister(unsigned int seed, int r1, int r2);
unsigned int middleSquareMethod(unsigned int seed, int r1, int r2);

int main(){
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 3);

  switch (distr(gen)) {
    case 1:
      std::cout << "Xorshift" << std::endl;
      for (unsigned int i = 0; i < N; i++) {
        unsigned int randomNumber = xorShift(seed, min, max);
        std::cout << randomNumber << std::endl;
        seed = randomNumber;
      }
    break;
    case 2:
      std::cout << "Mersenne Twister" << std::endl;
      mersenneTwister(seed, min, max);
    break;
    case 3:
      std::cout << "Middle Square Method" << std::endl;
      middleSquareMethod(seed, min, max);
    break;
  }

  return 0;
}

unsigned int xorShift(unsigned int seed, int r1, int r2) {
  seed ^= (seed << 13);
  seed ^= (seed >> 17);
  seed ^= (seed << 5);

  int min_value = std::min(r1, r2);
  int max_value = std::max(r1, r2);

  unsigned int result = min_value + (seed % (max_value - min_value + 1));

  return result;
}

unsigned int mersenneTwister(unsigned int seed, int r1, int r2) {
  return 0;
}

unsigned int middleSquareMethod(unsigned int seed, int r1, int r2) {
  return 0;
}
