#ifndef FLAMERING_H
#define FLAMERING_H

#include"../../Entity.h"
#include "../../Vec.hpp"
#include "../../Enemy.h"

class FlameRing : public Entity{

    Vec2d _position;

    double _damage;
    double _maxRadius;
    double _velocity;
    double _actualRadius;
    double _ringSize;

public:
    FlameRing(Vec2d position, double ringSize,
              double damage, double velocity,
              double maxRadius, double initialRadius);

    virtual bool tick();
    virtual void drawOver(sf::RenderWindow* window) const;
};

#endif // FLAMERING_H
