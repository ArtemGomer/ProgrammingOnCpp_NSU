//
// Created by Gomer on 15.11.2019.
//

#ifndef LAB32_FACTORY_H
#define LAB32_FACTORY_H
#include "Iblock.h"

class IblockCreator {
 public:
  virtual Iblock *create() const = 0;
};

class blockFactory {
 private:
  std::map<std::string, IblockCreator *> _factory;
 public:
  void add(const std::string &id, IblockCreator* creator) {
    auto it = _factory.find(id);
    if (it == _factory.end())
      _factory[id] = creator;
  };
  Iblock *create(const std::string &id);
  static blockFactory &Instance();
};

template<class C>
class blockCreator : public IblockCreator {
 public:
  blockCreator(const std::string &key){
    blockFactory::Instance().add(key, this);
  }
  Iblock *create() const override {
    return new C;
  }
};

#endif //LAB32_FACTORY_H
