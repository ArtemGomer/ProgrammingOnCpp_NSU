//
// Created by Gomer on 30.09.2019.
//

#include "wordCounter.h"

wordCounter::wordCounter() {
  counter = 0;
}

void wordCounter::countFrequency(char *inFileName) {
  std::ifstream in(inFileName);
  if (!in) {
    throw std::invalid_argument("Can not open file ");
  }
  std::string buffer, key;
  while (std::getline(in, buffer, '\n')) {
    int length = buffer.length();
    for (int i = 0; i <= length; i++) {
      if (isalpha(buffer[i]) || isdigit(buffer[i])) {
        key += buffer[i];
      } else {
        if (!key.empty()) {
          statistic[key]++;
          counter++;
          key.clear();
        }
      }
    }
  }
  for (const auto &pair : statistic) {
    items.emplace_back(pair.second, pair.first);
  }
  in.close();
}

void wordCounter::printFrequency(char *outFileName) {
  std::ofstream out(outFileName);
  items.sort([](auto &left, auto &right) {
    return left.first < right.first;
  });
  for (const auto &pair : items) {
    out << pair.first << ";" << pair.second << ";" << (pair.first / (float) counter) * 100 << std::endl;
  }
  out.close();
}

