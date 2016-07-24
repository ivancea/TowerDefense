#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <SFML/Graphics.hpp>

#include "Vec.hpp"

class Tooltip{
    Vec2i _point;
    int _maxWidth;

    sf::Color _backColor;
    sf::Color _foreColor;

    std::string _title;
    std::string _body;

public:
    Tooltip();
    Tooltip(std::string title, std::string body,
            Vec2i point, int maxWidth = 0,
            sf::Color backColor = sf::Color(255,255,200,220),
            sf::Color foreColor = sf::Color::Black);

    void setTitle(std::string title);
    void setBody(std::string body);
    void setPoint(Vec2i point);

    void draw(sf::RenderWindow* window) const;
};

#endif // TOOLTIP_H
