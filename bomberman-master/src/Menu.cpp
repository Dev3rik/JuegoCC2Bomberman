

#include "Menu.h"

void Menu::iniciar(sf::Vector2u windowSize) {
    this->itemSeleccionado = 0;
    this->texturaBackground.loadFromFile(RESOURCE_PATH(background.png));
    this->background.setTexture(this->texturaBackground);
    this->background.setScale((float) windowSize.x / this->texturaBackground.getSize().x,
                              (float) windowSize.y / this->texturaBackground.getSize().y);

    this->fuente.loadFromFile(RESOURCE_PATH(ARCADECLASSIC.TTF));

    this->agregarBoton("Jugar", 100, (float) windowSize.x / 2.f, (float) windowSize.y / 2.f + 100.f);
    this->agregarBoton("Salir", 100, (float) windowSize.x / 2.f, (float) windowSize.y / 2.f + 200.f);
    this->agregarBoton("GAME OVER", 100, (float) windowSize.x / 2.f, (float) windowSize.y / 2.f);
    this->agregarBoton("Presiona  Enter", 30, (float) windowSize.x / 2.f, (float) windowSize.y / 2.f + 70.f);

    this->buttons[this->itemSeleccionado].setFillColor(sf::Color::Red);
}

void Menu::agregarBoton(const std::string nombre, unsigned int tamanho, float posX, float posY) {
    sf::Text button;
    button.setFont(this->fuente);
    button.setString(nombre);
    button.setCharacterSize(tamanho);
    button.setOrigin(button.getLocalBounds().left + button.getLocalBounds().width / 2.0f,
                     button.getLocalBounds().top + button.getLocalBounds().height / 2.0f);
    button.setPosition(posX, posY);
    this->buttons.push_back(button);
}

void Menu::update(int key) {
    this->buttons[this->itemSeleccionado].setFillColor(sf::Color::White);

    int buttonsSize = this->buttons.size() - 2;

    if (this->itemSeleccionado - key >= buttonsSize) {
        this->itemSeleccionado = 0;
    } else if (this->itemSeleccionado - key < 0) {
        this->itemSeleccionado = buttonsSize - 1;
    } else {
        this->itemSeleccionado -= key;
    }

    this->buttons[this->itemSeleccionado].setFillColor(sf::Color::Red);
}


void Menu::draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const {
    objetivo.draw(this->background);

    for (int i = 0; i < this->buttons.size() - 2; i++) {
        objetivo.draw(this->buttons[i]);
    }
}

void Menu::drawGameOver(sf::RenderTarget *objetivo) {
    objetivo->draw(this->buttons[2]);
    objetivo->draw(this->buttons[3]);
}

void Menu::resetItemSeleccionado() {
    this->buttons[this->itemSeleccionado].setFillColor(sf::Color::White);
    this->itemSeleccionado = 0;
    this->buttons[this->itemSeleccionado].setFillColor(sf::Color::Red);
}

const int Menu::getItemSeleccionado() const {
    return itemSeleccionado;
}

