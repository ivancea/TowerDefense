#include "Enemy.h"

#include "Game.h"

Enemy::Enemy(int nextPositionIndex){
    _nextPositionIndex = nextPositionIndex;

    reloadDistanceToEnd();
}

bool Enemy::damage(double n){
    return (_life-=n)<=0;
}

void Enemy::killed(){}

void Enemy::reloadDistanceToEnd(){
    if(_nextPositionIndex<0 || _nextPositionIndex>=Game::enemiesRoute.size()){
        _distanceToEnd = -1;
    }else{
        double d = 0;
        Vec2d p = _position;
        for(int i=_nextPositionIndex; i<Game::enemiesRoute.size(); i++)
            d += p.distance(Game::enemiesRoute[i]);
        _distanceToEnd = d;
    }
}

bool Enemy::tick(){
    if(Game::enemiesRoute.size()<=_nextPositionIndex
    || _nextPositionIndex<0 || _distanceToEnd<=_velocity)
        return true;

    Vec2d p = Game::enemiesRoute[_nextPositionIndex];
    double toMove = _velocity;
    _distanceToEnd -= toMove;
    while(toMove>0.0){
        double d = _position.distance(p);
        if(d<=_velocity){
            _position = p;
            _nextPositionIndex += 1;
            /*if(Game::enemiesRoute.size()<=_nextPositionIndex){
                _nextPositionIndex = -1;
                return true;
            }*/
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

int Enemy::setNextPositionIndex(int nextPositionIndex){
    _nextPositionIndex = nextPositionIndex;
    reloadDistanceToEnd();
}

double Enemy::getDistanceToNextPosition() const{
    if(_nextPositionIndex<0 || Game::enemiesRoute.size()<=_nextPositionIndex)
        return -1;
    return _position.distance(Game::enemiesRoute[_nextPositionIndex]);
}

double Enemy::getDistanceToEnd() const{
    return _distanceToEnd;
}
