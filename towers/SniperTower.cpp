#include "SniperTower.h"

#include "../entities/LaserEntity.h"

SniperTower::SniperTower(int id){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 60;
    _damage = 5;

    _minRange = 0;
    _maxRange = -1;
}

TowerEvent SniperTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            Game::entities.push_back(new LaserEntity(Game::getRealPosition(_position), (*it)->getPosition(), 10));
            if((*it)->damage(_damage)){
                Game::kill(it);
            }
            _ticksForShoot = _ticksBetweenShoots;
        }

    }else --_ticksForShoot;
    return TowerEvent::None;
}

void SniperTower::draw(sf::RenderWindow* window) const{
    int t = Game::pixelsPerSquare/2-2;
    glColor3ub(_ticksForShoot*3,0,255);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.0; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();
}

