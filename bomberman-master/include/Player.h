

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Inputer.h"
#include "Bomb.h"
#include "TileMap.h"

class Player : public sf::Drawable {
private:
    sf::RectangleShape cuerpo;
    Animacion animacion;
    Inputer *inputer;
    Bomba bomba;

    sf::Vector2f playerPos;
    sf::Vector2f destino;

    int direccion;
    unsigned fila;

    float velocidad;

    bool enMovimiento;
    bool faceRight;
    bool muerto;

    sf::Vector2f direccionEnPaso(int dir);

    const bool checkColision(const std::vector<int> &mapa) const;

    const bool checkMuerte(const std::vector<int> &mapa) const;

public:
    Player(const std::string &textura, sf::Vector2f playerTamanho, sf::Vector2f playerPos, sf::Vector2u imageContador,
           float cambiarTiempo, float velocidad, Inputer *inputer, int radio);

    virtual ~Player();

    void update(float deltaTime, TileMap *tileMap);

    virtual void draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const;

    const float getVelocidad() const;

    const sf::RectangleShape &getCuerpo() const;

    const bool estaMuerto() const;
};

#endif