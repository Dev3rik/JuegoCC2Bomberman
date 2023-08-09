
#ifndef BOMBERMAN_BOMBERMANAPPLICATION_H
#define BOMBERMAN_BOMBERMANAPPLICATION_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "TileMap.h"
#include "Player.h"
#include "Player1Inputer.h"
#include "Player2Inputer.h"
#include "Menu.h"

enum GAME_STATE {
    MENU = 0,
    RUN,
    GAME_OVER
};

class BombermanAplicacion {
private:
    sf::RenderWindow* ventana;
    Menu menu;
    TileMap* mapa;
    std::vector<Player*> players;

    GAME_STATE gameState;

    float deltaTime;
    sf::Clock tiempo;

    void inicVentana();
    void inicMapa();
    void inicPlayers();
    void inicMenu();

    void update();
    void render();
    void restart();

    friend std::ostream& operator<<(std::ostream& os, const BombermanAplicacion& aplicacion);

public:
    BombermanAplicacion();
    virtual ~BombermanAplicacion();

    void run();
};


#endif
