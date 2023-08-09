

#include "Layer.h"


Capa::Capa() {
  const MapaConfig &map = Config::getConfig().getMapa();
  this->mapaArray = map.getData();
  this->anchoMapa = map.getAncho();
  this->altoMapa = map.getAlto();
  this->tileSize = map.getTileSize();

  this->tileSet.loadFromFile(RESOURCE_PATH(mapTile.png));

  this->vertexArray.setPrimitiveType(sf::Quads);
  this->vertexArray.resize(map.getAncho() * map.getAlto() * 4);
  this->update();
}



Capa::Capa(const Capa &layer) {
  this->tileSet = layer.tileSet;
  this->vertexArray = layer.vertexArray;
  this->mapaArray = layer.mapaArray;
}
MapIterator Capa::createIterator(){
    return MapIterator(this->mapaArray, this->anchoMapa * this->altoMapa);
}

void Capa::update() {
    MapIterator iterator = createIterator();
    while (iterator.hasNext()) {
        int tileNumber = iterator.next();

        int tu = tileNumber % (this->tileSet.getSize().x / this->tileSize);
        int tv = tileNumber / (this->tileSet.getSize().x / this->tileSize);

        sf::Vertex *quad = &(this->vertexArray)[(iterator.getCurrentIndex() - 1) * 4];

        quad[0].position = sf::Vector2f((iterator.getCurrentIndex() - 1) % this->anchoMapa * this->tileSize, (iterator.getCurrentIndex() - 1) / this->anchoMapa * this->tileSize);
        quad[1].position = sf::Vector2f((iterator.getCurrentIndex() - 1) % this->anchoMapa * this->tileSize + this->tileSize, (iterator.getCurrentIndex() - 1) / this->anchoMapa * this->tileSize);
        quad[2].position = sf::Vector2f((iterator.getCurrentIndex() - 1) % this->anchoMapa * this->tileSize + this->tileSize, (iterator.getCurrentIndex() - 1) / this->anchoMapa * this->tileSize + this->tileSize);
        quad[3].position = sf::Vector2f((iterator.getCurrentIndex() - 1) % this->anchoMapa * this->tileSize, (iterator.getCurrentIndex() - 1) / this->anchoMapa * this->tileSize + this->tileSize);

        quad[0].texCoords = sf::Vector2f(tu * this->tileSize, tv * this->tileSize);
        quad[1].texCoords = sf::Vector2f((tu + 1) * this->tileSize, tv * this->tileSize);
        quad[2].texCoords = sf::Vector2f((tu + 1) * this->tileSize, (tv + 1) * this->tileSize);
        quad[3].texCoords = sf::Vector2f(tu * this->tileSize, (tv + 1) * this->tileSize);
    }
}
void Capa::draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const {
    estados.texture = &this->tileSet;
  objetivo.draw(this->vertexArray, estados);
}
