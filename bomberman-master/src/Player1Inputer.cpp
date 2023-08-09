

#include "Player1Inputer.h"

int Player1Inputer::getInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    return 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    return 1;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    return 2;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    return 3;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    return 4;
  }

  return -1;
}
