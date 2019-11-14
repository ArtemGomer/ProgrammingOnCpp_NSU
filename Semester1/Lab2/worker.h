//
// Created by Gomer on 31.10.2019.
//

#ifndef LAB32_WORKER_H
#define LAB32_WORKER_H
#include "parser.h"
#include "factory.h"
class worker {
 private:
  std::vector<std::string> text;
 public:
  void process(const char *workFile);
};

#endif //LAB32_WORKER_H
