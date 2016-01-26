#ifndef ROCKETTOWER_H
#define ROCKETTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"
#include "entities/Rocket.h"

class RocketTower : public Tower{
    int _ticksForShoot;
    int _ticksBetweenShoots;
    double _damage;
    double _explosionRange;
    double _rocketVelocity; // If followEnemy is active

    double _maxRocketDistance;

    bool _followEnemy;
    bool _hitEnemiesInPath;

    std::list<Rocket*> _rockets;

public:
    RocketTower(int id);
    ~RocketTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // ROCKETTOWER_H
