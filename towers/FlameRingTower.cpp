#include "FlameRingTower.h"

FlameRingTower::FlameRingTower(int id){
    _id = id;
    _ticksForRing = 0;
    _ticksBetweenRings = 5;
    _minRange = 5;
    _maxRange = 80;
    _ringVelocity = 2.5;
    _ringActualRange = _minRange;
    _ringSize = 30;
    _damage = 0.15;
}

TowerEvent FlameRingTower::tick(){
    if(_ticksForRing<=0){
        _ringActualRange += _ringVelocity;
        if(_ringActualRange+_ringSize>_maxRange){
            _ringActualRange = _minRange;
            _ticksForRing = _ticksBetweenRings;
        }
        for(auto it = Game::enemies.begin(); it!=Game::enemies.end();){
            if(Game::isInRange((_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare, _ringActualRange, _ringActualRange+_ringSize, *it)){
                if((*it)->damage(_damage))
                    it = Game::kill(it);
                else
                    it++;
            }else it++;
        }
    }else --_ticksForRing;
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

void FlameRingTower::drawOver(sf::RenderWindow* window) const{
    glColor3ub(127,127,0);
    glBegin(GL_TRIANGLE_STRIP);
    for(float i=0; i<=PI*2.01; i+=PI/360.0){
        glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*_ringActualRange,
                   _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*_ringActualRange);
        glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*(_ringActualRange+_ringSize),
                   _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*(_ringActualRange+_ringSize));
    }
    glEnd();
}
