#include "BasicEnemy.h"

#include <SFML/OpenGL.hpp>

#include "Game.h"

<<<<<<< HEAD
BasicEnemy::BasicEnemy(double velocity, double life, double damage)
: Enemy(1){
=======
BasicEnemy::BasicEnemy(double velocity, double life, double damage){
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    _velocity = velocity;
    _life = life;
    _damage = damage;
    if(Game::enemiesRoute.size()>=1)
        _position = Game::enemiesRoute[0];
<<<<<<< HEAD
=======
    _nextPositionIndex = 1;
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
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
