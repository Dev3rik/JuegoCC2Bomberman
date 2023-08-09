

#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H

#include <SFML/Graphics.hpp>
#include "Config.h"

class Menu : public sf::Drawable {
private:
    sf::Font fuente;
    sf::Texture texturaBackground;
    sf::Sprite background;
    std::vector<sf::Text> buttons;
    int itemSeleccionado;

    void agregarBoton(const std::string nombre, unsigned tamanho, float posX, float posY);

public:
    void iniciar(sf::Vector2u windowSize);
    void update(int key);
    void resetItemSeleccionado();

    virtual void draw(sf::RenderTarget& objetivo, sf::RenderStates estados) const;
    void drawGameOver(sf::RenderTarget* objetivo);

    const int getItemSeleccionado() const;
};


#endif
