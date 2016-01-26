#ifndef SOLDIERTOWER_H
#define SOLDIERTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"
#include "entities/Bullet.h"

class SoldierTower : public Tower{
    int _ticksForShoot;
    int _ticksBetweenShoots;
    double _damage;
    double _bulletVelocity;

    double _maxBulletDistance;

    std::list<Bullet*> _bullets;

public:
    SoldierTower(int id);
    ~SoldierTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // SOLDIERTOWER_H
