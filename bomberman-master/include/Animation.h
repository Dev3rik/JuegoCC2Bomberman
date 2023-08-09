

#ifndef BOMBERMAN_ANIMATION_H
#define BOMBERMAN_ANIMATION_H

#include <SFML/Graphics.hpp>

class Animacion {
private:
    sf::Vector2u ContadorImagen;
    sf::Vector2u imagenActual;
    sf::Texture textura;
    sf::IntRect uvRect;

    float tiempoTotal;
    float cambiarTiempo;

public:
    Animacion(const std::string& textura, sf::Vector2u ContadorImagen, float cambiarTiempo);

    void update(int fila, float deltaTime, bool faceRight);

    const sf::Texture &getTextura() const;
    const sf::IntRect &getUvRect() const;
};


#endif
