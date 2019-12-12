#include "day1.hpp"
#include <iostream>

int main(int argc, char **argv) {
  int day = std::stoi(argv[1]);
  int half = std::stoi(argv[2]);

  switch (day) {
  case 1:
    day1().run_sim(half);
    break;
  default:
    std::cout << "Day " << day << " not implemented yet!" << std::endl;
  }

  return 0;
}
