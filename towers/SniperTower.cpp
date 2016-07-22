#include "SniperTower.h"

#include <cmath>

#include <SFML/OpenGL.hpp>

#include "../Resources.h"
#include "../entities/LaserEntity.h"
#include "../entities/FireEntity.h"

int SniperTower::id = -1;

SniperTower::SniperTower()
:_spriteBase(*Resources::getTexture("sprites/sniperTower.png"), sf::IntRect(0,0, 32,32), 1,1),
_spriteCanon(*Resources::getTexture("sprites/sniperTower.png"), sf::IntRect(32,0, 32,32), 1,1){
    _id = id;
    _ticksForShoot = 60;
    _ticksBetweenShoots = 60;
    _damage = 5;

    _minRange = 0;
    _maxRange = -1;

    _spriteBase.setOrigin(16,16);
    _spriteBase.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);
    _spriteCanon.setOrigin(16,26);
    _spriteCanon.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);
}

void  SniperTower::setPosition(Vec2i position){
    Tower::setPosition(position);
    Vec2d pos = Game::getRealPosition(position);
    _spriteBase.setPosition(pos.x, pos.y);
    _spriteCanon.setPosition(pos.x, pos.y);
}

TowerEvent SniperTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            Vec2d pos = Game::getRealPosition(_position);

            Game::entities.push_back(new LaserEntity(pos, (*it)->getPosition(), 10));
            Game::entities.push_back(new FireEntity((*it)->getPosition(), 50));

            Vec2d temp((*it)->getPosition()-pos);
            if(temp.x!=0)
                _spriteCanon.setRotation(90 + atan2(temp.y, temp.x) * 180/PI);

            if((*it)->damage(_damage)){
                Game::kill(it);
            }
            _ticksForShoot = _ticksBetweenShoots;
        }

    }else --_ticksForShoot;
    return TowerEvent::None;
}

void SniperTower::draw(sf::RenderWindow* window) const{
    window->pushGLStates();

        window->draw(_spriteBase);

    window->popGLStates();
}

void SniperTower::drawOver(sf::RenderWindow* window) const{
    window->pushGLStates();

        window->draw(_spriteCanon);

    window->popGLStates();
}

Tower* SniperTower::clone() const {
    return new SniperTower();
}
