#include "TowerType.h"


TowerType::TowerType()
: model(nullptr), name(), description(), cost(0){}

TowerType::TowerType(Tower* _model, std::string _name, std::string _description, int _cost)
: model(_model), name(_name), description(_description), cost(_cost){}
