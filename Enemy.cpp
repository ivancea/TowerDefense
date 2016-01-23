#include "Enemy.h"

#include "Game.h"

bool Enemy::damage(double n){
    return (_life-=n)<=0;
}

bool Enemy::tick(){
    if(Game::enemiesRoute.size()<=_nextPositionIndex
    || _nextPositionIndex<0)
        return true;
    Vec2d p = Game::enemiesRoute[_nextPositionIndex];
    double toMove = _velocity;
    while(toMove>0.0){
        double d = _position.distance(p);
        if(d<=_velocity){
            _position = p;
            _nextPositionIndex += 1;
            if(Game::enemiesRoute.size()<=_nextPositionIndex){
                _nextPositionIndex = -1;
                return true;
            }
            toMove -= d;
            p = Game::enemiesRoute[_nextPositionIndex];
        }else{
            Vec2d t = p-_position;
            t.normalize();
            t *= _velocity;
            _position += t;
            toMove = 0.0;
        }
    }
    return false;
}

double Enemy::getDistanceToNextPosition() const{
    if(_nextPositionIndex<0 || Game::enemiesRoute.size()<=_nextPositionIndex)
        return -1;
    return _position.distance(Game::enemiesRoute[_nextPositionIndex]);
}
