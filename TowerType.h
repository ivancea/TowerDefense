#ifndef TOWERTYPE_H
#define TOWERTYPE_H

struct TowerType;

#include <string>
#include <SFML/Graphics.hpp>

#include "Tower.h"

struct TowerType{
    Tower* model;
    std::string name,
           description;
    int cost;
    sf::Texture *baseTexture,
                *canonTexture;

    TowerType();
    TowerType(Tower* model, std::string name, std::string description, int cost, sf::Texture* baseTexture, sf::Texture* canonTexture);
};

#endif // TOWERTYPE_H
