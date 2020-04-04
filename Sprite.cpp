#include "Sprite.hpp"

Sprite::Sprite(){
    _countX = 1;
    _countY = 1;
    _count = 1;
    _actualFrame = 0;
}

Sprite::Sprite(const sf::Texture& texture, int countX, int countY, int count)
:sf::Sprite(texture),_rect(0,0, texture.getSize().x, texture.getSize().y),_countX(countX),_countY(countY),_count(count),_actualFrame(0){
    if(_count<=0)
        _count = _countX*_countY;
    if(_count<=0 ||_countX<=0 || _countY<=0)
        throw "Sprite frame count cannot be less than 1";
    setFrame(0);
}

Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rect, int countX, int countY, int count)
:sf::Sprite(texture),_rect(rect),_countX(countX),_countY(countY),_count(count),_actualFrame(0){
    if(_count<=0)
        _count = _countX*_countY;
    if(_count<=0 || _countX<=0 || _countY<=0)
        throw "Sprite frame count less than 1";
    setFrame(0);
}

void Sprite::setCount(int countX, int countY, int count){
    _countX = countX;
    _countY = countY;
    if(_count<=0)
        _count = _countX*_countY;
    if(_count<=0 || _countX<=0 || _countY<=0)
        throw "Sprite frame count less than 1";
}

void Sprite::nextFrame(){
    setFrame(_actualFrame+1);
}

void Sprite::setFrame(int n){
    if(_count<=0 || _countX<=0 || _countY<=0)
        throw "Sprite frame count less than 1";
    _actualFrame = n%_count;
    setTextureRect(sf::IntRect(_rect.left + (_actualFrame%_countX)*_rect.width/_countX, _rect.top + ((_actualFrame/_countX)%_countY)*_rect.height/_countY,
                               _rect.width/_countX,_rect.height/_countY));
}

int Sprite::getFrame() const{
    return _actualFrame;
}

sf::Vector2i Sprite::getSize() const{
    sf::FloatRect t = getGlobalBounds();
    return sf::Vector2i(t.width, t.height);
}
