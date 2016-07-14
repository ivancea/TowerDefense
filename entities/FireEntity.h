#ifndef FIREENTITY_H
#define FIREENTITY_H

#include <SFML/Graphics.hpp>

#include "../Vec.hpp"
#include "../entity.h"

class FireEntity : public Entity {
    Vec2d _position;
    int _ticksAlive;
    int _ticksLived;
    int _spriteFrame;

public:
    FireEntity(Vec2d position, int ticksAlive);

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const;
};

#endif // FIREENTITY_H
