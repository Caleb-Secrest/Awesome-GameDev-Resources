// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <random>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);
unsigned int mersenneTwister(unsigned int seed, int r1, int r2);
unsigned int middleSquareMethod(unsigned int seed, int r1, int r2);
int main(){
  // code here
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 3);

  switch(distr(gen)) {
    case 1:
      xorShift(seed, min, max);
    case 2:
      mersenneTwister(seed, min, max);
    case 3:
      middleSquareMethod(seed, min, max);
  }
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
    unsigned int xorShift(unsigned int seed, int r1, int r2)
{
  std::cout << 1 << std::endl;
}

unsigned int mersenneTwister(unsigned int seed, int r1, int r2)
{
  std::cout << 2 << std::endl;
}

unsigned int middleSquareMethod(unsigned int seed, int r1, int r2)
{
  std::cout << 3 << std::endl;
}
