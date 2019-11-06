//
// Created by Gomer on 06.11.2019.
//

#ifndef LABGAME_GAME_H
#define LABGAME_GAME_H
#include "players.h"
enum class Players{
  Player1, Player2
};

class game {
 public:
  static void start(IPlayer *player);
};

#endif //LABGAME_GAME_H
