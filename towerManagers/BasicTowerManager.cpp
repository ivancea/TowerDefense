#include "BasicTowerManager.hpp"

#include "../towers/SoldierTower.hpp"
#include "../towers/SniperTower.hpp"
#include "../towers/RocketTower.hpp"
#include "../towers/FlameRingTower.hpp"
#include "../towers/ShotgunTower.hpp"
#include "../towers/SwordTower.hpp"


BasicTowerManager::BasicTowerManager(){
    SoldierTower::id = 1;
    SniperTower::id = 2;
    RocketTower::id = 3;
    FlameRingTower::id = 4;
    ShotgunTower::id = 5;
    SwordTower::id = 6;

    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<SoldierTower>(),
                                   "Soldier",
                                   "Fast shots, low damage",
                                   150));
    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<SniperTower>(),
                                   "Sniper",
                                   "High damage and global range, but low attack rate",
                                   200));
    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<RocketTower>(),
                                   "Rocket",
                                   "Ground area damage",
                                   300));
    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<FlameRingTower>(),
                                   "Flame Ring",
                                   "Area damage, low range",
                                   400));
    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<ShotgunTower>(),
                                   "Shotgun",
                                   "High spread damage, low attack rate and range",
                                   250));
    _towerTypes.emplace_back(std::make_unique<TowerType>(std::make_unique<SwordTower>(),
                                   "Sword",
                                   "Average area damage, unstoppable",
                                   250));
}
