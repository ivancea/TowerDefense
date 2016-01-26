#include "Rocket.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "../../Game.h"
<<<<<<< HEAD
#include "../../entities/ExplosionEntity.h"
=======
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178

Rocket::Rocket(Enemy* target, double damage, double explosionRange,
               double velocity, double maxDistance,
               bool hitEnemiesInPath, Vec2d position){
    _position = position;
    _targetEnemy = target;
    _targetPosition = target->getPosition();
    _damage = damage;
    _explosionRange = explosionRange;
    _velocity = velocity;
<<<<<<< HEAD
    _distanceTraveled = 0;
    _maxDistance = maxDistance;
=======
    _maxDistance = maxDistance; // TODO: Implement
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    _hitEnemiesInPath = hitEnemiesInPath;
}

Rocket::Rocket(Vec2d target, double damage, double explosionRange,
               double velocity, double maxDistance,
               bool hitEnemiesInPath, Vec2d position){
    _position = position;
    _targetEnemy = nullptr;
    _targetPosition = target;
    _damage = damage;
    _explosionRange = explosionRange;
    _velocity = velocity;
<<<<<<< HEAD
    _distanceTraveled = 0;
=======
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    _maxDistance = maxDistance;
    _hitEnemiesInPath = hitEnemiesInPath;
}

void Rocket::damageEnemies() const{
<<<<<<< HEAD
    Game::entities.push_back(new ExplosionEntity(_position, _explosionRange, 10));
=======
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    for(auto it = Game::enemies.begin(); it != Game::enemies.end();){
        if((*it)->getPosition().distance(_position)<=_explosionRange){
            if((*it)->damage(_damage))
                it = Game::kill(it);
            else
                it++;
        }else it++;
    }
}

bool Rocket::tick(){
    if(Game::exists(_targetEnemy)){
        _targetPosition = _targetEnemy->getPosition();
    }else{
        _targetEnemy = nullptr;
    }

    Vec2d p = _targetPosition;
<<<<<<< HEAD
    double distance = p.distance(_position);
    if(distance<=_velocity
    && distance+_distanceTraveled<_maxDistance){
=======

    if(p.distance(_position)<=_velocity){
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
        _position = p;
        damageEnemies();
        return true;
    }else{
        p = p-_position;
        p.normalize();
<<<<<<< HEAD
        if(_velocity+_distanceTraveled<_maxDistance){
            p *= _velocity;
            _distanceTraveled += _velocity;
            _position += p;
        }else{
            p *= _maxDistance-_distanceTraveled;
            _distanceTraveled = _maxDistance;
            _position += p;
            damageEnemies();
            return true;
        }
    }

    if(_hitEnemiesInPath && Game::findEnemiesInRange(_position, 0,10).size()>0){
        damageEnemies();
        return true;
=======
        p *= _velocity;
        _position += p;
>>>>>>> 7146168b63f00ded2fecf3a9893f4a80e25f7178
    }

    /// TODO: HitEnemiesInPath mode

    return false;
}

void Rocket::draw(sf::RenderWindow* window) const{
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.0; i+=PI/360)
            glVertex2i(_position.x+sin(i)*5,
                       _position.y+cos(i)*5);
    glEnd();
}
