#include "LaserEntity.h"

#include "../Game.h"
#include <SFML/OpenGL.hpp>

LaserEntity::LaserEntity(Vec2d from, Vec2d to, int ticks){
    _from = from;
    _to = to;
    _ticksRemaining = ticks;
}

bool LaserEntity::tick(){
    return _ticksRemaining-- <= 0;
}

void LaserEntity::drawOver(sf::RenderWindow* window) const{
    glLineWidth(1);
    glColor3ub(255,125,125);
    glBegin(GL_LINES);
        glVertex2i(_from.x, _from.y);
        glVertex2i(_to.x, _to.y);
    glEnd();
}

