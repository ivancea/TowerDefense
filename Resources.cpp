#include "Resources.h"

namespace Resources{

    sf::Texture fire;
    sf::Texture explosion;
    sf::Texture sniperTower;

    void loadAll(){
        fire.loadFromFile("resources/sprites/fire.png");
        explosion.loadFromFile("resources/sprites/explosion.png");
        sniperTower.loadFromFile("resources/sprites/sniperTower.png");
    }

}
