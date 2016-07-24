#include "TowerManager.h"

#include "Game.h"

TowerManager::~TowerManager(){
    for(TowerType* tt : _towerTypes){
        if(tt!=nullptr){
            if(tt->model != nullptr)
                delete tt->model;
            delete tt;
        }
    }
    _towerTypes.clear();
}

int TowerManager::getTowerCount() const{
    return _towerTypes.size();
}

TowerType* TowerManager::getTowerType(int id) const{
    for(TowerType* tt : _towerTypes)
        if(tt!=nullptr && tt->model!=nullptr && id==tt->model->getId())
            return tt;
    return nullptr;
}

int TowerManager::getTowerCost(int id) const{
    for(TowerType* tt : _towerTypes)
        if(tt!=nullptr && tt->model!=nullptr && id==tt->model->getId()){
            return tt->cost;
        }
    return 0;
}

Tower* TowerManager::parseEvent(sf::Event event) const{

}

sf::Vector2i TowerManager::getDrawRectSize() const{
    return sf::Vector2i(Game::pixelsPerSquare*2 + 40,
                       (Game::pixelsPerSquare+10)*(_towerTypes.size()/2 + (_towerTypes.size()%2!=0)) + 20); // 30 - (10 remaining)
}

void TowerManager::drawTowersPanel(sf::RenderWindow* window, sf::Vector2i point) const{
    sf::Vector2i size = getDrawRectSize();
    window->pushGLStates();
        sf::RectangleShape rect;
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(point.x, point.y);
        rect.setSize(sf::Vector2f(size.x, size.y));
        window->draw(rect);

        rect.setSize(sf::Vector2f(Game::pixelsPerSquare,Game::pixelsPerSquare));
        rect.setOutlineColor(sf::Color::Black);
        rect.setFillColor(sf::Color::Green);
        for(int i=0; i<_towerTypes.size(); i++){
            rect.setPosition(point.x + 15 + (i%2!=0? 10+Game::pixelsPerSquare:0),
                             point.y + 15 + (i/2)*(Game::pixelsPerSquare+10));
            window->draw(rect);
        }
    window->popGLStates();

    int i = 0;
    Vec2d p;
    for(TowerType* tt:_towerTypes){
        if(tt==nullptr || tt->model==nullptr)
            continue;
        p.x = point.x + 15 + Game::pixelsPerSquare/2 + (i%2!=0? 10+Game::pixelsPerSquare:0);
        p.y = point.y + 15 + Game::pixelsPerSquare/2 + (i/2)*(Game::pixelsPerSquare+10);

        tt->model->draw(window, p);
        tt->model->drawOver(window, p);

        ++i;
    }
}

