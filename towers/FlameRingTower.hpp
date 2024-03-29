#ifndef FLAMERINGTOWER_H
#define FLAMERINGTOWER_H

#include <SFML/Graphics.hpp>

#include "../Game.hpp"
#include "../Tower.hpp"

class FlameRingTower : public Tower{
    double _ringVelocity;
    double _ringSize;
    double _ringActualRange;

    double _damage;

public:

    static int id;

    FlameRingTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;

    virtual std::unique_ptr<Tower> clone() const;
};

#endif // FLAMERINGTOWER_H
