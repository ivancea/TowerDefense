#ifndef SHOTGUNTOWER_H
#define SHOTGUNTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.hpp"
#include "../Tower.hpp"
#include "entities/Bullet.hpp"

class ShotgunTower : public Tower {
    double _damage;
    double _bulletVelocity;

    double _maxBulletDistance;

public:

    static int id;

    ShotgunTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;

    virtual std::unique_ptr<Tower> clone() const;
};

#endif // SHOTGUNTOWER_H
