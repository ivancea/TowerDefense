#ifndef SNIPERTOWER_H
#define SNIPERTOWER_H

#include <SFML/Graphics.hpp>

#include "../Vec.hpp"
#include "../sprite.hpp"
#include "../Game.hpp"
#include "../Tower.hpp"

class SniperTower : public Tower{
    double _damage;

    Sprite _spriteBase,
           _spriteCanon;

public:

    static int id;

    SniperTower();

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window, Vec2d point) const;
    virtual void drawOver(sf::RenderWindow* window, Vec2d point) const;

    virtual Tower* clone() const;
};

#endif // SNIPERTOWER_H
