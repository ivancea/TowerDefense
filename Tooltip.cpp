#include "Tooltip.hpp"

Tooltip::Tooltip(){
    _maxWidth = 0;
    _backColor = sf::Color(255,255,200,220);
    _foreColor = sf::Color::Black;

    _fontArial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
}

Tooltip::Tooltip(const std::string& title, const std::string& body,
                 Vec2i point, int maxWidth,
                 sf::Color backColor, sf::Color foreColor){
    setTitle(title);
    setBody(body);

    _point = point;
    _maxWidth = maxWidth;

    _backColor = backColor;
    _foreColor = foreColor;

    _fontArial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
}

void Tooltip::setTitle(const std::string& title){
    _title = title;
}

void Tooltip::setBody(const std::string& body){
    _body = body;
}

void Tooltip::setPoint(Vec2i point){
    _point = point;
}

void Tooltip::draw(sf::RenderWindow* window) const {
    window->pushGLStates();

        sf::Text titleText, bodyText;
        titleText.setFont(_fontArial);
        titleText.setString(_title);
        titleText.setColor(_foreColor);
        titleText.setCharacterSize(15);
        titleText.setStyle(sf::Text::Bold);
        bodyText.setFont(_fontArial);
        bodyText.setString(_body);
        bodyText.setColor(_foreColor);
        bodyText.setCharacterSize(12);
        sf::FloatRect titleBounds = titleText.getGlobalBounds(),
                      bodyBounds = bodyText.getGlobalBounds();

        int width = 10 + (titleBounds.width>bodyBounds.width?titleBounds.width:bodyBounds.width);
        int height = 5 + 10 + titleBounds.height + bodyBounds.height;

        sf::RectangleShape rect(sf::Vector2f(width,height));
        rect.setPosition(_point.x-width, _point.y);
        rect.setFillColor(_backColor);
        rect.setOutlineThickness(1);
        window->draw(rect);

        titleText.setPosition(_point.x-width+5, _point.y);
        bodyText.setPosition(_point.x-width+5, _point.y + titleBounds.height + 10);
        window->draw(titleText);
        window->draw(bodyText);


    window->popGLStates();
}
