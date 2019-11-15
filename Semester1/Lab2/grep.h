//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_GREP_H
#define LAB32_GREP_H
#include "factory.h"

class grep : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override{
    for (size_t i = 0; i < (text).size(); i++){
      if ((text[i].find((args)[0]) == std::string::npos)){
        text.erase(text.begin() + i);
        i--;
      }
    }
  }
  blockType getType() override {
    return blockType::INOUT;
  }
};

REGISTER_FUNCTION(grep);

#endif //LAB32_GREP_H
