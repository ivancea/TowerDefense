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
