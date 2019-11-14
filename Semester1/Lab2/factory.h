//
// Created by Gomer on 31.10.2019.
//

#ifndef LAB32_FACTORY_H
#define LAB32_FACTORY_H
#include "Iblock.h"
#include <map>
class abstractIblockCreator {
 public:
  virtual Iblock *create() const = 0;
};

template<class C>
class IblockCreator : public abstractIblockCreator {
 public:
  Iblock *create() const override {
    return new C;
  }
};

class IblockFactory {
 private:
  std::map<std::string, abstractIblockCreator *> _factory;
 public:
  template<class C>
  void add(const std::string &id) {
    auto it = _factory.find(id);
    if (it == _factory.end())
      _factory[id] = new IblockCreator<C>();
  };
  Iblock *create(const std::string &id);
  static IblockFactory &Instance();
};

#endif //LAB32_FACTORY_H
