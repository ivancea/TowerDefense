#include "InhibitorEnemy.h"

#include <SFML/OpenGL.hpp>

#include "Game.h"


InhibitorEnemy::InhibitorEnemy(double velocity, double life, double damage)
: Enemy(1), _inhibitionTicks(0){
    _velocity = velocity;
    _life = life;
    _damage = damage;
    if(Game::enemiesRoute.size()>=1)
        _position = Game::enemiesRoute[0];
}

bool InhibitorEnemy::tick(){
    ++_inhibitionTicks;
    if(_inhibitionTicks==50){
        Tower* t = nullptr;
        double d = 151;
        for(Tower* tower : Game::towers){
            double dist = Game::getDistance(tower->getPosition(), _position);
            if(dist < d){
                t = tower;
                d = dist;
            }
        }
        if(t != nullptr){
            _target = t;
        }else{
            _inhibitionTicks = 49;
        }
    }else if(_inhibitionTicks>100){
        _inhibitionTicks = 0;
        _target = nullptr;
    }else if(_inhibitionTicks>50){
        if(_target==nullptr){
            _inhibitionTicks = 49;
        }else if(!Game::exists(_target)){
            _target = nullptr;
            _inhibitionTicks = 0;
        }else{
            if(Game::getDistance(_target->getPosition(), _position) < 150){
                _target->setTicksForShoot(_target->getTicksBetweenShoots());
            }else{
                _target = nullptr;
                _inhibitionTicks = 0;
            }
        }
    }
    return Enemy::tick();
}

void InhibitorEnemy::draw(sf::RenderWindow* window) const{
    int sz = _life/3;
    if(sz<=0)
        sz = 1;
    glColor3ub(0,150,200);
    glBegin(GL_POLYGON);
        glVertex2i(_position.x-sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y-sz);
        glVertex2i(_position.x+sz,_position.y+sz);
        glVertex2i(_position.x-sz,_position.y+sz);
    glEnd();
    if(Game::exists(_target)){
        glLineWidth(3);
        glColor4ub(200,50,50, 125);
        glBegin(GL_LINES);
            glVertex2i(_position.x, _position.y);
            glVertex2i(_target->getPosition().x*Game::pixelsPerSquare + Game::pixelsPerSquare/2, _target->getPosition().y*Game::pixelsPerSquare + Game::pixelsPerSquare/2);
        glEnd();
    }
}
