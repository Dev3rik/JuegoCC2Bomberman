

#include "Animation.h"

Animacion::Animacion(const std::string& textura, sf::Vector2u ContadorImagen, float cambiarTiempo) {
  this->textura.loadFromFile(textura);

  this->ContadorImagen = ContadorImagen;
  this->cambiarTiempo = cambiarTiempo;
  this->tiempoTotal = 0.0f;
  this->imagenActual.x = 0;

  this->uvRect.width = this->textura.getSize().x / float(ContadorImagen.x);
  this->uvRect.height = this->textura.getSize().y / float(ContadorImagen.y);
}

void Animacion::update(int fila, float deltaTime, bool faceRight) {
  this->imagenActual.y = fila;
  this->tiempoTotal += deltaTime;

  if (this->tiempoTotal >= this->cambiarTiempo) {
    this->tiempoTotal -= this->cambiarTiempo;
    this->imagenActual.x++;

    if (this->imagenActual.x >= this->ContadorImagen.x) {
      this->imagenActual.x = 0;
    }
  }

  this->uvRect.top = this->imagenActual.y * this->uvRect.height;

  if (fila == 2 && !faceRight) {
    this->uvRect.left = (this->imagenActual.x + 1) * abs(this->uvRect.width);
    this->uvRect.width = -abs(this->uvRect.width);
  } else {
    this->uvRect.left = this->imagenActual.x * abs(this->uvRect.width);
    this->uvRect.width = abs(this->uvRect.width);
  }
}

const sf::Texture &Animacion::getTextura() const {
  return textura;
}

const sf::IntRect &Animacion::getUvRect() const {
  return uvRect;
}

