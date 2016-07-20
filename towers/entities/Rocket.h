#ifndef ROCKET_H
#define ROCKET_H

#include "../../Entity.h"
#include "../../Vec.hpp"
#include "../../Enemy.h"

class Rocket : public Entity{

    Vec2d _position;

    Enemy* _targetEnemy;
    Vec2d _targetPosition;

    double _damage;
    double _explosionRange;
    double _velocity;
    double _distanceTraveled;
    double _maxDistance;
    bool _hitEnemiesInPath;

public:
    Rocket(Enemy* target, double damage, double explosionRange,
           double velocity, double maxDistance,
           bool hitEnemiesInPath, Vec2d position);
    Rocket(Vec2d target, double damage, double explosionRange,
           double velocity, double maxDistance,
           bool hitEnemiesInPath, Vec2d position);

    void damageEnemies() const;

    virtual bool tick();
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // ROCKET_H
