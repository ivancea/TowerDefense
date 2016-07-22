#include "SoldierTower.h"

int SoldierTower::id = -1;

SoldierTower::SoldierTower(){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 12;
    _damage = 0.75;
    _bulletVelocity = 15;

    _maxBulletDistance = 300;

    _minRange = 0;
    _maxRange = 150;
}

SoldierTower::~SoldierTower(){
    auto it = _bullets.begin();
    while(it!=_bullets.end()){
        delete *it;
        it = _bullets.erase(it);
    }
}

TowerEvent SoldierTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){
            Vec2d target = (*it)->getPosition()-((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare;
            target.normalize();
            target = ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare + target*(_maxBulletDistance>_maxRange?_maxBulletDistance:_maxRange);
            _bullets.push_back(new Bullet(target, _damage, _bulletVelocity,
                                          ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    for(auto it = _bullets.begin(); it!=_bullets.end();){
        Bullet* r = *it;
        if(r->tick()){
            delete r;
            it = _bullets.erase(it);
        }else it++;
    }

    return TowerEvent::None;
}

void SoldierTower::draw(sf::RenderWindow* window) const {
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(100,200,100);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();

    for(Bullet* b : _bullets)
        b->draw(window);
}

void SoldierTower::drawOver(sf::RenderWindow* window) const {
    for(Bullet* b : _bullets)
        b->draw(window);
}
