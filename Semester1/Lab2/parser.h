//
// Created by Gomer on 31.10.2019.
//

#ifndef LAB32_PARSER_H
#define LAB32_PARSER_H
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
class parser {
 private:
  std::map<unsigned long, std::pair<std::string,std::vector<std::string>>> parsedText;
  std::vector<unsigned long> sequence;
 public:
  void parse(const char *fileName);
  std::vector<unsigned long> &getSequence(){
    return sequence;
  }
  std::map<unsigned long, std::pair<std::string,std::vector<std::string>>> &getParsedText(){
    return parsedText;
  }
};

#endif //LAB32_PARSER_H
