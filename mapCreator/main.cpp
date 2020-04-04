#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "MapManager.hpp"
#include "Vec.hpp"

using namespace std;

vector< vector<bool> > tileMap;
vector<Vec2i> pathPoints;
int pixelsPerSquare;

void draw(sf::RenderWindow* window){
    for(int i=0; i<tileMap.size(); i++)
        for(int j=0; j<tileMap[i].size(); j++){
            if(tileMap[i][j] == 0)
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
        glColor3ub(0,0,0);
        int sizeX = tileMap.size(),
            sizeY = tileMap[0].size();
        glBegin(GL_LINES);
        for(int i=0; i<=sizeX; i++){
            glVertex2i(i*pixelsPerSquare, 0);
            glVertex2i(i*pixelsPerSquare, sizeX*pixelsPerSquare);

            glVertex2i(0, i*pixelsPerSquare);
            glVertex2i(sizeX*pixelsPerSquare, i*pixelsPerSquare);
        }
        glEnd();

        glColor3ub(255,0,0);
        glBegin(GL_LINES);
            auto it1 = pathPoints.begin(),
                 it2 = pathPoints.begin();
            it2++;
            for(; it1!=pathPoints.end() && it2!=pathPoints.end(); it1++,it2++){
                glVertex2i(it1->x, it1->y);
                glVertex2i(it2->x, it2->y);
            }
        glEnd();
        glColor3ub(0,0, 255);
        for(Vec2i p : pathPoints){
            glBegin(GL_POLYGON);
                glVertex2i(p.x-2, p.y-2);
                glVertex2i(p.x-2, p.y+2);
                glVertex2i(p.x+2, p.y+2);
                glVertex2i(p.x+2, p.y-2);
            glEnd();
            glColor3ub(255,0,0);
        }
}


int main(){
    bool running = true;
    sf::RenderWindow window;
    Vec2i mouse;

    bool shiftPressed = false,
         aPressed = false,
         sPressed = false,
         dPressed = false,
         wPressed = false;

    do{
        cin.clear();
        cout << "Map WIDTH, HEIGHT, and pixels per square: ";
        cin >> mouse.x >> mouse.y >> pixelsPerSquare;
    }while(cin.fail() || mouse.x<=0 || mouse.y<=0 || pixelsPerSquare<=0);

    for(int i=0; i<mouse.x; i++)
        tileMap.push_back(vector<bool>(mouse.y, true));

    mouse.x = mouse.y = -1;

    cout << "Left click for set or unset road tiles." << endl;
    cout << "Right click for set a path point." << endl;
    cout << "Space for delete the last path point." << endl;
    cout << "Alt+click for center path point in a tile." << endl;
    cout << "A/W/S/D+click for center a path point in a tile side." << endl << endl;
    cout << "Finally, press ENTER for save (saved or overwritten in file \"map.tdm\")" << endl;

    window.create(sf::VideoMode(tileMap.size()*pixelsPerSquare,
                                tileMap[0].size()*pixelsPerSquare), "Map Creator", sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);

    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glOrtho(0,window.getSize().x, window.getSize().y,0,0,1);
    glMatrixMode(GL_PROJECTION);

    int tickCount = 0;

    double lastLife = 0;

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
                switch(ev.key.code){
                case sf::Keyboard::Space:
                    if(pathPoints.size()>0)
                        pathPoints.pop_back();
                    break;
                case sf::Keyboard::Return:
                    if(pathPoints.size()<=1){
                        cout << "2 or more path points needed." << endl;
                    }else{
                        int n = MapManager::save(tileMap, pixelsPerSquare, pathPoints, "map.tdm");
                        n = MapManager::load(tileMap, pixelsPerSquare, pathPoints, "map.tdm");
                        if(n!=0){
                            cout << "Couldn't save. Error: " << n << endl;
                        }else{
                            cout << "Map saved into \"map.tdm\"" << endl;
                        }
                    }
                    break;
                case sf::Keyboard::LShift: shiftPressed = true; break;
                case sf::Keyboard::A: aPressed = true; break;
                case sf::Keyboard::S: sPressed = true; break;
                case sf::Keyboard::D: dPressed = true; break;
                case sf::Keyboard::W: wPressed = true; break;
                default:
                    break;
                }
                break;
            case sf::Event::KeyReleased:
                switch(ev.key.code){
                case sf::Keyboard::LShift: shiftPressed = false; break;
                case sf::Keyboard::A: aPressed = false; break;
                case sf::Keyboard::S: sPressed = false; break;
                case sf::Keyboard::D: dPressed = false; break;
                case sf::Keyboard::W: wPressed = false; break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                {
                    if(mouse.x<0 || mouse.x>=window.getSize().x
                    || mouse.y<0 || mouse.y>=window.getSize().y)
                        break;
                    Vec2i p = Vec2i(mouse.x,mouse.y)/pixelsPerSquare;
                    int rad = pixelsPerSquare/2;
                    Vec2i t = p*pixelsPerSquare + Vec2i(rad,rad);
                    if(ev.mouseButton.button == sf::Mouse::Left){
                        if(tileMap.size()>p.x && p.x>=0
                        && tileMap[p.x].size()>p.y && p.y>=0){
                            tileMap[p.x][p.y] = !tileMap[p.x][p.y];
                        }
                    }else if(ev.mouseButton.button == sf::Mouse::Right){
                        if(shiftPressed){
                            pathPoints.push_back(t);
                        }else if(!aPressed && !sPressed && !dPressed && !wPressed){
                            pathPoints.push_back(mouse);
                        }else{
                            if(aPressed)
                                t.x -= rad;
                            else if(dPressed)
                                t.x += rad;
                            if(wPressed)
                                t.y -= rad;
                            else if(sPressed)
                                t.y += rad;
                            pathPoints.push_back(t);
                        }
                        if(pathPoints.size()>=2 && pathPoints.back()==pathPoints[pathPoints.size()-2]){
                            pathPoints.pop_back();
                            cout << "Error: point equal to last point." << endl;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        window.clear();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        draw(&window);
        window.display();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    window.close();
}
