#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include <iostream>

int main(int argc, char **argv) {
  int day = std::stoi(argv[1]);
  int half = std::stoi(argv[2]);

  switch (day) {
  case 1:
    day1().run_sim(half);
    break;
  case 2:
    day2().run_sim(half);
    break;
  case 3:
    day3().run_sim(half);
    break;
  default:
    std::cout << "Day " << day << " not implemented yet!" << std::endl;
  }

  return 0;
}
