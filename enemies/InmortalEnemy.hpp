#ifndef INMORTALENEMY_H
#define INMORTALENEMY_H

#include "../Enemy.hpp"

class InmortalEnemy : public Enemy{
public:
    InmortalEnemy(double velocity, double damage);

    virtual bool damage(double n);

    virtual void draw(sf::RenderWindow* window) const;
};

#endif // INMORTALENEMY_H
