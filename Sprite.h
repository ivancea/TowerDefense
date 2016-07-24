#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite{
    sf::IntRect _rect;
    int _countX;
    int _countY;
    int _count;

    int _actualFrame;

public:
    Sprite();
    Sprite(const sf::Texture& texture, int countX, int countY, int count = 0);
    Sprite(const sf::Texture& texture, const sf::IntRect& rect, int countX, int countY, int count = 0);

    void setCount(int countX, int countY, int count = 0);

    void nextFrame();
    void setFrame(int n);
    int getFrame() const;

    sf::Vector2i getSize() const;
};

#endif // SPRITE_H
