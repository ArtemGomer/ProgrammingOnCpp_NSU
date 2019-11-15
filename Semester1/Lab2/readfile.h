//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_READFILE_H
#define LAB32_READFILE_H
#include "factory.h"
#include <fstream>
class readfile : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override{
    std::ifstream input(args[0]);
    std::string buffer;
    while (std::getline(input, buffer)) {
      (text).push_back(buffer);
    }
  }
  blockType getType() override {
    return blockType::IN;
  }
};

REGISTER_FUNCTION(readfile);


#endif //LAB32_READFILE_H
