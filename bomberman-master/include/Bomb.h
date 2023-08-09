

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Bomba {
private:
    sf::Vector2i bombaPos;
    sf::Clock bombaTiempo;
    sf::Clock fuegoTiempo;

    int radio;
    bool limpiar;
    bool usado;

    void setFuego(TileMap* tileMap);
    void limpiarFuego(TileMap* tileMap);

public:
    Bomba(int radio);

    void ponerBomba(sf::Vector2i bombPos, TileMap* tileMap);
    void check(TileMap* tileMap);

    bool esUsado() const;
};


#endif
