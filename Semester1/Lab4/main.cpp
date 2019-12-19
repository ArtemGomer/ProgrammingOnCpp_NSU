#include <tuple>
#include <iostream>
#include "CsvParser.h"
int main(int argc, char **argv) {
  std::ifstream f("in.csv", std::ios::binary);
  try {
    CsvParser<int, std::string, float> p(f, 0);
    for (auto &it : p){
      std::cout << it << std::endl;
    }
  }
  catch (std::exception &ex){
    std::cout << ex.what() << std::endl;
    f.close();
    return 1;
  }
  f.close();
  return 0;
}