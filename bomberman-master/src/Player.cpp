

#include "Player.h"

Player::Player(const std::string& textura, sf::Vector2f playerTamanho, sf::Vector2f playerPos, sf::Vector2u imageContador, float cambiarTiempo, float velocidad, Inputer* inputer, int radio) : animacion(textura, imageContador, cambiarTiempo), inputer(inputer), bomba(radio) {
  this->velocidad = velocidad;
  this->fila = 0;
  this->direccion = -1;
  this->enMovimiento = false;
  this->playerPos = this->cuerpo.getPosition();
  this->muerto = false;

  this->cuerpo.setSize(playerTamanho);
  this->cuerpo.setOrigin(playerTamanho.x / 2, playerTamanho.y > 64 ? 96 : 32);
  this->cuerpo.setPosition(playerPos);
  this->cuerpo.setTexture(&this->animacion.getTextura());
  this->cuerpo.setTextureRect(this->animacion.getUvRect());
}

Player::~Player() {
  delete this->inputer;
}

void Player::draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const {
    estados.texture = &this->animacion.getTextura();
  objetivo.draw(this->cuerpo, estados);
}

sf::Vector2f Player::direccionEnPaso(int dir) {
  if (dir == 0) {
    this->fila = 2;
    this->faceRight = false;
    return {-this->velocidad, 0};
  } else if (dir == 1) {
    this->fila = 2;
    this->faceRight = true;
    return {this->velocidad, 0};
  } else if (dir == 2) {
    this->fila = 1;
    return {0, -this->velocidad};
  } else if (dir == 3) {
    this->fila = 0;
    return {0, this->velocidad};
  }

  return {0, 0};
}

const bool Player::checkColision(const std::vector<int>& mapa) const {
  int x = this->destino.x / 64;
  int y = this->destino.y / 64;
  int collision = mapa[x + y * 13];
  return collision == 0 || collision == 2 || collision == 3;
}

const bool Player::checkMuerte(const std::vector<int>& mapa) const {
  int x = this->cuerpo.getPosition().x / 64;
  int y = this->cuerpo.getPosition().y / 64;

  return mapa[x + y * 13] == 4;
}

void Player::update(float deltaTime, TileMap* tileMap) {
  this->bomba.check(tileMap);

  if (this->checkMuerte(tileMap->capas[1]->mapaArray)) {
    this->muerto = true;
    return;
  }

  int input = this->inputer->getInput();

  if (this->enMovimiento) {
    if (checkColision(tileMap->capas[0]->mapaArray) || checkColision(tileMap->capas[1]->mapaArray)) {
      this->enMovimiento = false;
      return;
    }

    if (this->cuerpo.getPosition() != this->destino) {
      sf::Vector2f step = direccionEnPaso(this->direccion);
      sf::Vector2f newStep = direccionEnPaso(input);

      if (step == -newStep) {
        step = newStep;
        this->direccion = input;
        this->destino = this->destino + (step / this->velocidad) * 64.f;
        return;
      }

      this->animacion.update(this->fila, deltaTime, this->faceRight);
      this->cuerpo.setTextureRect(this->animacion.getUvRect());
      this->cuerpo.move(step);
      return;
    }

    this->enMovimiento = false;
  }

  if (input == -1) {
    return;
  }

  if (input == 4 && !this->bomba.esUsado()) {
    sf::Vector2i bombPos;
    bombPos.x = this->cuerpo.getPosition().x / 64;
    bombPos.y = this->cuerpo.getPosition().y / 64;
      this->bomba.ponerBomba(bombPos, tileMap);
    return;
  }

  this->enMovimiento = true;
  this->direccion = input;

  switch (input) {
    case 0: {
      this->destino.x = this->cuerpo.getPosition().x - 64;
      this->destino.y = this->cuerpo.getPosition().y;
      return;
    }
    case 1: {
      this->destino.x = this->cuerpo.getPosition().x + 64;
      this->destino.y = this->cuerpo.getPosition().y;
      return;
    }
    case 2: {
      this->destino.y = this->cuerpo.getPosition().y - 64;
      this->destino.x = this->cuerpo.getPosition().x;
      return;
    }
    case 3: {
      this->destino.y = this->cuerpo.getPosition().y + 64;
      this->destino.x = this->cuerpo.getPosition().x;
      return;
    }
  }
}

const sf::RectangleShape &Player::getCuerpo() const {
  return cuerpo;
}

const float Player::getVelocidad() const {
  return velocidad;
}

const bool Player::estaMuerto() const {
  return muerto;
}

