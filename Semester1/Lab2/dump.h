//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_DUMP_H
#define LAB32_DUMP_H
#include "factory.h"
#include <fstream>

class dump : public Iblock {
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override {
    std::ofstream output(args[0]);
    std::string buffer;
    for (const std::string &str : text) {
      output << str << std::endl;
    }
  }
  blockType getType() override {
    return blockType::INOUT;
  }
};

REGISTER_FUNCTION(dump);

#endif //LAB32_DUMP_H
