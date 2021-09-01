#include "SwordTower.hpp"

int SwordTower::id = -1;

SwordTower::SwordTower(){
    _id = id;
    _damage = 0.51;
    _swordLength = 100;
    _swordWidth = 3;
    _swordAngle = 0;
}

double distanceBetweenLineAndPoint(Vec2d start, Vec2d end, Vec2d point) {
    Vec2d v = end - start;
    Vec2d w = point - start;
    double c1 = w * v;

    if (c1 <= 0) {
        return point.distance(start);
    }

    double c2 = v * v;

    if (c2 <= c1) {
        return point.distance(end);
    }

    double b = c1 / c2;
    Vec2d pB = start + v * b;
    
    return pB.distance(point);
}

TowerEvent SwordTower::tick(){
    _swordAngle += PI / 30;

    auto towerCenter = Game::getRealPosition(_position);
    auto swordEnd = Vec2d(towerCenter.x + _swordLength * cos(_swordAngle), towerCenter.y + _swordLength * sin(_swordAngle));
    
    for(auto it = Game::enemies.begin(); it!=Game::enemies.end();){
        double distance = distanceBetweenLineAndPoint(towerCenter, swordEnd, (*it)->getPosition());
        boolean killed = false;
        
        if(distance < 20){
            if((*it)->damage(_damage)) {
                it = Game::kill(it);
                killed = true;
            }
        }
        if (!killed) {
            it++;
        }
    }

    return TowerEvent::None;
}

void SwordTower::draw(sf::RenderWindow* window, Vec2d point) const{
    double t = Game::pixelsPerSquare/2-2;
    glColor3ub(100,200,100);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(point.x+sin(i)*t,
                       point.y+cos(i)*t);
    glEnd();
}

void SwordTower::drawOver(sf::RenderWindow* window, Vec2d point) const{
    auto towerCenter = Game::getRealPosition(_position);
    auto swordEnd = Vec2d(towerCenter.x + _swordLength * cos(_swordAngle), towerCenter.y + _swordLength * sin(_swordAngle));

    glLineWidth(_swordWidth);
    glColor3ub(255,125,125);
    glBegin(GL_LINES);
        glVertex2i(towerCenter.x, towerCenter.y);
        glVertex2i(swordEnd.x, swordEnd.y);
    glEnd();
}

std::unique_ptr<Tower> SwordTower::clone() const {
    return std::make_unique<SwordTower>();
}
