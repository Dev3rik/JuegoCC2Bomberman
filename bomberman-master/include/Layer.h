

#ifndef BOMBERMAN_LAYER_H
#define BOMBERMAN_LAYER_H

#include <SFML/Graphics.hpp>
#include <Config.h>

class MapIterator {
private:
    const std::vector<int>& mapaArray;
    int currentIndex;
    int totalElements;

public:
    MapIterator(const std::vector<int>& mapaArray, int totalElements)
            : mapaArray(mapaArray), currentIndex(0), totalElements(totalElements) {}

    bool hasNext() {
        return currentIndex < totalElements;
    }

    int next() {
        int element = mapaArray[currentIndex];
        currentIndex++;
        return element;
    }

    int getCurrentIndex() const {
        return currentIndex;
    }
};

class Capa : public sf::Drawable {

private:
    sf::Texture tileSet;
    sf::VertexArray vertexArray;

    unsigned anchoMapa;
    unsigned altoMapa;
    unsigned tileSize;

public:
    std::vector<int> mapaArray;
    Capa();
    Capa(const Capa& layer);
    MapIterator createIterator();
    void update();
    virtual void draw(sf::RenderTarget& objetivo, sf::RenderStates estados) const;
};


#endif //