#include "BasicTowerManager.h"

#include "SoldierTower.h"
#include "SniperTower.h"
#include "RocketTower.h"
#include "FlameRingTower.h"


BasicTowerManager::BasicTowerManager(){
    SoldierTower::id = 1;
    SniperTower::id = 2;
    RocketTower::id = 3;
    FlameRingTower::id = 4;
    _towerTypes.push_back(new TowerType(new SoldierTower(),
                                   "Soldier",
                                   "Fast shots, low damage",
                                   150, nullptr, nullptr));
    _towerTypes.push_back(new TowerType(new SniperTower(),
                                   "Sniper",
                                   "High damage and global range, but low attack rate",
                                   200, nullptr, nullptr));
    _towerTypes.push_back(new TowerType(new RocketTower(),
                                   "Rocket",
                                   "Ground area damage",
                                   300, nullptr, nullptr));
    _towerTypes.push_back(new TowerType(new FlameRingTower(),
                                   "Flame Ring",
                                   "Area damage, low range",
                                   300, nullptr, nullptr));

    _lastError = 0;
}
