//
// Created by sbixby on 12/12/19.
//

#ifndef AOC2019_DAY_BASE_HPP
#define AOC2019_DAY_BASE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class day_base {
public:
  virtual std::vector<std::string> load_data(std::string fileName);
  virtual void run_sim(int half) = 0;
};

#endif // AOC2019_DAY_BASE_HPP
