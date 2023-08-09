

#include "TileMap.h"

void TileMap::draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const {
  for (int i = 0; i < this->capas.size(); i++) {
    this->capas[i]->draw(objetivo, estados);
  }
}

TileMap::~TileMap() {
  for (int i = 0; i < this->capas.size(); i++) {
    delete this->capas[i];
  }
}
