#ifndef BASICTOWERMANAGER_H
#define BASICTOWERMANAGER_H

#include "../TowerManager.h"
#include "RocketTower.h"
#include "SniperTower.h"

class BasicTowerManager : public TowerManager{
    int _nextId;

public:
    BasicTowerManager();
};

#endif // BASICTOWERMANAGER_H
