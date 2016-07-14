#include "TowerManager.h"


TowerManager::~TowerManager(){
    for(TowerType* tt : _towerTypes){
        if(tt!=nullptr){
            if(tt->model != nullptr)
                delete tt->model;
            delete tt;
        }
    }
    _towerTypes.clear();
}

TowerType* TowerManager::getTowerType(int id){
    for(TowerType* tt : _towerTypes)
        if(tt!=nullptr && tt->model!=nullptr && id==tt->model->getId())
            return tt;
    return nullptr;
}

int TowerManager::getTowerCost(int id){
    for(TowerType* tt : _towerTypes)
        if(tt!=nullptr && tt->model!=nullptr && id==tt->model->getId()){
            return tt->cost;
        }
    return 0;
}
