#include "RocketTower.h"

int RocketTower::id = -1;

RocketTower::RocketTower(){
    _id = id;
    _ticksForShoot = 120;
    _ticksBetweenShoots = 120;
    _damage = 5;
    _explosionRange = 40;
    _rocketVelocity = 5;

    _maxRocketDistance = 500;

    _followEnemy = false;
    _hitEnemiesInPath = true;

    _minRange = 0;
    _maxRange = 120;
}

TowerEvent RocketTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            Game::entities.push_back(_followEnemy?
                               new Rocket(*it, _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare)
                              :new Rocket((*it)->getPosition(), _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    return TowerEvent::None;
}

void RocketTower::draw(sf::RenderWindow* window) const {
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(255,0,127);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();

    glColor3ub(0,0,127);
    glBegin(GL_POLYGON);
        glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2,
                   _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2);
        for(float i=0; i<PI*2.0*((double)_ticksForShoot/(double)_ticksBetweenShoots); i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(-i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i+PI)*t);
    glEnd();
}

Tower* RocketTower::clone() const {
    return new RocketTower();
}
