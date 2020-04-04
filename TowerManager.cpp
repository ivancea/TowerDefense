#include "TowerManager.hpp"

#include <vector>

#include "Game.hpp"

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

TowerType* TowerManager::parseEvent(sf::Event event, Vec2i mouse, sf::Vector2i point) const{
    static const std::vector<sf::Keyboard::Key> bindings({
        sf::Keyboard::Q,sf::Keyboard::W,sf::Keyboard::E,sf::Keyboard::R,
        sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D,sf::Keyboard::F
    });

    if(_towerTypes.size()==0)
        return nullptr;
    Vec2d p(point.x + 15, point.y + 15);
    Vec2i t;
    switch(event.type){
    case sf::Event::MouseMoved:
        t.x = (mouse.x-p.x)/(10+Game::pixelsPerSquare);
        t.y = (mouse.y-p.y)/(10+Game::pixelsPerSquare);
        if(mouse.x>=p.x && mouse.y>=p.y && t.x<=1 && t.y<=(_towerTypes.size()-1)/2
        && mouse.x-p.x-t.x*(10+Game::pixelsPerSquare) <= Game::pixelsPerSquare
        && mouse.y-p.y-t.y*(10+Game::pixelsPerSquare) <= Game::pixelsPerSquare
        && t.y*2 + t.x < _towerTypes.size()){
            auto it = _towerTypes.begin();
            for(int i = t.y*2 + t.x; i>0; i--)
                it++;
            return *it;
        }
    case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Left){
            t.x = (mouse.x-p.x)/(10+Game::pixelsPerSquare);
            t.y = (mouse.y-p.y)/(10+Game::pixelsPerSquare);
            if(mouse.x>=p.x && mouse.y>=p.y && t.x<=1 && t.y<=(_towerTypes.size()-1)/2
            && mouse.x-p.x-t.x*(10+Game::pixelsPerSquare) <= Game::pixelsPerSquare
            && mouse.y-p.y-t.y*(10+Game::pixelsPerSquare) <= Game::pixelsPerSquare
            && t.y*2 + t.x < _towerTypes.size()){
                auto it = _towerTypes.begin();
                for(int i = t.y*2 + t.x; i>0; i--)
                    it++;
                return *it;
            }
        }
        break;
    case sf::Event::KeyPressed:
        for(int i=0; i<bindings.size(); i++)
            if(bindings[i] == event.key.code){
                if(i<_towerTypes.size()){
                    auto it = _towerTypes.begin();
                    while(i-->0)
                        ++it;
                    return *it;
                }
                break;
            }
        break;
    default:
        break;
    }

    return nullptr;
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
        p.x = point.x + 15 + Game::pixelsPerSquare/2 + (i%2)*(10+Game::pixelsPerSquare);
        p.y = point.y + 15 + Game::pixelsPerSquare/2 + (i/2)*(Game::pixelsPerSquare+10);

        tt->model->draw(window, p);
        tt->model->drawOver(window, p);

        ++i;
    }
}

