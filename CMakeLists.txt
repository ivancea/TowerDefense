cmake_minimum_required(VERSION 3.12)
project(TowerDefense)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/obj)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#Interfaces
add_library(Vec INTERFACE)
target_sources(Vec INTERFACE ${CMAKE_SOURCE_DIR}/Vec.hpp)
add_library(Entity INTERFACE)
target_sources(Entity INTERFACE ${CMAKE_SOURCE_DIR}/Entity.hpp)

#Global
add_library(Enemy Enemy.cpp Enemy.hpp)
add_library(Game Game.cpp Game.hpp)
add_library(MapManager MapManager.cpp MapManager.hpp)
add_library(Resources Resources.cpp Resources.hpp)
add_library(Sprite Sprite.cpp Sprite.hpp)
add_library(Tooltip Tooltip.cpp Tooltip.hpp)
add_library(Tower Tower.cpp Tower.hpp)
add_library(TowerManager TowerManager.cpp TowerManager.hpp)
add_library(TowerType TowerType.cpp TowerType.hpp)

#Enemies
add_library(BasicEnemy enemies/BasicEnemy.cpp enemies/BasicEnemy.hpp)
target_link_libraries(BasicEnemy Enemy Game)
add_library(InhibitorEnemy enemies/InhibitorEnemy.cpp enemies/InhibitorEnemy.hpp)
target_link_libraries(InhibitorEnemy Enemy Tower Game)
add_library(InmortalEnemy enemies/InmortalEnemy.cpp enemies/InmortalEnemy.hpp)
target_link_libraries(InmortalEnemy Enemy Game)

#Entities
add_library(ExplosionEntity entities/ExplosionEntity.cpp entities/ExplosionEntity.hpp)
target_link_libraries(ExplosionEntity Entity Resources Sprite)
add_library(FireEntity entities/FireEntity.cpp entities/FireEntity.hpp)
target_link_libraries(FireEntity Entity Sprite)
add_library(LaserEntity entities/LaserEntity.cpp entities/LaserEntity.hpp)
target_link_libraries(LaserEntity Entity Tower)

#Tower Entities
add_library(Bullet towers/entities/Bullet.cpp towers/entities/Bullet.hpp)
target_link_libraries(Bullet Entity)
add_library(FlameRing towers/entities/FlameRing.cpp towers/entities/FlameRing.hpp)
target_link_libraries(FlameRing Entity)
add_library(Rocket towers/entities/Rocket.cpp towers/entities/Rocket.hpp)
target_link_libraries(Rocket Entity)
add_library(FlameRingTower towers/FlameRingTower.cpp towers/FlameRingTower.hpp)
#Towers
add_library(RocketTower towers/RocketTower.cpp towers/RocketTower.hpp)
target_link_libraries(RocketTower Tower)
add_library(SniperTower towers/SniperTower.cpp towers/SniperTower.hpp)
target_link_libraries(SniperTower Tower LaserEntity FireEntity Sprite Resources)
add_library(SoldierTower towers/SoldierTower.cpp towers/SoldierTower.hpp)
target_link_libraries(SoldierTower Tower)
add_library(ShotgunTower towers/ShotgunTower.cpp towers/ShotgunTower.hpp)
target_link_libraries(ShotgunTower Tower)

#TowerManagers
add_library(BasicTowerManager towerManagers/BasicTowerManager.cpp towerManagers/BasicTowerManager.hpp)
target_link_libraries(BasicTowerManager TowerManager TowerType FlameRingTower RocketTower SniperTower SoldierTower ShotgunTower)

# Executable
add_executable(TowerDefense main.cpp)
target_link_libraries(TowerDefense
    Vec
    Entity
    Enemy
    Entity
    Game
    MapManager
    Resources
    Sprite
    Tooltip
    Tower
    TowerManager
    TowerType

    BasicEnemy
    InhibitorEnemy
    InmortalEnemy

    ExplosionEntity
    FireEntity
    LaserEntity

    BasicTowerManager

    FlameRingTower
    RocketTower
    SniperTower
    SoldierTower
    Bullet
    FlameRing
    Rocket
    ${CONAN_LIBS})

