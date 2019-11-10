//
// Created by Gomer on 06.11.2019.
//

#ifndef LABGAME_GAME_H
#define LABGAME_GAME_H
#include "players.h"
#include <ctime>
enum class Players{
  Player1, Player2
};

class game {
 public:
  static void printLogo();
  static void printMods();
  static bool start(IPlayer *player);
  static IPlayer *makeChoice();
};

#endif //LABGAME_GAME_H
