#include "Bullet.hpp"

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "../../Game.hpp"

Bullet::Bullet(Vec2d target, double damage,
               double velocity, Vec2d position){
    _position = position;
    _target = target;
    _damage = damage;
    _velocity = velocity;
}

bool Bullet::tick(){
    Vec2d p = _target;
    bool ret = false;
    if(p.distance(_position)<=_velocity){
        _position = p;
        ret = true;
    }else{
        p = p-_position;
        p.normalize();
        p *= _velocity;
        _position += p;
    }
    auto t = Game::enemies.end();
    double minDistance = -1;
    for(auto it = Game::enemies.begin(); it!=Game::enemies.end(); it++){
        double d = _position.distance((*it)->getPosition());
        if(d<15 && (minDistance<0 || d<minDistance)){
            t = it;
            minDistance = d;
        }
    }
    if(t!=Game::enemies.end()){
        if((*t)->damage(_damage))
            Game::kill(t);
        ret = true;
    }
    return ret;
}

void Bullet::drawOver(sf::RenderWindow* window) const{
    glColor3ub(100,100,255);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.0; i+=PI/360)
            glVertex2i(_position.x+sin(i)*3,
                       _position.y+cos(i)*3);
    glEnd();
}
