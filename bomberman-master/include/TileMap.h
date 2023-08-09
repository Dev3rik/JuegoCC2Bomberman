

#ifndef BOMBERMAN_TILEMAP_H
#define BOMBERMAN_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Layer.h"

class TileMap : public sf::Drawable {
public:
    std::vector<Capa*> capas;

    virtual ~TileMap();
    virtual void draw(sf::RenderTarget& objetivo, sf::RenderStates estados) const;
};


#endif
