#include "game.h"

int main() {
  IPlayer *player = nullptr;
  while (true) { //Повтор игры при выборе 'y'
    system("cls");
    game::printLogo();
    player = game::makeChoice();
    if (player) {
      if (game::start(player)) {
        delete (player);
        continue;
      } else {
        delete (player);
        break;
      }
    } else {
      break;
    }
  }
  return 0;
}