

#include "Bomb.h"

Bomba::Bomba(int radio) {
  this->radio = radio;
  this->usado = false;
  this->limpiar = false;
}

void Bomba::ponerBomba(sf::Vector2i bombPos, TileMap* tileMap) {
  this->bombaTiempo.restart();
  this->bombaPos = bombPos;

  tileMap->capas[1]->mapaArray[bombPos.x + bombPos.y * 13] = 3;
  tileMap->capas[1]->update();

  this->usado = true;
}

void Bomba::check(TileMap *tileMap) {
  if (this->usado && !this->limpiar && this->bombaTiempo.getElapsedTime().asSeconds() >= 3) {
      this->setFuego(tileMap);
  }

  if (this->limpiar && this->fuegoTiempo.getElapsedTime().asSeconds() >= 2) {
      this->limpiarFuego(tileMap);
  }
}

void Bomba::setFuego(TileMap* tileMap) {
  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + i + bombaPos.y * 13] == 0) {
      break;
    }

    if (tileMap->capas[0]->mapaArray[bombaPos.x + i + bombaPos.y * 13] == 2) {
      tileMap->capas[0]->mapaArray[bombaPos.x + i + bombaPos.y * 13] = 1;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + i + bombaPos.y * 13] = 4;
  }

  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x - i + bombaPos.y * 13] == 0) {
      break;
    }

    if (tileMap->capas[0]->mapaArray[bombaPos.x - i + bombaPos.y * 13] == 2) {
      tileMap->capas[0]->mapaArray[bombaPos.x - i + bombaPos.y * 13] = 1;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x - i + bombaPos.y * 13] = 4;
  }

  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] == 0) {
      break;
    }

    if (tileMap->capas[0]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] == 2) {
      tileMap->capas[0]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] = 1;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] = 4;
  }


  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] == 0) {
      break;
    }

    if (tileMap->capas[0]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] == 2) {
      tileMap->capas[0]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] = 1;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] = 4;
  }

  tileMap->capas[0]->update();
  tileMap->capas[1]->update();

  fuegoTiempo.restart();
  this->limpiar = true;
}

void Bomba::limpiarFuego(TileMap* tileMap) {
  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + i + bombaPos.y * 13] == 0) {
      break;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + i + bombaPos.y * 13] = 1;
  }

  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x - i + bombaPos.y * 13] == 0) {
      break;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x - i + bombaPos.y * 13] = 1;
  }

  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] == 0) {
      break;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y + i) * 13] = 1;
  }

  for (int i = 0; i < this->radio; i++) {
    if (tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] == 0) {
      break;
    }

    tileMap->capas[1]->mapaArray[bombaPos.x + (bombaPos.y - i) * 13] = 1;
  }

  tileMap->capas[1]->update();

  this->limpiar = false;
  this->usado = false;
}

bool Bomba::esUsado() const {
  return usado;
}



