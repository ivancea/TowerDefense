#include "TowerType.hpp"


TowerType::TowerType()
: model(nullptr), name(), description(), cost(0){}

TowerType::TowerType(std::unique_ptr<Tower> _model, std::string _name, std::string _description, int _cost)
: model(std::move(_model)), name(_name), description(_description), cost(_cost){}
