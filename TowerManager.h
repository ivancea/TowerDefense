#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

class TowerManager;

#include <string>
#include <list>

#include "TowerType.h"

class TowerManager{ /// TODO: redo clone method (or change schema)

protected:
    int _lastError;
    std::list<TowerType*> _towerTypes;

public:
    virtual ~TowerManager();

    virtual TowerType* getTowerType(int id);
    virtual int getTowerCost(int id);
};

#endif // TOWERMANAGER_H
