#ifndef ROCKETTOWER_H
#define ROCKETTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"
#include "entities/Rocket.h"

class RocketTower : public Tower{
    double _damage;
    double _explosionRange;
    double _rocketVelocity;

    double _maxRocketDistance;

    bool _followEnemy;
    bool _hitEnemiesInPath;

public:

    static int id;

    RocketTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;

    virtual Tower* clone() const;
};

#endif // ROCKETTOWER_H
