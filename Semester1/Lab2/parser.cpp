#include "parser.h"
void parser::parse(const char *fileName) {
  std::ifstream in(fileName);
  if (!in.is_open()){
    throw std::invalid_argument("Can`t open file");
  }
  std::string buffer;
  std::getline(in, buffer);
  if (buffer != "desc"){
    throw std::logic_error("Wrong file content");
  }
  while (true){
    std::getline(in, buffer);
    if (buffer == "csed"){
      break;
    }
    if (in.eof()){
      throw std::logic_error("Wrong file content");
    }
    size_t counter = 0;
    std::string id;
    std::string part;
    while (buffer[counter] != '='){
      id += buffer[counter];
      counter++;
    }
    counter++;
    while (buffer[counter] == ' '){
      counter++;
    }
    while (buffer[counter] != ' ' && buffer[counter] != '\0'){
      part += buffer[counter];
      counter++;
    }
    parsedText[std::stoul(id)].first = part;
    for (;counter <= buffer.length(); counter++){
      part.clear();
      while (buffer[counter] == ' '){
        counter++;
      }
      while (buffer[counter] != ' ' && buffer[counter] != '\0'){
        part += buffer[counter];
        counter++;
      }
      parsedText[std::stoul(id)].second.push_back(part);
    }
  }
  std::getline(in, buffer);
  if (buffer.empty()){
    throw std::logic_error("Wrong file content");
  }
  for (size_t counter = 0; counter <= buffer.length(); counter++){
    std::string part;
    while (buffer[counter] == ' '){
      counter++;
    }
    while (buffer[counter] != ' ' && buffer[counter] != '\0'){
      part += buffer[counter];
      counter++;
    }
    if (part != "->") {
      sequence.push_back(std::stoul(part));
    }
  }
  for (const auto &i : parsedText) {
    std::cout << i.first << " ";
    std::cout << i.second.first << " ";
    for (const auto &j : i.second.second) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
  for (const auto &i : sequence) {
    std::cout << i << " ";
  }
}