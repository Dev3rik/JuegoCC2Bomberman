

#include "Player2Inputer.h"

int Player2Inputer::getInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return 1;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    return 2;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    return 3;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
    return 4;
  }

  return -1;
}
