#include "BasicTowerManager.h"

#include "RocketTower.h"
#include "SniperTower.h"


BasicTowerManager::BasicTowerManager(){
    _towerTypes.push_back(new TowerType(new SniperTower(_nextId++),
                                   "Sniper",
                                   "High damage and global range, but low attack rate",
                                   200, nullptr, nullptr));
    _towerTypes.push_back(new TowerType(new RocketTower(_nextId++),
                                   "Rocket",
                                   "Ground area damage",
                                   200, nullptr, nullptr));

    _lastError = 0;
}

TowerType* BasicTowerManager::getTowerType(int id){
    for(TowerType* tt : _towerTypes)
        if(tt!=nullptr && tt->model!=nullptr && id==tt->model->getId())
            return tt;
    return nullptr;
}
