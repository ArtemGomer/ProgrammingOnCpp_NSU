//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_WRITEFILE_H
#define LAB32_WRITEFILE_H
#include "factory.h"
#include <fstream>

class writefile : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override{
    std::ofstream output(args[0]);
    std::string buffer;
    for (const std::string &str : text) {
      output << str << std::endl;
    }
  }
  blockType getType() override {
    return blockType::OUT;
  }
};

REGISTER_FUNCTION(writefile);
#endif //LAB32_WRITEFILE_H
