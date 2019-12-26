#include "day_base.hpp"
#include <string>
#include <vector>

std::vector<std::string> day_base::load_data(std::string fileName) {
  try {
    std::ifstream ifl(fileName.c_str());
    if (ifl.is_open()) {
      std::vector<std::string> lines;
      while (ifl.good()) {
        std::string line;
        std::getline(ifl, line);
        if (!line.empty())
          lines.push_back(line);
      }
      ifl.close();
      return lines;
    } else {
      std::cout << "Couldn't open file" << std::endl;
      exit(1);
    }
  } catch (std::exception &e) {
    std::cout << "File load exception thrown:" << e.what() << std::endl;
    exit(2);
  }
}

