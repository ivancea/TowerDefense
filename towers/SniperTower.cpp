#include "SniperTower.h"

#include <cmath>

#include "../Resources.h"
#include "../entities/LaserEntity.h"
#include "../entities/FireEntity.h"

int SniperTower::id = -1;

SniperTower::SniperTower()
:_spriteBase(Resources::sniperTower, sf::IntRect(0,0, 32,32), 1,1),
_spriteCanon(Resources::sniperTower, sf::IntRect(32,0, 32,32), 1,1){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 60;
    _damage = 5;

    _minRange = 0;
    _maxRange = -1;

    _spriteBase.setOrigin(16,16);
    _spriteBase.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);
    _spriteCanon.setOrigin(16,26);
    _spriteCanon.scale(Game::pixelsPerSquare/32.0, Game::pixelsPerSquare/32.0);
}

TowerEvent SniperTower::tick(){
    Vec2d pos = Game::getRealPosition(_position);
    _spriteBase.setPosition(pos.x, pos.y); // TODO: setPosition of tower as virtual?
    _spriteCanon.setPosition(pos.x, pos.y);

    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
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

/*void SniperTower::draw(sf::RenderWindow* window) const{
    int t = Game::pixelsPerSquare/2-2;
    glColor3ub(_ticksForShoot*3,0,255);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.0; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();
}*/

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

