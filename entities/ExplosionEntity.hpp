#ifndef EXPLOSIONENTITY_H
#define EXPLOSIONENTITY_H

#include <SFML/Graphics.hpp>

#include "../Sprite.hpp"
#include "../Vec.hpp"
#include "../Entity.hpp"

class ExplosionEntity : public Entity {
    Vec2d _position;
    double _range;
    int _ticksAlive;
    int _ticksLived;

    Sprite _sprite;

public:
    ExplosionEntity(Vec2d position, double range, int ticksAlive);

    virtual bool tick();
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // EXPLOSIONENTITY_H
