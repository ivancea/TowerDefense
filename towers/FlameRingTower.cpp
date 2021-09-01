#include "FlameRingTower.hpp"

#include "entities/FlameRing.hpp"

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

        Game::entities.emplace_back(
            std::make_unique<FlameRing>(
                Game::getRealPosition(_position),
                _ringSize, _damage, _ringVelocity,
                _maxRange, _minRange
            )
        );

        _ticksForShoot = _ticksBetweenShoots;
    }else --_ticksForShoot;
    return TowerEvent::None;
}

void FlameRingTower::draw(sf::RenderWindow* window, Vec2d point) const{
    int t = Game::pixelsPerSquare/2-2;
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(point.x+sin(i)*t,
                       point.y+cos(i)*t);
    glEnd();
}

std::unique_ptr<Tower> FlameRingTower::clone() const {
    return std::make_unique<FlameRingTower>();
}
