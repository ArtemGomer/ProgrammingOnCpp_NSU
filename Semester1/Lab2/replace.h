//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_REPLACE_H
#define LAB32_REPLACE_H
#include "factory.h"

class replace : public  Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override{
    for (auto & i : text){
      for (auto j = i.find(args[0]); j != std::string::npos; j = i.find(args[0])){
        i.replace(j, j + args[0].length(), args[1]);
      }
    }
  }
  blockType getType() override {
    return blockType::INOUT;
  }
};

REGISTER_FUNCTION(replace);

#endif //LAB32_REPLACE_H
