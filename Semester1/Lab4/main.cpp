#include <tuple>
#include <iostream>
#include "CsvParser.h"
int main(int argc, char **argv) {
  std::ifstream f("in.csv", std::ios::binary);
  CsvParser<int, std::string, float> p(f, 0);
  for (auto &it : p){
    std::cout << it << std::endl;
  }
//  for (auto it = p.begin(); it != p.end(); ++it) {
//    std::cout << *it << std::endl;
//  }
  f.close();
  return 0;
}
