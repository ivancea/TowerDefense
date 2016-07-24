#ifndef SOLDIERTOWER_H
#define SOLDIERTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Tower.h"
#include "entities/Bullet.h"

class SoldierTower : public Tower{
    double _damage;
    double _bulletVelocity;

    double _maxBulletDistance;

public:

    static int id;

    SoldierTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;

    virtual Tower* clone() const;
};

#endif // SOLDIERTOWER_H
