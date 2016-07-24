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
#include "Tooltip.h"

///Towers (TEMPORAL, will be replaced by TowerManager)
#include "towers/SoldierTower.h"
#include "towers/RocketTower.h"
#include "towers/SniperTower.h"
#include "towers/FlameRingTower.h"

using namespace std;

void initializeGame(){
    vector< vector<bool> > tileMap;
    int n = MapManager::load(tileMap, Game::pixelsPerSquare, Game::enemiesRoute, "map.tdm");

    /// Always after initialize Game::pixelsPerSquare
    Game::towerManager = new BasicTowerManager();

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
    Game::tickCount = 0;
}

void freeGame(){
    if(Game::towerManager != nullptr)
        delete Game::towerManager;
    Game::clearEnemies();
    Game::clearEntities();
    Game::clearTowers();
}

void setTooltip(Tooltip*& tooltip, Vec2i mouse){
    Vec2i p = Vec2i(mouse.x,mouse.y)/Game::pixelsPerSquare;
    bool mustDelete = true;

    if(Game::map.size()>p.x && p.x>=0
    && Game::map[p.x].size()>p.y && p.y>=0
    && Game::map[p.x][p.y] == Game::TileType::TowerTile){
        Tower* tower = Game::getTower(p);
        if(tower!=nullptr){
            TowerType* tt = Game::towerManager->getTowerType(tower->getId());
            if(tt!=nullptr){
                if(tooltip==nullptr)
                    tooltip = new Tooltip();
                tooltip->setPoint(mouse);
                tooltip->setTitle(tt->name);
                tooltip->setBody(tt->description + "\n\nCost: " + to_string(tt->cost));
                mustDelete = false;
            }
        }
    }

    if(tooltip!=nullptr && mustDelete){
        delete tooltip;
        tooltip = nullptr;
    }
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


    sf::IntRect towersPanel(sf::Vector2i(Game::map.size()*Game::pixelsPerSquare,100),
                            Game::towerManager->getDrawRectSize()),
                upgradesPanel(0,Game::map[0].size()*Game::pixelsPerSquare,
                              towersPanel.left+towersPanel.width,200);


    window.create(sf::VideoMode(upgradesPanel.left+upgradesPanel.width,
                                upgradesPanel.top+upgradesPanel.height), "Tower Defense", sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);


    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glOrtho(0,window.getSize().x, window.getSize().y,0, 0,1);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool paused = false;

    Tooltip* tooltip = nullptr;

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
                setTooltip(tooltip, mouse);
                break;
            case sf::Event::KeyPressed:
                keys[ev.key.code] = true;
                if(ev.key.code == sf::Keyboard::Space){
                    paused = !paused;
                }else if(ev.key.code == sf::Keyboard::Return){
                    Game::clearEnemies();
                    Game::clearEntities();
                    Game::clearTowers();
                    Game::life = 20;
                    Game::money = 1500;
                    Game::tickCount = 0;
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
                                    t = Game::towerManager->getTowerType(1)->model->clone();//new SoldierTower();
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
                setTooltip(tooltip, mouse);
                break;
            default:
                break;
            }
        }

        window.clear();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        window.pushGLStates();
            sf::RectangleShape rect;
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setFillColor(sf::Color::Green);
            rect.setPosition(upgradesPanel.left, upgradesPanel.top);
            rect.setSize(sf::Vector2f(upgradesPanel.width, upgradesPanel.height));
            window.draw(rect);
        window.popGLStates();

        Game::towerManager->drawTowersPanel(&window, sf::Vector2i(towersPanel.left,towersPanel.top));

        Game::draw(&window);

        if(tooltip!=nullptr)
            tooltip->draw(&window);

        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));

        if(!paused){
            if(Game::tick())
                running = false;
        }
    }
    window.close();
    freeGame();
}
