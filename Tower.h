#ifndef TOWER_H
#define TOWER_H

class Tower;

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Vec.hpp"

enum TowerEvent{
    None
};

enum Priority{
    Default,
    First,
    Last,
    Near,
    Far,
    MoreLife,
    LessLife,
    MoreDamage,
    LessDamage,
    MoreEnemiesTogether
};


class Tower{

protected:
    int _id;

    int _ticksForShoot;
    int _ticksBetweenShoots;

    Vec2i _position;
    Priority _priority;

    double _minRange,
           _maxRange;

public:
    Tower() : _priority(Default){}
    virtual ~Tower() {};

    int getId() const { return _id; }
    void setId(int id) { _id = id; }

    int getTicksForShoot() const { return _ticksForShoot; }
    void setTicksForShoot(int ticksForShoot) { _ticksForShoot = ticksForShoot; }
    int getTicksBetweenShoots() const { return _ticksBetweenShoots; }
    void setTicksBetweenShoots(int ticksBetweenShoots) { _ticksBetweenShoots = ticksBetweenShoots; }

    Vec2i getPosition() const { return _position; }
    void setPosition(Vec2i position) { _position = position; }
    Priority getPriority() const { return _priority; }
    void setPriority(Priority priority){ _priority = priority; }

    double getMinRange() const { return _minRange; }
    void setMinRange(double minRange){ _minRange = minRange; }
    double getMaxRange() const { return _maxRange; }
    void setMaxRange(double maxRange){ _maxRange = maxRange; }

    virtual TowerEvent tick() = 0;
    virtual void draw(sf::RenderWindow* window) const {};
    virtual void drawOver(sf::RenderWindow* window) const {};
};

#endif // TOWER_H
