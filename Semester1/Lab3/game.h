//
// Created by Gomer on 08.12.2019.
//

#ifndef LABGAME2_GAME_H
#define LABGAME2_GAME_H
#include "players.h"
enum class Players{
  player1, player2
};

class game {
 private:
  IPlayer *p1 = nullptr;
  IPlayer *p2 = nullptr;
 public:
  game();
  ~game();
  bool gameStart();
  void makeChoice();
  static void printMods();
  static void printLogo();
  static void printRules();
};

#endif //LABGAME2_GAME_H
