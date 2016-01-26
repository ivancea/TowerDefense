#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Vec.hpp"

class Enemy{
    int _nextPositionIndex;

protected:
    double _life;
    double _velocity;
    Vec2d _position;
    double _damage;
    double _distanceToEnd;

    void reloadDistanceToEnd();

public:
    Enemy(int nextPositionIndex);
    virtual ~Enemy(){}

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const = 0;

    virtual bool damage(double n);

    double getLife() const { return _life ; }
    double getVelocity() const { return _velocity; }
    Vec2d getPosition() const { return _position; }
    double getDamage() const { return _damage; }
    int getNextPositionIndex() const { return _nextPositionIndex; }
    int setNextPositionIndex(int nextPositionIndex);

    double getDistanceToNextPosition() const;
    double getDistanceToEnd() const;
};

#endif // ENEMY_H
