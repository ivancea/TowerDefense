#include "SniperTower.h"

#include <cmath>

#include <SFML/OpenGL.hpp>

#include "../Resources.h"
#include "../entities/LaserEntity.h"
#include "../entities/FireEntity.h"

int SniperTower::id = -1;

SniperTower::SniperTower(){
    _id = id;
    _ticksForShoot = 60;
    _ticksBetweenShoots = 60;
    _damage = 5;

    _minRange = 0;
    _maxRange = -1;

    sf::Texture* tex = Resources::getTexture("sprites/sniperTower.png");
    if(tex!=nullptr){
        _spriteBase.setTexture(*tex);
        _spriteCanon.setTexture(*tex);
    }
    _spriteBase.setTextureRect(sf::IntRect(0,0, 32,32));
    _spriteBase.setOrigin(16,16);
    _spriteBase.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);

    _spriteCanon.setTextureRect(sf::IntRect(32,0, 32,32));
    _spriteCanon.setOrigin(16,26);
    _spriteCanon.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);
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

void SniperTower::draw(sf::RenderWindow* window, Vec2d point) const{
    window->pushGLStates();

        sf::RenderStates rs;
        rs.transform.translate(point.x, point.y);
        window->draw(_spriteBase, rs);

    window->popGLStates();
}

void SniperTower::drawOver(sf::RenderWindow* window, Vec2d point) const{
    window->pushGLStates();

        sf::RenderStates rs;
        rs.transform.translate(point.x, point.y);
        window->draw(_spriteCanon, rs);

    window->popGLStates();
}

Tower* SniperTower::clone() const {
    return new SniperTower();
}
