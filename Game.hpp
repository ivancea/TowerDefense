#ifndef GAME_H
#define GAME_H

#define PI 3.14159265358979323846

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "TowerManager.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "Vec.hpp"

namespace Game{

    namespace Stats{

        extern unsigned int enemiesKilled;

    }

    enum TileType{
        EmptyTile,
        TowerTile,
        RoadTile
    };

    extern std::unique_ptr<TowerManager> towerManager;
    extern std::list<std::unique_ptr<Tower>> towers;
    extern std::list<std::unique_ptr<Enemy>> enemies;
    extern std::list<std::unique_ptr<Entity>> entities;

    extern std::vector<Vec2i> enemiesRoute;
    extern std::vector< std::vector<TileType> > map;
    extern int pixelsPerSquare;

    extern double life;
    extern int money;

    extern int tickCount;
    extern int velocity;

    extern Tower* selectedTower;

    bool tick();
    void draw(sf::RenderWindow* window);


    /// HELPERS

    Tower* getTower(Vec2i position);
    bool putTower(std::unique_ptr<Tower>& tower);
    std::list<Tower*>::iterator removeTower(std::list<Tower*>::iterator tower);
    boolean removeTower(Vec2i position);

    bool isInRange(Vec2d position, double minRange, double maxRange, Enemy* enemy);

    std::list<std::unique_ptr<Enemy>>::iterator kill(std::list<std::unique_ptr<Enemy>>::iterator enemy);
    std::list<std::unique_ptr<Enemy>>::iterator findTarget(Tower* tower);
    std::list< std::list<std::unique_ptr<Enemy>>::iterator > findEnemiesInRange(Vec2d position, double minRange, double maxRange);

    bool exists(Enemy* enemy);
    bool exists(Tower* tower);
    bool exists(Entity* entities);

    void clearTowers();
    void clearEntities();
    void clearEnemies();
    void killEnemies();

    double getDistance(Vec2i towerPosition, Vec2d position);
    Vec2d getRealPosition(Vec2i towerPosition);
}

#endif // GAME_H
