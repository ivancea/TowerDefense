#ifndef BULLET_H
#define BULLET_H

#include "../../Vec.hpp"
#include "../../Enemy.h"

class Bullet{

    Vec2d _position;

    Vec2d _target;

    double _damage;
    double _velocity;

public:
    Bullet(Vec2d target, double damage,
           double velocity, Vec2d position);

    bool tick();
    void draw(sf::RenderWindow* window) const;
};

#endif // BULLET_H
