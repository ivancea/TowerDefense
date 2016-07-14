#include "Resources.h"

namespace Resources{

    sf::Texture fire;
    sf::Texture explosion;

    void loadAll(){
        fire.loadFromFile("resources/sprites/fire.png");
        explosion.loadFromFile("resources/sprites/explosion.png");
    }

}
