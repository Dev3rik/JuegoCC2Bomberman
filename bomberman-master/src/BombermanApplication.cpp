

#include "BombermanApplication.h"

void BombermanAplicacion::inicVentana() {
  this->gameState = MENU;

  std::ifstream configFile(RESOURCE_PATH(configFile.json));

  nlohmann::json j;
  configFile >> j;
  configFile.close();

    Config::iniciar(j);

  const Config& config = Config::getConfig();

  const VentanaConfig& windowConfig = config.getVentanaConfig();
  sf::VideoMode windowBounds(windowConfig.getAncho(), windowConfig.getAlto());

  this->ventana = new sf::RenderWindow(windowBounds, windowConfig.getTitulo());
  this->ventana->setFramerateLimit(windowConfig.getFrameLimite());
  this->ventana->setVerticalSyncEnabled(windowConfig.esVerticalSyncEnable());
  this->deltaTime = 0.0f;
}

void BombermanAplicacion::inicMapa() {
  this->mapa = new TileMap();
  this->mapa->capas.push_back(new Capa);
  this->mapa->capas.push_back(new Capa);
}

void BombermanAplicacion::inicPlayers() {
  this->players.push_back(new Player(RESOURCE_PATH(player0.png), sf::Vector2f(64.0f, 128.0f), sf::Vector2f(11 * 64 + 32, 1 * 64 + 32), sf::Vector2u(8, 3), 0.1f, 4.0f, new Player1Inputer, 4));
  this->players.push_back(new Player(RESOURCE_PATH(player1.png), sf::Vector2f(64.0f, 64.0f), sf::Vector2f(1 * 64 + 32, 11 * 64 + 32), sf::Vector2u(6, 3), 0.1f, 4.0f, new Player2Inputer, 4));
}

void BombermanAplicacion::inicMenu() {
    this->menu.iniciar(this->ventana->getSize());
}

BombermanAplicacion::BombermanAplicacion() {
    this->inicVentana();
    this->inicMapa();
    this->inicPlayers();
    this->inicMenu();

  std::cout << *this;
}

BombermanAplicacion::~BombermanAplicacion() {
  delete this->ventana;
  delete this->mapa;

  for (int i = 0; i < players.size(); i++) {
    delete this->players[i];
  }
}

void BombermanAplicacion::run() {
  while (this->ventana->isOpen()) {
    this->deltaTime = this->tiempo.restart().asSeconds();
    this->update();
    this->render();
  }
}

void BombermanAplicacion::update() {
  sf::Event event;
  while (this->ventana->pollEvent(event)) {
    if (event.Event::type == sf::Event::Closed) {
      this->ventana->close();
    } else if (event.type == event.Event::KeyPressed && (this->gameState == MENU || this->gameState == GAME_OVER)) {
      switch (event.key.code) {
        case sf::Keyboard::Escape:
          this->ventana->close();
          break;
        case sf::Keyboard::Up:
          this->menu.update(1);
          break;
        case sf::Keyboard::Down:
          this->menu.update(-1);
          break;
        case sf::Keyboard::Enter:
          if (this->gameState == GAME_OVER) {
            this->gameState = MENU;
            this->restart();
          } else if (this->menu.getItemSeleccionado() == 0) {
            this->gameState = RUN;
          } else if (this->menu.getItemSeleccionado() == 1) {
            this->ventana->close();
          }
          break;
        default: break;
      }
    }
  }

  if (this->gameState == RUN) {
    for (int i = 0; i < players.size(); i++) {
      this->players[i]->update(this->deltaTime, this->mapa);

      if (this->players[i]->estaMuerto()) {
        this->gameState = GAME_OVER;
        break;
      }
    }
  }
}

void BombermanAplicacion::restart() {
  delete this->mapa;

  for (int i = 0; i < players.size(); i++) {
    delete this->players[i];
  }

  this->players.clear();

    this->inicMapa();
    this->inicPlayers();

    this->menu.resetItemSeleccionado();
}

void BombermanAplicacion::render() {
  this->ventana->clear();

  if (this->gameState == MENU) {
    this->ventana->draw(this->menu);
  } else if (this->gameState == RUN || this->gameState == GAME_OVER) {
    this->ventana->draw(*this->mapa);
    for (auto& p : this->players) {
      this->ventana->draw(*p);
    }

    if (this->gameState == GAME_OVER) {
      this->menu.drawGameOver(this->ventana);
    }
  }

  this->ventana->display();
}

std::ostream& operator<<(std::ostream& os, const BombermanAplicacion& aplicacion)
{
  for (auto& p : aplicacion.players) {
    os
    << "-----------Player-----------\n"
    << "Speed: "
    << p->getVelocidad()
    << "\n"
    << "Position: X: "
    << p->getCuerpo().getPosition().x
    << " Y: "
    << p->getCuerpo().getPosition().y
    << "\n";
  }

  return os;
}
