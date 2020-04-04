#ifndef TOWERTYPE_H
#define TOWERTYPE_H

struct TowerType;

#include <string>
#include <SFML/Graphics.hpp>

#include "Tower.hpp"

struct TowerType{
    Tower* model;
    std::string name;
    std::string description;
    int cost;

    TowerType();
    TowerType(Tower* model, std::string name, std::string description, int cost);
};

#endif // TOWERTYPE_H
