#include "Rocket.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "../../Game.hpp"
#include "../../entities/ExplosionEntity.hpp"

Rocket::Rocket(Enemy* target, double damage, double explosionRange,
               double velocity, double maxDistance,
               bool hitEnemiesInPath, Vec2d position){
    _position = position;
    _targetEnemy = target;
    _targetPosition = target->getPosition();
    _damage = damage;
    _explosionRange = explosionRange;
    _velocity = velocity;
    _distanceTraveled = 0;
    _maxDistance = maxDistance;
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
    _distanceTraveled = 0;
    _maxDistance = maxDistance;
    _hitEnemiesInPath = hitEnemiesInPath;
}

void Rocket::damageEnemies() const{
    Game::entities.emplace_back(std::make_unique<ExplosionEntity>(_position, _explosionRange, 50));
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
    double distance = p.distance(_position);
    if(distance<=_velocity
    && distance+_distanceTraveled<_maxDistance){
        _position = p;
        damageEnemies();
        return true;
    }else{
        p = p-_position;
        p.normalize();
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
    }

    return false;
}

void Rocket::drawOver(sf::RenderWindow* window) const{
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.0; i+=PI/360)
            glVertex2i(_position.x+sin(i)*5,
                       _position.y+cos(i)*5);
    glEnd();
}
