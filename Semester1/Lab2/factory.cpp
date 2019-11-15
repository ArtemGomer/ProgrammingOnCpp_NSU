//
// Created by Gomer on 15.11.2019.
//

#include "factory.h"
blockFactory &blockFactory::Instance() {
  static blockFactory factory;
  return factory;
}

Iblock *blockFactory::create(const std::string &id) {
  auto it = _factory.find(id);
  if (it != _factory.end()) {
    return it->second->create();
  }
  else{
    throw std::logic_error("Undefined function");
  }
}