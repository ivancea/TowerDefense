#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Vec.hpp"

class Enemy{

protected:
    double _life;
    double _velocity;
    Vec2d _position;
    double _damage;
    int _nextPositionIndex;

public:
    virtual ~Enemy(){}

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const = 0;

    virtual bool damage(double n);

    double getLife() const { return _life ; }
    double getVelocity() const { return _velocity; }
    Vec2d getPosition() const { return _position; }
    double getDamage() const { return _damage; }
    int getNextPositionIndex() const { return _nextPositionIndex; }

    virtual double getDistanceToNextPosition() const;
};

#endif // ENEMY_H
