//
// Created by Gomer on 09.09.2019.
//

#ifndef LAB00_WORDCOUNTER_H
#define LAB00_WORDCOUNTER_H
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
class frequency {
 private:
  int count;
  vector <pair<int, string>> items;
  void isEmpty(string &strKey, map<string, int> & mp);
 public:
  frequency();
  void countFrequency();
  void writeFrequency();
};
#endif //LAB00_WORDCOUNTER_H
