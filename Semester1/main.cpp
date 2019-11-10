#include "game.h"

int main() {
  IPlayer *player = nullptr;
  BEGIN:
  system("cls");
  game::printLogo();
  game::printMods();
  player = game::makeChoice();
  if (game::start(player)){
    delete (player);
    goto BEGIN;
  }
  return 0;
}