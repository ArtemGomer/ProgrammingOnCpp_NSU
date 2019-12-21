//
// Created by Gomer on 16.12.2019.
//

#ifndef LAB5_1_CSVPARSER_H
#define LAB5_1_CSVPARSER_H
#include <fstream>
#include <sstream>
#include <tuple>
#include <string>
#include <vector>
#include <limits>

template<size_t i, typename... Args>
typename std::enable_if<(i >= sizeof...(Args))>::type
printTuple(std::ostream &, const std::tuple<Args...> &tuple) { return; }

template<size_t i, typename... Args>
typename std::enable_if<(i < sizeof...(Args))>::type
printTuple(std::ostream &out, std::tuple<Args...> tuple) {
  if (i != 0) {
    out << ", ";
  }
  out << std::get<i>(tuple);
  printTuple<i + 1>(out, tuple);
}

template<typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &tup) {
  printTuple<0>(os, tup);
  return os;
}

template<typename T>
T convert(std::string &cell) {
  T t;
  std::stringstream str(cell);
  str.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  str >> t;
  return t;
}

template<>
std::string convert(std::string &cell) {
  return cell;
}

static std::vector<std::string> parseLine(std::string &line, const size_t columns) {
  std::vector<std::string> parsedLine;
  for (size_t i = 0; i < line.size(); i++) {
    std::string cell;
    while (i < line.size() && line[i] != ';') {
      cell += line[i];
      i++;
    }
    if (!cell.empty()) {
      parsedLine.push_back(cell);
    }
  }
  if (parsedLine.size() != columns){
    throw std::logic_error("Wrong data table");
  }
  return parsedLine;
}

template<size_t i, typename... Args>
typename std::enable_if<(i >= sizeof...(Args))>::type
createTuple(std::vector<std::string> &parsedLine, std::tuple<Args...> &tuple) {
  return;
}

template<size_t i, typename... Args>
typename std::enable_if<(i < sizeof...(Args))>::type
createTuple(std::vector<std::string> parsedLine, std::tuple<Args...> &tuple) {
  std::get<i>(tuple) = convert<typename std::tuple_element<i, std::tuple<Args...>>::type>(parsedLine[i]);
  createTuple<i + 1>(parsedLine, tuple);
}

template <typename... Args>
class CsvParser{
 private:
  std::ifstream &stream;
 public:
  class Iterator;
  CsvParser(std::ifstream &in, size_t skipLines) : stream(in){
    std::string trash;
    for (size_t i = 0; i < skipLines; i++){
      std::getline(stream, trash);
    }
  }
  Iterator begin() const{
    return Iterator(&stream);
  }
  Iterator end() const{
    return Iterator();
  }
  class Iterator{
   private:
    std::ifstream *_stream;
    std::tuple<Args...> rowTuple;
    size_t filePos;
    void readLine(std::ifstream &in){
      std::string line;
      in.seekg(filePos);
      std::getline(in, line);
      filePos = in.tellg();
      if (line.empty()){
        return;
      }
      createTuple<0>(parseLine(line, sizeof...(Args)), rowTuple);
    }
   public:
    explicit Iterator(std::ifstream *in) : _stream(in){
      filePos = 0;
      readLine(*(_stream));
    }
    Iterator() : _stream(nullptr){
      filePos = SIZE_MAX;
    }
    std::tuple<Args...> const &operator*() const{
      return rowTuple;
    }
    Iterator &operator++(){
      readLine(*(_stream));
      if (_stream->eof()){
        _stream = nullptr;
      }
      return *this;
    }
    bool operator==(Iterator const &it){
      return (this->filePos == it.filePos || (this->_stream == nullptr && it._stream == nullptr));
    }
    bool operator!=(Iterator const &it){
      return !((*this)==it);
    }
  };
};

#endif //LAB5_1_CSVPARSER_H
