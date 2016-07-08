#include "ExplosionEntity.h"

#include "../Game.h"
#include <SFML/OpenGL.hpp>

ExplosionEntity::ExplosionEntity(Vec2d position, double range, int ticksAlive){
    _position = position;
    _range = range;
    _ticksAlive = ticksAlive;
    _ticksLived = 0;
}

bool ExplosionEntity::tick(){
    return _ticksLived++ >= _ticksAlive;
}

void ExplosionEntity::draw(sf::RenderWindow* window) const{
    glColor4ub(255,127,0, 230);
    glBegin(GL_TRIANGLES);
        for(float i=0; i<=PI*2.00; i+=PI/360.0){
            glVertex2i(_position.x+sin(i)*_range,
                       _position.y+cos(i)*_range);
            glVertex2i(_position.x+sin(i+PI/360.0)*_range,
                       _position.y+cos(i+PI/360.0)*_range);
            glVertex2i(_position.x,_position.y);
        }
    glEnd();
}
