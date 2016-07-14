#include "FireEntity.h"

#include "../Resources.h"
#include "../Game.h"
#include <SFML/OpenGL.hpp>

FireEntity::FireEntity(Vec2d position, int ticksAlive)
:_sprite(Resources::fire, 8,4){
    _position = position;
    _ticksAlive = ticksAlive;
    _ticksLived = 0;

    _sprite.setColor(sf::Color(255,255,255, 175));
    _sprite.setPosition(_position.x-32, _position.y-100);
}

bool FireEntity::tick(){
    _sprite.nextFrame();
    return _ticksLived++ >= _ticksAlive;
}

void FireEntity::draw(sf::RenderWindow* window) const{
    window->pushGLStates();

        window->draw(_sprite);

    window->popGLStates();
}
