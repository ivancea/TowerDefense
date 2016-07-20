#include "FlameRingTower.h"

#include "entities/FlameRing.h"

int FlameRingTower::id = -1;

FlameRingTower::FlameRingTower(){
    _id = id;
    _ticksForShoot = 30;
    _ticksBetweenShoots = 30;
    _minRange = 5;
    _maxRange = 80;
    _ringVelocity = 2.5;
    _ringActualRange = _minRange;
    _ringSize = 30;
    _damage = 0.15;
}

TowerEvent FlameRingTower::tick(){
    if(_ticksForShoot <= 0){

        Game::entities.push_back(
            new FlameRing(
                Game::getRealPosition(_position),
                _ringSize, _damage, _ringVelocity,
                _maxRange, _minRange
            )
        );

        _ticksForShoot = _ticksBetweenShoots;
    }else --_ticksForShoot;
    return TowerEvent::None;
}

void FlameRingTower::draw(sf::RenderWindow* window) const{
    int t = Game::pixelsPerSquare/2-2;
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();
}
