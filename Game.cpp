#include "Game.hpp"

#include <cmath>
#include <string>

#include "Resources.hpp"

#include "entities/ExplosionEntity.hpp"

/// Enemies (TEMPORAL, will be replaced by some Rounds engine
#include "enemies/BasicEnemy.hpp"
#include "enemies/InhibitorEnemy.hpp"
#include "enemies/InmortalEnemy.hpp"


namespace Game{

    namespace Stats{

        unsigned int enemiesKilled = 0;

    }

    std::unique_ptr<TowerManager> towerManager;
    std::list<std::unique_ptr<Tower>> towers;
    std::list<std::unique_ptr<Enemy>> enemies;
    std::list<std::unique_ptr<Entity>> entities;

    std::vector<Vec2i> enemiesRoute;
    std::vector< std::vector<TileType> > map;
    int pixelsPerSquare = 0;

    double life = 0;
    int money = 0;

    int tickCount = 0;
    int velocity = 1;

    Tower* selectedTower;

    bool tick(){
        for(unsigned int i=0; i<velocity; i++){ // TODO: Put here new enemies with RoundsManager
            auto it1 = enemies.begin();
            while(it1 != enemies.end()){
                bool lost = life<=0;
                auto& e = *it1;
                if(e->tick()){
                    life -= e->getDamage();
                    it1 = enemies.erase(it1);
                }else it1++;

                if(life<=0 && !lost){
                    money = 0;
                    clearEntities();

                    for(auto& t:towers){
                        entities.emplace_back(std::make_unique<ExplosionEntity>(getRealPosition(t->getPosition()), pixelsPerSquare, 200));
                    }

                    clearTowers();
                }
            }
            auto it2 = entities.begin();
            while(it2 != entities.end()){
                auto& e = *it2;
                if(e->tick()){
                    it2 = entities.erase(it2);
                }else it2++;
            }
            for(auto& t : towers){
                t->tick();
            }

            if(life>0){
                if(tickCount%400 == 1)
                    enemies.emplace_back(std::make_unique<InhibitorEnemy>(1.0, 30+tickCount/500, 1));
                else if(tickCount%20 == 1)
                    enemies.emplace_back(std::make_unique<BasicEnemy>(1.0 + (double)(rand()%10)/10.0, 15+tickCount/500, 1));
            }
            ++tickCount;
        }

        return false;
    }

