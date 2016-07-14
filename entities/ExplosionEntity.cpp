#include "ExplosionEntity.h"

#include "../Resources.h"
#include "../Sprite.h"
#include "../Game.h"
#include <SFML/OpenGL.hpp>

ExplosionEntity::ExplosionEntity(Vec2d position, double range, int ticksAlive){
    _position = position;
    _range = range;
    _ticksAlive = ticksAlive;
    _ticksLived = 0;
}

bool ExplosionEntity::tick(){
    return _ticksLived++ >= _ticksAlive;
}

void ExplosionEntity::draw(sf::RenderWindow* window) const{
    window->pushGLStates();
        Sprite sprite(Resources::explosion, 6,7, 37);
        sprite.setColor(sf::Color(255,255,255, 175));
        sprite.setFrame((_ticksLived*37)/_ticksAlive);
        sprite.scale(_range/sprite.getSize().x, _range/sprite.getSize().y);
        sprite.setPosition(_position.x-sprite.getSize().x/2, _position.y-sprite.getSize().y/2);
        window->draw(sprite);
        /*int frame = (_ticksLived*37)/_ticksAlive;
        sf::Sprite fire(Resources::explosion);
        fire.setColor(sf::Color(255,255,255, 175));
        fire.setTextureRect(sf::IntRect((frame%6)*100,((frame/6)%7)*100, 100,100));
        fire.scale(_range/100.0, _range/100.0);
        fire.setPosition(_position.x-fire.getGlobalBounds().width/2, _position.y-fire.getGlobalBounds().height/2);
        window->draw(fire);*/

    window->popGLStates();
}
