#ifndef BULLET_H
#define BULLET_H

#include "../../Entity.h"
#include "../../Vec.hpp"
#include "../../Enemy.h"

class Bullet : public Entity{

    Vec2d _position;

    Vec2d _target;

    double _damage;
    double _velocity;

public:
    Bullet(Vec2d target, double damage,
           double velocity, Vec2d position);

    virtual bool tick();
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // BULLET_H
