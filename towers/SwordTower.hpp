#ifndef SWORDTOWER_H
#define SWORDTOWER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../Game.hpp"
#include "../Tower.hpp"

class SwordTower : public Tower {
    double _damage;

    double _swordLength;
    double _swordWidth;
    double _swordAngle;

public:

    static int id;

    SwordTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;
    virtual void drawOver(sf::RenderWindow* window, Vec2d point) const;

    virtual std::unique_ptr<Tower> clone() const;
};

#endif // SWORDTOWER_H
