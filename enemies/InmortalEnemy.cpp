#include "InmortalEnemy.hpp"

#include <SFML/OpenGL.hpp>

#include "../Game.hpp"

InmortalEnemy::InmortalEnemy(double velocity, double damage)
: Enemy(1){
    _velocity = velocity;
    _life = 1;
    _damage = damage;
    if(Game::enemiesRoute.size()>=1)
        _position = Game::enemiesRoute[0];
}

bool InmortalEnemy::damage(double n){
    return false;
}

void InmortalEnemy::draw(sf::RenderWindow* window) const{
    int sz = Game::pixelsPerSquare/3;
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
        glVertex2i(_position.x-sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y+sz);
        glVertex2i(_position.x-sz,_position.y+sz);
    glEnd();

    glLineWidth(1.0);
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(_position.x-sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y+sz);
        glVertex2i(_position.x-sz,_position.y+sz);
        glVertex2i(_position.x+sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y+sz);
        glVertex2i(_position.x-sz,_position.y-sz);
        glVertex2i(_position.x-sz,_position.y+sz);
    glEnd();
}
