#include "FlameRing.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "../../Game.hpp"

FlameRing::FlameRing(Vec2d position, double ringSize,
                     double damage, double velocity,
                     double maxRadius, double initialRadius){
    _position = position;
    _ringSize = ringSize;
    _damage = damage;
    _velocity = velocity;
    _maxRadius = maxRadius;
    _actualRadius = initialRadius;
}

bool FlameRing::tick(){

    auto li = Game::findEnemiesInRange(_position, _actualRadius, _actualRadius+_ringSize);
    for(auto it:li){
        if((*it)->damage(_damage)){
            Game::kill(it);
        }
    }

    _actualRadius += _velocity;

    return _actualRadius + _ringSize >= _maxRadius;
}

void FlameRing::drawOver(sf::RenderWindow* window) const{
    glColor4ub(127,127,0, 200);
    glBegin(GL_TRIANGLE_STRIP);
        for(float i=0; i<=PI*2.01; i+=PI/360.0){
            glVertex2i(_position.x+sin(i)*_actualRadius,
                       _position.y+cos(i)*_actualRadius);
            glVertex2i(_position.x+sin(i)*(_actualRadius+_ringSize),
                       _position.y+cos(i)*(_actualRadius+_ringSize));
        }
    glEnd();
}
