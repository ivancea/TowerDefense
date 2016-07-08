#ifndef INHIBITORENEMY_H
#define INHIBITORENEMY_H

#include "Enemy.h"
#include "Tower.h"

class InhibitorEnemy : public Enemy{

    int _inhibitionTicks;
    Tower* _target;

public:
    InhibitorEnemy(double velocity, double life, double damage);

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const;
};

#endif // INHIBITORENEMY_H
