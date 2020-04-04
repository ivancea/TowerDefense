#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "../Enemy.hpp"

class BasicEnemy : public Enemy{
public:
    BasicEnemy(double velocity, double life, double damage);

    virtual void killed();
    virtual void draw(sf::RenderWindow* window) const;
};

#endif // BASICENEMY_H
