//
// Created by Gomer on 31.10.2019.
//
#include "factory.h"

IblockFactory &IblockFactory::Instance() {
  static IblockFactory factory;
  return factory;
}

Iblock *IblockFactory::create(const std::string &id) {
  auto it = _factory.find(id);
  if (it != _factory.end()) {
    return it->second->create();
  }
  else{
    throw std::logic_error("Undefined function");
  }
}