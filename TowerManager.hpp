#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

class TowerManager;

#include <list>
#include <SFML/Graphics.hpp>

#include "TowerType.hpp"

class TowerManager{

protected:
    std::list<std::unique_ptr<TowerType>> _towerTypes;

public:
    virtual ~TowerManager();

    int getTowerCount() const;

    virtual TowerType* getTowerType(int id) const;
    virtual int getTowerCost(int id) const;

    virtual TowerType* parseEvent(sf::Event event, Vec2i mouse, sf::Vector2i point) const;
    virtual sf::Vector2i getDrawRectSize() const;
    virtual void drawTowersPanel(sf::RenderWindow* window, sf::Vector2i point) const;
};

#endif // TOWERMANAGER_H
