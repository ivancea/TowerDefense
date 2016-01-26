#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include "Vec.hpp"

class Enemy{
    int _nextPositionIndex;
=======

#include "Vec.hpp"

class Enemy{
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178

protected:
    double _life;
    double _velocity;
    Vec2d _position;
    double _damage;
<<<<<<< HEAD
    double _distanceToEnd;

    void reloadDistanceToEnd();

public:
    Enemy(int nextPositionIndex);
=======
    int _nextPositionIndex;

public:
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    virtual ~Enemy(){}

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const = 0;

    virtual bool damage(double n);

    double getLife() const { return _life ; }
    double getVelocity() const { return _velocity; }
    Vec2d getPosition() const { return _position; }
    double getDamage() const { return _damage; }
    int getNextPositionIndex() const { return _nextPositionIndex; }
<<<<<<< HEAD
    int setNextPositionIndex(int nextPositionIndex);

    double getDistanceToNextPosition() const;
    double getDistanceToEnd() const;
=======

    virtual double getDistanceToNextPosition() const;
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
};

#endif // ENEMY_H
