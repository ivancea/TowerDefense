#include "SoldierTower.hpp"

int SoldierTower::id = -1;

SoldierTower::SoldierTower(){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 6;
    _damage = 0.5;
    _bulletVelocity = 15;

    _maxBulletDistance = 300;

    _minRange = 0;
    _maxRange = 150;
}

TowerEvent SoldierTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            Vec2d target = (*it)->getPosition()-((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare;
            target.normalize();
            target = ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare + target*(_maxBulletDistance>_maxRange?_maxBulletDistance:_maxRange);
            Game::entities.emplace_back(std::make_unique<Bullet>(target, _damage, _bulletVelocity,
                                                ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    return TowerEvent::None;
}

void SoldierTower::draw(sf::RenderWindow* window, Vec2d point) const{
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(100,200,100);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(point.x+sin(i)*t,
                       point.y+cos(i)*t);
    glEnd();
}

std::unique_ptr<Tower> SoldierTower::clone() const {
    return std::make_unique<SoldierTower>();
}
