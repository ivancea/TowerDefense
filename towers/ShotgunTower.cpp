#include "ShotgunTower.hpp"

#include <random>

int ShotgunTower::id = -1;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,1000);

double random(double min, double max) {
    return (distribution(generator) / 1000.) * (max - min) + min;
}

ShotgunTower::ShotgunTower(){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 20;
    _damage = 0.25;
    _bulletVelocity = 15;

    _maxBulletDistance = 300;

    _minRange = 0;
    _maxRange = 150;
}

TowerEvent ShotgunTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            for (int i = 0; i < 10; i++) {
                Vec2d target = (*it)->getPosition() + Vec2d(random(-30, 30), random(-30, 30))-((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare;
                target.normalize();
                target = ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare + target*(_maxBulletDistance>_maxRange?_maxBulletDistance:_maxRange);
                Game::entities.emplace_back(std::make_unique<Bullet>(target, _damage, _bulletVelocity,
                                                    ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));
            }

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    return TowerEvent::None;
}

void ShotgunTower::draw(sf::RenderWindow* window, Vec2d point) const{
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(200,200,100);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(point.x+sin(i)*t,
                       point.y+cos(i)*t);
    glEnd();
}

std::unique_ptr<Tower> ShotgunTower::clone() const {
    return std::make_unique<ShotgunTower>();
}
