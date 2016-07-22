#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

class TowerManager;

#include <string>
#include <list>

#include "TowerType.h"

class TowerManager{

protected:
    std::list<TowerType*> _towerTypes;

public:
    virtual ~TowerManager();

    virtual TowerType* getTowerType(int id);
    virtual int getTowerCost(int id);
};

#endif // TOWERMANAGER_H
