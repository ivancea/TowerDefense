#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>

namespace Resources{

    extern sf::Texture fire; // 8x4, 64x128 pixels per frame
    extern sf::Texture explosion; // 6x7, 100x100 pixels per frame, 37 frames

    void loadAll();

};

#endif // RESOURCES_H