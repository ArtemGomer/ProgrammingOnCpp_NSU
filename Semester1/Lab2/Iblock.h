//
// Created by Gomer on 28.10.2019.
//

#ifndef LAB31_IBLOCK_H
#define LAB31_IBLOCK_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
class Iblock {
 public:
  virtual ~Iblock() = default;
  virtual void execute(std::vector<std::string> &args, std::vector<std::string> &text) = 0;
};

class Readfile : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

class Writefile : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

class Sort : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

class Grep : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

class Dump : public Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

class Replace : public  Iblock{
 public:
  void execute(std::vector<std::string> &args, std::vector<std::string> &text) override;
};

#endif //LAB31_IBLOCK_H
