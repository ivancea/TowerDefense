#ifndef SNIPERTOWER_H
#define SNIPERTOWER_H

#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"

class SniperTower : public Tower{
    double _damage;

public:
    SniperTower(int id);

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
};

#endif // SNIPERTOWER_H
