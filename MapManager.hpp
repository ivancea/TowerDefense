#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <fstream>

#include "Vec.hpp"

namespace MapManager{
    int save(std::vector< std::vector<bool> > tileMap, int pixelsPerSquare, std::vector<Vec2i> pathPoints, std::string fileName);
    int load(std::vector< std::vector<bool> >& tileMap, int& pixelsPerSquare, std::vector<Vec2i>& pathPoints, std::string fileName);
}

#endif // MAPMANAGER_H
