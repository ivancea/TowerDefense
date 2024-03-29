#include "RocketTower.hpp"

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
            Game::entities.emplace_back(_followEnemy
                                ? std::make_unique<Rocket>(it->get(), _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare)
                                : std::make_unique<Rocket>((*it)->getPosition(), _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    return TowerEvent::None;
}

void RocketTower::draw(sf::RenderWindow* window, Vec2d point) const {
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(255,0,127);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(point.x+sin(i)*t,
                       point.y+cos(i)*t);
    glEnd();

    glColor3ub(0,0,127);
    glBegin(GL_POLYGON);
        glVertex2i(point.x, point.y);
        for(float i=0; i<PI*2.0*((double)_ticksForShoot/(double)_ticksBetweenShoots); i+=PI/360)
            glVertex2i(point.x+sin(-i)*t,
                       point.y+cos(i+PI)*t);
    glEnd();
}

std::unique_ptr<Tower> RocketTower::clone() const {
    return std::make_unique<RocketTower>();
}
