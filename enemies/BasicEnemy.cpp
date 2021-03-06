#include "BasicEnemy.hpp"

#include <SFML/OpenGL.hpp>

#include "../Game.hpp"

BasicEnemy::BasicEnemy(double velocity, double life, double damage)
: Enemy(1){
    _velocity = velocity;
    _life = life;
    _damage = damage;
    if(Game::enemiesRoute.size()>=1)
        _position = Game::enemiesRoute[0];
}

void BasicEnemy::killed(){
    Game::money += 10;
}

void BasicEnemy::draw(sf::RenderWindow* window) const{
    int sz = _life/2;
    if(sz<=0)
        sz = 1;
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        glVertex2i(_position.x-sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y+sz);
        glVertex2i(_position.x-sz,_position.y+sz);
    glEnd();
}
