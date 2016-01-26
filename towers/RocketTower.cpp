#include "RocketTower.h"

RocketTower::RocketTower(int id){
    _id = id;
    _ticksForShoot = 0;
    _ticksBetweenShoots = 120;
    _damage = 5;
<<<<<<< HEAD
    _explosionRange = 40;
=======
    _explosionRange = 50;
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    _rocketVelocity = 5;

    _maxRocketDistance = 500;

    _followEnemy = false;
    _hitEnemiesInPath = true;

    _minRange = 0;
    _maxRange = 120;
}

RocketTower::~RocketTower(){
    auto it = _rockets.begin();
    while(it!=_rockets.end()){
        delete *it;
        it = _rockets.erase(it);
    }
}

TowerEvent RocketTower::tick(){
    if(_ticksForShoot<=0){
        auto it = Game::findTarget(this);
        if(it != Game::enemies.end()){

            _rockets.push_back(_followEnemy?
                               new Rocket(*it, _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare)
                              :new Rocket((*it)->getPosition(), _damage, _explosionRange,
                                          _rocketVelocity, _maxRocketDistance,
                                          _hitEnemiesInPath, ((Vec2d)_position+Vec2d(0.5,0.5))*Game::pixelsPerSquare));

            _ticksForShoot = _ticksBetweenShoots;
        }
    }else --_ticksForShoot;

    for(auto it = _rockets.begin(); it!=_rockets.end();){
        Rocket* r = *it;
        if(r->tick()){
            delete r;
            it = _rockets.erase(it);
        }else it++;
    }

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
    t *= (double)_ticksForShoot/(double)_ticksBetweenShoots;
    glColor3ub(0,0,127);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(_position.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2+sin(i)*t,
                       _position.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2+cos(i)*t);
    glEnd();

    for(Rocket* r : _rockets)
        r->draw(window);
}

void RocketTower::drawOver(sf::RenderWindow* window) const {
    for(Rocket* r : _rockets)
        r->draw(window);
}
