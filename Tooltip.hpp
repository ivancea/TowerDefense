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

    sf::Font _fontArial;

public:
    Tooltip();
    Tooltip(const std::string& title, const std::string& body,
            Vec2i point, int maxWidth = 0,
            sf::Color backColor = sf::Color(255,255,200,220),
            sf::Color foreColor = sf::Color::Black);

    void setTitle(const std::string& title);
    void setBody(const std::string& body);
    void setPoint(Vec2i point);

    void draw(sf::RenderWindow* window) const;
};

#endif // TOOLTIP_H
