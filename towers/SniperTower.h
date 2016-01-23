#ifndef SNIPERTOWER_H
#define SNIPERTOWER_H

#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"

class SniperTower : public Tower{
    int _ticksForShoot;
    int _ticksBetweenShoots;
    double _damage;

    Vec2d _lastShootPosition;

public:
    SniperTower(int id);

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // SNIPERTOWER_H
