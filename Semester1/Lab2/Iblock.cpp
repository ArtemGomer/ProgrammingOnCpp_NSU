//
// Created by Gomer on 28.10.2019.
//

#include "Iblock.h"
void Writefile::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  std::ofstream output(args[0]);
  std::string buffer;
  for (const std::string &str : text) {
    output << str << std::endl;
  }
}

void Readfile::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  std::ifstream input(args[0]);
  std::string buffer;
  while (std::getline(input, buffer)) {
    (text).push_back(buffer);
  }
}

void Grep::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  for (size_t i = 0; i < (text).size(); i++){
    if ((text[i].find((args)[0]) == std::string::npos)){
      text.erase(text.begin() + i);
      i--;
    }
  }
}

void Sort::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  sort(text.begin(), text.end());
}

void Dump::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  Writefile w;
  w.execute(args, text);
}

void Replace::execute(std::vector<std::string> &args, std::vector<std::string> &text) {
  for (auto & i : text){
    for (auto j = i.find(args[0]); j != std::string::npos; j = i.find(args[0])){
      i.replace(j, j + args[0].length(), args[1]);
    }
  }
}
