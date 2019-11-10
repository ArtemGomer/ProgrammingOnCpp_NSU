//
// Created by Gomer on 06.11.2019.
//

#ifndef LABGAME_PLAYERS_H
#define LABGAME_PLAYERS_H
#include <string>
#include <iostream>
class IPlayer {
 protected:
  std::string name;
  std::string number;
 public:
  virtual ~IPlayer() = default;
  virtual void playerGenerator() = 0;
  virtual std::string generateNumber() = 0;
  virtual bool check(const std::string &atp, const std::string &opNumber) = 0;
  [[nodiscard]] std::string getName() const;
  [[nodiscard]] std::string getNumber() const;
};

class HumanPlayer : public IPlayer {
 public:
  std::string generateNumber() override;
  void playerGenerator() override;
  bool check(const std::string &atp, const std::string &opNumber) override;
};

class PrimitiveAI : public IPlayer{
 private:
  int bulls[10]{};
  int state;
 public:
  PrimitiveAI();
  void playerGenerator() override;
  std::string generateNumber() override;
  bool check(const std::string &atp, const std::string &opNumber) override;
};

//class AdvancedAI : public IPlayer{
// public:
//  void playerGenerator() override;
//};
#endif //LABGAME_PLAYERS_H
