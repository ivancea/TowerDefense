#include "Tower.hpp"

#include "Game.hpp"

Tower::Tower():_priority(Default){}

void Tower::draw(sf::RenderWindow* window) const {
    draw(window, Game::getRealPosition(_position));
}

void Tower::drawOver(sf::RenderWindow* window) const {
    drawOver(window, Game::getRealPosition(_position));
}