    void draw(sf::RenderWindow* window){
        for(int i=0; i<map.size(); i++)
            for(int j=0; j<map[i].size(); j++){
                if(map[i][j] == TileType::RoadTile)
                    glColor3ub(220,220,220);
                else
                    glColor3ub(0,255,0);
                glBegin(GL_POLYGON);
                    glVertex2i(i*pixelsPerSquare, j*pixelsPerSquare);
                    glVertex2i((i+1)*pixelsPerSquare, j*pixelsPerSquare);
                    glVertex2i((i+1)*pixelsPerSquare, (j+1)*pixelsPerSquare);
                    glVertex2i(i*pixelsPerSquare, (j+1)*pixelsPerSquare);
                glEnd();
            }
        if(map.size()>=1){
            glLineWidth(1.0);
            glColor3ub(0,0,0);
            int sizeX = map.size(),
                sizeY = map[0].size();
            glBegin(GL_LINES);
            for(int i=0; i<=sizeX; i++){
                glVertex2i(i*pixelsPerSquare, 0);
                glVertex2i(i*pixelsPerSquare, sizeY*pixelsPerSquare);

                glVertex2i(0, i*pixelsPerSquare);
                glVertex2i(sizeX*pixelsPerSquare, i*pixelsPerSquare);
            }
            glEnd();
        }

        for(auto& e : enemies)
            e->draw(window);
        for(auto& e : entities)
            e->draw(window);
        for(auto& t : towers)
            t->draw(window);

        for(auto& e : enemies)
            e->draw(window);
        for(auto& e : entities)
            e->drawOver(window);
        for(auto& t : towers)
            t->drawOver(window);

        if(selectedTower){
            if(exists(selectedTower)){
                Vec2i p = Vec2i(((double)selectedTower->getPosition().x+0.5)*pixelsPerSquare,
                                ((double)selectedTower->getPosition().y+0.5)*pixelsPerSquare);
                glLineWidth(1.0);
                glColor3ub(255,0,0);
                if(selectedTower->getMinRange()>0){
                    glBegin(GL_LINE_LOOP);
                        for(float i=0; i<PI*2.0; i+=PI/360)
                            glVertex2i(p.x+sin(i)*selectedTower->getMinRange(), p.y+cos(i)*selectedTower->getMinRange());
                    glEnd();
                }
                if(selectedTower->getMaxRange()>0){
                    glBegin(GL_LINE_LOOP);
                        for(float i=0; i<PI*2.0; i+=PI/360)
                            glVertex2i(p.x+sin(i)*selectedTower->getMaxRange(), p.y+cos(i)*selectedTower->getMaxRange());
                    glEnd();
                }

                glLineWidth(3.0);
                glColor3ub(0,0,0);
                glBegin(GL_LINE_LOOP);
                    glVertex2i(selectedTower->getPosition().x*pixelsPerSquare,selectedTower->getPosition().y*pixelsPerSquare);
                    glVertex2i((selectedTower->getPosition().x+1)*pixelsPerSquare,selectedTower->getPosition().y*pixelsPerSquare);
                    glVertex2i((selectedTower->getPosition().x+1)*pixelsPerSquare,(selectedTower->getPosition().y+1)*pixelsPerSquare);
                    glVertex2i(selectedTower->getPosition().x*pixelsPerSquare,(selectedTower->getPosition().y+1)*pixelsPerSquare);
                glEnd();
            }else{
                selectedTower = nullptr;
            }
        }

        window->pushGLStates();

            sf::Font fontArial;
            sf::Text text;
            fontArial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
            text.setFont(fontArial);
            if(life>0)
                text.setString("Lifes: " + std::to_string((int)life));
            else
                text.setString("Score: " + std::to_string(Stats::enemiesKilled));
            text.setColor(sf::Color::White);
            text.setCharacterSize(20);
            sf::FloatRect bounds = text.getGlobalBounds();
            text.setPosition(window->getSize().x-bounds.width-10, 10);
            window->draw(text);

            text.setString("Money: " + std::to_string(money));
            text.setColor(sf::Color(255,255,150));
            text.setCharacterSize(20);
            bounds = text.getGlobalBounds();
            text.setPosition(window->getSize().x-bounds.width-10, 50);
            window->draw(text);

            text.setString("Pause (Space)");
            text.setColor(sf::Color(200,255,200));
            text.setCharacterSize(20);
            bounds = text.getGlobalBounds();
            text.setPosition(window->getSize().x-bounds.width-10, 250);
            window->draw(text);

            text.setString("Restart (Enter)");
            text.setColor(sf::Color(200,200,200));
            text.setCharacterSize(20);
            bounds = text.getGlobalBounds();
            text.setPosition(window->getSize().x-bounds.width-10, 310);
            window->draw(text);

        window->popGLStates();
    }


    /// HELPERS

    Tower* getTower(Vec2i position){
        for(auto& t: towers)
            if(t->getPosition()==position)
                return t.get();
        return nullptr;
    }

    bool putTower(std::unique_ptr<Tower>& tower){
        Vec2i p = tower->getPosition();
        if(map.size()>p.x && p.x>=0
        && map[p.x].size()>p.y && p.y>=0
        && map[p.x][p.y]==TileType::EmptyTile){ /// TODO: Is occupied?
            Game::towers.emplace_back(std::move(tower));
            map[p.x][p.y] = TileType::TowerTile;
            return true;
        }
        return false;
    }

    std::list<std::unique_ptr<Tower>>::iterator removeTower(std::list<std::unique_ptr<Tower>>::iterator tower){
        Vec2i p = (*tower)->getPosition();
        if(map.size()>p.x && p.x>=0
        && map[p.x].size()>p.y && p.y>=0
        && map[p.x][p.y]==TileType::TowerTile)
            map[p.x][p.y] = TileType::EmptyTile;
        return towers.erase(tower);
    }

    boolean removeTower(Vec2i position){
        for(auto it = towers.begin(); it!= towers.end(); it++)
            if((*it)->getPosition()==position){
                removeTower(it);
                return true;
            }
        return false;
    }

    std::list<std::unique_ptr<Enemy>>::iterator kill(std::list<std::unique_ptr<Enemy>>::iterator enemy){
        (*enemy)->killed();
        ++Stats::enemiesKilled;
        return enemies.erase(enemy);
    }

    bool isInRange(Vec2d position, double minRange, double maxRange, Enemy* enemy){
        if(maxRange<0)
            return true;
        if(maxRange<minRange)
            return false;
        double d = position.distance(enemy->getPosition());
        return d<=maxRange && d>=minRange;
    }

