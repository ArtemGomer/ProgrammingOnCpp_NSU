//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_SORT_H
#define LAB32_SORT_H
#include <algorithm>
#include "Iblock.h"
#include "factory.h"

class sort : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override{
    std::sort(text.begin(), text.end());
  }
  blockType getType() override {
    return blockType::INOUT;
  }
};

REGISTER_FUNCTION(sort);
#endif //LAB32_SORT_H
