#include "TowerType.h"


TowerType::TowerType()
: model(nullptr), name(), description(), cost(0), baseTexture(nullptr), canonTexture(nullptr){}

TowerType::TowerType(Tower* _model, std::string _name, std::string _description, int _cost, sf::Texture* _baseTexture, sf::Texture* _canonTexture)
: model(_model), name(_name), description(_description), cost(_cost), baseTexture(_baseTexture), canonTexture(_canonTexture){}
