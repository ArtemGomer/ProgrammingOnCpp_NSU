//
// Created by Gomer on 06.11.2019.
//

#include "game.h"
void game::start(IPlayer *player2) {
  HumanPlayer player1;
  player1.playerGenerator();
  player2->playerGenerator();
  system("cls");
  Players state = Players::Player1;
  while (true) {
    if (state == Players::Player1) {
      std::string attempt = player1.generateNumber();
      system("cls");
      if (player1.check(attempt, player2->getNumber())) {
        std::cout << player1.getName() << " wins.";
        break;
      }
      state = Players::Player2;
    } else {
      std::string attempt = player2->generateNumber();
      system("cls");
      if (player2->check(attempt, player1.getNumber())) {
        std::cout << player2->getName() << " wins.";
        break;
      }
      state = Players::Player1;
    }
  }
}