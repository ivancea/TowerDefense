#include "ExplosionEntity.hpp"

#include "../Resources.hpp"
#include "../Sprite.hpp"
#include "../Game.hpp"
#include <SFML/OpenGL.hpp>

ExplosionEntity::ExplosionEntity(Vec2d position, double range, int ticksAlive)
:_sprite(*Resources::getTexture("sprites/explosion.png"), 6,7, 37){
    _position = position;
    _range = range;
    _ticksAlive = ticksAlive;
    _ticksLived = 0;

    _sprite.setColor(sf::Color(255,255,255, 175));
    _sprite.scale(_range/_sprite.getSize().x, _range/_sprite.getSize().y);
    _sprite.setPosition(_position.x-_sprite.getSize().x/2, _position.y-_sprite.getSize().y/2);
}

bool ExplosionEntity::tick(){
    _sprite.setFrame((_ticksLived*37)/_ticksAlive);
    return _ticksLived++ >= _ticksAlive;
}

void ExplosionEntity::drawOver(sf::RenderWindow* window) const{
    window->pushGLStates();

        window->draw(_sprite);

    window->popGLStates();
}
