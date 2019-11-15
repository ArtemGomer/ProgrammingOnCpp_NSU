//
// Created by Gomer on 28.10.2019.
//

#ifndef LAB31_IBLOCK_H
#define LAB31_IBLOCK_H
#include <string>
#include <vector>
#include <map>

#define REGISTER_FUNCTION(C) static blockCreator<C> C(#C)

enum class blockType{
  IN, INOUT, OUT
};

class Iblock {
 public:
  virtual ~Iblock() = default;
  virtual void execute(std::vector<std::string> &args, std::vector<std::string> &text) = 0;
  virtual blockType getType() = 0;
};

#endif //LAB31_IBLOCK_H
