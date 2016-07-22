#ifndef SNIPERTOWER_H
#define SNIPERTOWER_H

#include <SFML/Graphics.hpp>

#include "../Vec.hpp"
#include "../sprite.h"
#include "../Game.h"
#include "../Tower.h"

class SniperTower : public Tower{
    double _damage;

    Sprite _spriteBase,
           _spriteCanon;

public:

    static int id;

    SniperTower();

    virtual void setPosition(Vec2i position);

    virtual TowerEvent tick();
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;
    virtual Tower* clone() const;
};

#endif // SNIPERTOWER_H
