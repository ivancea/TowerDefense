#ifndef GAME_H
#define GAME_H

#define PI 3.14159265358979323846

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "TowerManager.h"
#include "Tower.h"
#include "Enemy.h"
#include "Vec.hpp"

namespace Game{

    enum TileType{
        EmptyTile,
        TowerTile,
        RoadTile
    };

    extern TowerManager* towerManager;
    extern std::list<Tower*> towers;
    extern std::list<Enemy*> enemies;

    extern std::vector<Vec2i> enemiesRoute;
    extern std::vector< std::vector<TileType> > map;
    extern int pixelsPerSquare;

    extern double life;

    extern Tower* selectedTower;

    bool tick();
    void draw(sf::RenderWindow* window);


    /// HELPERS

    Tower* getTower(Vec2i position);
    bool putTower(Tower* tower);
    std::list<Tower*>::iterator removeTower(std::list<Tower*>::iterator tower);
    Tower* removeTower(Vec2i position);

    bool isInRange(Vec2i position, double minRange, double maxRange, Enemy* enemy);

    std::list<Enemy*>::iterator kill(std::list<Enemy*>::iterator enemy);
    std::list<Enemy*>::iterator findTarget(Tower* tower);
    std::list< std::list<Enemy*>::iterator > findEnemiesInRange(Vec2i position, double minRange, double maxRange);

    bool exists(Enemy* enemy);
    bool exists(Tower* tower);
}

#endif // GAME_H
