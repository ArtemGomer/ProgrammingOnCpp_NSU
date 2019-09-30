//
// Created by Gomer on 30.09.2019.
//

#ifndef LAB01_WORDCOUNTER_H
#define LAB01_WORDCOUNTER_H
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>


class wordCounter {
 private:
  int counter;
  std::map<std::string, int> statistic;
  std::list<std::pair<int, std::string>> items;
 public:
  wordCounter();
  void countFrequency(char *inFileName);
  void printFrequency(char *outFileName);
};

#endif //LAB01_WORDCOUNTER_H
