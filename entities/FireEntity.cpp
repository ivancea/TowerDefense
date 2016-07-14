#include "FireEntity.h"

#include "../Resources.h"
#include "../Game.h"
#include <SFML/OpenGL.hpp>

FireEntity::FireEntity(Vec2d position, int ticksAlive){
    _position = position;
    _ticksAlive = ticksAlive;
    _ticksLived = 0;
    _spriteFrame = 0;
}

bool FireEntity::tick(){
    return _ticksLived++ >= _ticksAlive;
}

void FireEntity::draw(sf::RenderWindow* window) const{
    window->pushGLStates();

        sf::Sprite fire(Resources::fire);
        fire.setColor(sf::Color(255,255,255, 175));
        fire.setPosition(_position.x-32, _position.y-100);
        fire.setTextureRect(sf::IntRect((_spriteFrame%8)*64,((_spriteFrame/8)%4)*128, 64,128));

        ++const_cast<int&>(_spriteFrame);
        window->draw(fire);

    window->popGLStates();
}
