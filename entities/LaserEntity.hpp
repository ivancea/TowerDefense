#ifndef LASERENTITY_H
#define LASERENTITY_H

#include <SFML/Graphics.hpp>

#include "../Vec.hpp"
#include "../entity.hpp"

class LaserEntity : public Entity {
    Vec2d _from, _to;
    int _ticksRemaining;

public:
    LaserEntity(Vec2d from, Vec2d to, int ticks);

    virtual bool tick();
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // LASERENTITY_H
