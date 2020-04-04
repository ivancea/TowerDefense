#ifndef FIREENTITY_H
#define FIREENTITY_H

#include <SFML/Graphics.hpp>

#include "../Sprite.hpp"
#include "../Vec.hpp"
#include "../entity.hpp"

class FireEntity : public Entity {
    Vec2d _position;
    int _ticksAlive;
    int _ticksLived;

    Sprite _sprite;

public:
    FireEntity(Vec2d position, int ticksAlive);

    virtual bool tick();
    virtual void draw(sf::RenderWindow* window) const;
};

#endif // FIREENTITY_H
