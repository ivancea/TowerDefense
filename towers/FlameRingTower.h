#ifndef FLAMERINGTOWER_H
#define FLAMERINGTOWER_H

#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"

class FlameRingTower : public Tower{
    double _ringVelocity;
    double _ringSize;
    double _ringActualRange;

    double _damage;

public:

    static int id;

    FlameRingTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // FLAMERINGTOWER_H