    std::list<std::unique_ptr<Enemy>>::iterator findTarget(Tower* tower){
        auto it = enemies.end();
        int index = -1;
        double t = -1;

        Vec2d p = Vec2i(((double)tower->getPosition().x+0.5)*Game::pixelsPerSquare,
                        ((double)tower->getPosition().y+0.5)*Game::pixelsPerSquare);

        switch(tower->getPriority()){
        case Last:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                auto& e = *it2;
                if(e->getDistanceToEnd()>0 && (t<0 || e->getDistanceToEnd()>t)){
                    t = e->getDistanceToEnd();
                    it = it2;
                }
            }
            break;
        case Near:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double d = (*it2)->getPosition().distance(p);
                if(t<0 || d<t){
                    it = it2;
                    t = d;
                }
            }
            break;
        case Far:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double d = (*it2)->getPosition().distance(p);
                if(t<0 || d>t){
                    it = it2;
                    t = d;
                }
            }
            break;
        case MoreLife:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double l = (*it2)->getLife();
                if(l>0 && (t<0 || l>t)){
                    it = it2;
                    t = l;
                }
            }
            break;
        case LessLife:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double l = (*it2)->getLife();
                if(l>0 && (t<0 || l<t)){
                    it = it2;
                    t = l;
                }
            }
            break;
        case MoreDamage:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double d = (*it2)->getDamage();
                if(d>0 && (t<0 || d>t)){
                    it = it2;
                    t = d;
                }
            }
            break;
        case LessDamage:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                double d = (*it2)->getDamage();
                if(d>0 && (t<0 || d<t)){
                    it = it2;
                    t = d;
                }
            }
            break;
        case MoreEnemiesTogether:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                Vec2d p = (*it2)->getPosition();
                int count = 0;
                for(auto it3=Game::enemies.begin(); it3!=Game::enemies.end(); it3++){
                    if(p.distance((*it3)->getPosition())<=Game::pixelsPerSquare)
                        ++count;
                }
                if(count>t){
                    it = it2;
                    t = count;
                }
            }
            break;
        case First:
        case Default:
        default:
            for(auto it2=Game::enemies.begin(); it2!=Game::enemies.end(); it2++){
                if(!isInRange(p, tower->getMinRange(), tower->getMaxRange(), it2->get()))
                    continue;
                auto& e = *it2;
                if(e->getDistanceToEnd()>0 && (t<0 || e->getDistanceToEnd()<t)){
                    t = e->getDistanceToEnd();
                    it = it2;
                }
            }
            break;
        }

        return it;
    }

    std::list< std::list<std::unique_ptr<Enemy>>::iterator > findEnemiesInRange(Vec2d position, double minRange, double maxRange){
        std::list< std::list<std::unique_ptr<Enemy>>::iterator > ret;
        for(auto it = enemies.begin();  it!=enemies.end(); it++){
            if(isInRange(position, minRange, maxRange, it->get()))
                ret.push_back(it);
        }
        return ret;
    }


    bool exists(Enemy* enemy){
        if(enemy == nullptr)
            return false;
        for(auto& e : enemies)
            if(e.get()==enemy)
                return true;
        return false;
    }

    bool exists(Tower* tower){
        if(tower == nullptr)
            return false;
        for(auto& t : towers)
            if(t.get()==tower)
                return true;
        return false;
    }

    bool exists(Entity* entity){
        if(entity == nullptr)
            return false;
        for(auto& e : entities)
            if(e.get()==entity)
                return true;
        return false;
    }


    void clearTowers(){
        for(auto it = towers.begin(); it!=towers.end();){
            it = removeTower(it);
        }
    }

    void clearEntities(){
        entities.clear();
    }

    void clearEnemies(){
        enemies.clear();
    }

    void killEnemies(){
        for(auto it = enemies.begin(); it!=enemies.end();)
            it = kill(it);
    }

    double getDistance(Vec2i towerPosition, Vec2d position){
        return position.distance(Vec2d((towerPosition.x+0.5)*Game::pixelsPerSquare,
                                 (towerPosition.y+0.5)*Game::pixelsPerSquare));
    }

    Vec2d getRealPosition(Vec2i towerPosition){
        return Vec2d(towerPosition.x*Game::pixelsPerSquare+Game::pixelsPerSquare/2,
                     towerPosition.y*Game::pixelsPerSquare+Game::pixelsPerSquare/2);
    }

}
