#ifndef TOWER_H
#define TOWER_H

class Tower;

#include <SFML/Graphics.hpp>

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
    Tower();
    virtual ~Tower() {};

    int getId() const { return _id; }
    void setId(int id) { _id = id; }

    int getTicksForShoot() const { return _ticksForShoot; }
    virtual void setTicksForShoot(int ticksForShoot) { _ticksForShoot = ticksForShoot; }
    int getTicksBetweenShoots() const { return _ticksBetweenShoots; }
    virtual void setTicksBetweenShoots(int ticksBetweenShoots) { _ticksBetweenShoots = ticksBetweenShoots; }

    Vec2i getPosition() const { return _position; }
    virtual void setPosition(Vec2i position) { _position = position; }
    Priority getPriority() const { return _priority; }
    virtual void setPriority(Priority priority){ _priority = priority; }

    double getMinRange() const { return _minRange; }
    virtual void setMinRange(double minRange){ _minRange = minRange; }
    double getMaxRange() const { return _maxRange; }
    virtual void setMaxRange(double maxRange){ _maxRange = maxRange; }

    virtual TowerEvent tick() = 0;
    virtual void draw(sf::RenderWindow* window) const;
    virtual void drawOver(sf::RenderWindow* window) const;

    virtual void draw(sf::RenderWindow* window, Vec2d point) const {};
    virtual void drawOver(sf::RenderWindow* window, Vec2d point) const {};

    virtual std::unique_ptr<Tower> clone() const = 0;
};

#endif // TOWER_H
