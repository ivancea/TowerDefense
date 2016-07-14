#include <iostream>
#include <map>
#include <cmath>
#include <ctime>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game.h"
#include "Resources.h"
#include "MapManager.h"
#include "BasicTowerManager.h"

///Towers (TEMPORAL, will be replaced by TowerManager)
#include "towers/SoldierTower.h"
#include "towers/RocketTower.h"
#include "towers/SniperTower.h"
#include "towers/FlameRingTower.h"

/// Enemies (TEMPORAL, will be replaced by some Rounds engine
#include "enemies/BasicEnemy.h"
#include "enemies/InhibitorEnemy.h"
#include "enemies/InmortalEnemy.h"

using namespace std;

void initializeGame(){
    Game::towerManager = new BasicTowerManager();
    vector< vector<bool> > tileMap;
    int n = MapManager::load(tileMap, Game::pixelsPerSquare, Game::enemiesRoute, "map.tdm");
    if(n==0){
        Game::map.resize(tileMap.size(), vector<Game::TileType>(tileMap[0].size(), Game::TileType::EmptyTile));
        for(int i=0; i<tileMap.size(); i++)
            for(int j=0; j<tileMap[i].size(); j++)
                if(!tileMap[i][j])
                    Game::map[i][j] = Game::TileType::RoadTile;
    }else{
        cout << "Error loading map \"map.tdm\". Error: " << n << endl;
        cout << "Loading default map." << endl;

        Game::pixelsPerSquare = 50;
        Game::enemiesRoute.push_back(Vec2i(0,25));
        Game::enemiesRoute.push_back(Vec2i(475,25));
        Game::enemiesRoute.push_back(Vec2i(475,500));
        for(int i=0; i<10; i++)
            Game::map.push_back(vector<Game::TileType>(10, Game::TileType::EmptyTile));
        for(int i=0; i<10; i++){
            Game::map[i][0] = Game::TileType::RoadTile;
            Game::map[9][i] = Game::TileType::RoadTile;
        }

        Tower* t = new SniperTower();
        t->setPosition(Vec2i(3,3));
        t->setPriority(Near);
        if(!Game::putTower(t))
            delete t;
        t = new SniperTower();
        t->setPosition(Vec2i(4,5));
        t->setPriority(Last);
        if(!Game::putTower(t))
            delete t;
        t = new SniperTower();
        t->setPosition(Vec2i(5,4));
        if(!Game::putTower(t))
            delete t;
    }

    Game::life = 20;
    Game::money = 1500;

}

void freeGame(){
    delete Game::towerManager;
    for(Enemy* e : Game::enemies)
        delete e;
    Game::enemies.clear();
    for(Tower* t : Game::towers)
        delete t;
    Game::towers.clear();
}

int main(){
    srand(time(0));
    map<sf::Keyboard::Key, bool> keys;
    bool running = true;
    sf::RenderWindow window;
    Vec2i mouse;

    initializeGame();
    if(Game::map.size()==0)
        Game::map.push_back(vector<Game::TileType>(1, Game::TileType::EmptyTile));


    window.create(sf::VideoMode(Game::map.size()*Game::pixelsPerSquare + 200,
                                Game::map[0].size()*Game::pixelsPerSquare), "Tower Defense", sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);

    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glOrtho(0,window.getSize().x, window.getSize().y,0,0,1);
    glMatrixMode(GL_PROJECTION);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Resources::loadAll();

    int tickCount = 0;

    double lastLife = 0;

    bool paused = false;

    while(running && window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            switch(ev.type){
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::MouseMoved:
                mouse.x = ev.mouseMove.x;
                mouse.y = ev.mouseMove.y;
                break;
            case sf::Event::KeyPressed:
                keys[ev.key.code] = true;
                if(ev.key.code == sf::Keyboard::Space){
                    paused = !paused;
                }
                break;
            case sf::Event::KeyReleased:
                keys[ev.key.code] = false;
                break;
            case sf::Event::MouseButtonPressed:
                SetFocus(window.getSystemHandle());
                if(ev.mouseButton.button == sf::Mouse::Left){
                    Vec2i p = Vec2i(mouse.x,mouse.y)/Game::pixelsPerSquare;
                    if(Game::map.size()>p.x && p.x>=0
                    && Game::map[p.x].size()>p.y && p.y>=0){
                        bool mustDeselect = true;
                        if(Game::map[p.x][p.y] == Game::TileType::EmptyTile){
                            Tower* t = nullptr;
                            if(keys[sf::Keyboard::Q]){
                                if(Game::money>=150){
                                    t = new SoldierTower();
                                    Game::money -= 150;
                                }
                            }else if(keys[sf::Keyboard::W]){
                                if(Game::money>=200){
                                    t = new SniperTower();
                                    t->setPriority(MoreLife);
                                    Game::money -= 200;
                                }
                            }else if(keys[sf::Keyboard::E]){
                                if(Game::money>=300){
                                    t = new RocketTower();
                                    t->setPriority(Priority::MoreEnemiesTogether);
                                    Game::money -= 300;
                                }
                            }else if(keys[sf::Keyboard::R]){
                                if(Game::money>=300){
                                    t = new FlameRingTower();
                                    Game::money -= 300;
                                }
                            }
                            if(t!=nullptr){
                                t->setPosition(p);
                                if(!Game::putTower(t))
                                    delete t;
                                else
                                    mustDeselect = false;
                            }
                        }else if(Game::map[p.x][p.y] == Game::TileType::TowerTile){
                            Game::selectedTower = Game::getTower(Vec2i(mouse.x,mouse.y)/Game::pixelsPerSquare);
                            mustDeselect = false;
                        }
                        if(mustDeselect)
                            Game::selectedTower = nullptr;
                    }
                }else if(ev.mouseButton.button == sf::Mouse::Right){
                    Vec2i p = Vec2i(mouse.x,mouse.y)/Game::pixelsPerSquare;
                    if(Game::map[p.x][p.y] == Game::TileType::TowerTile){
                        Tower* t = Game::removeTower(p);
                        if(t==nullptr){
                            cout << "ERROR DELETING TOWER" << endl;
                        }else{
                            Game::money += Game::towerManager->getTowerCost(t->getId());
                            delete t;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }

        clock_t cl = clock();

        window.clear();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        Game::draw(&window);
        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));

        if(tickCount%20==0)
            window.setTitle(("Tower Defense + (" + to_string(1000/((clock()-cl)*1000/CLOCKS_PER_SEC + 1)) + " fps)").c_str());

        if(lastLife != Game::life){
            cout << "Vida: " << Game::life << endl;
            lastLife = Game::life;
            if(lastLife <= 0)
                cout << "DEAD" << endl;
        }
        if(!paused && Game::life>0){
            tickCount += 1;
            if(tickCount%400 == 1)
                Game::enemies.push_back(new InhibitorEnemy(1.0, 30+tickCount/500, 1));
            else if(tickCount%20 == 1)
                Game::enemies.push_back(new BasicEnemy(1.0 + (double)(rand()%10)/10.0, 15+tickCount/500, 1));
                //Game::enemies.push_back(new InmortalEnemy(1.0, 1));
            if(Game::tick())
                running = false;
        }
    }
    window.close();
    freeGame();
}
