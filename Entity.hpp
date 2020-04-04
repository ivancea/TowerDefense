#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity{

public:
    virtual ~Entity(){}

    virtual bool tick() = 0;
    virtual void draw(sf::RenderWindow* window) const {};
    virtual void drawOver(sf::RenderWindow* window) const {};
};

#endif // ENTITY_H
