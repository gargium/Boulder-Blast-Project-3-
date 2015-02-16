#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor (int IID, int x, int y, Direction dir) : GraphObject (IID, x, y, dir) {
        
    }
    int getHealth () {
        return m_health;
    }
    void setHealth (int hp) {
        m_health = hp;
    }
    int getAmmo () {
        return m_ammo;
    }
    void setAmmo (int ammo) {
        m_ammo = ammo;
    }
    
private:
    int m_health;
    int m_ammo;
    
};

class Object : public GraphObject {
public:
    Object (int IID, int x, int y, Direction dir) : GraphObject (IID, x, y, dir) {
        
    }
};

class Player : public Actor {
    Player (int IID, int x, int y, Direction dir) : Actor (IID, x, y, dir) {
        moveTo(x, y);
        setHealth(20);
        setAmmo(20);
        dir = right;
        setVisible(true);
    }
};

class SnarlBot : Actor {
    
};

class HorizontalSnarlBot : SnarlBot {
    
};

class VerticalSnarlBot : SnarlBot {
    
};

class KleptoBot : Actor {
    
};

class AngryKleptoBot: KleptoBot {
    
};


class Factory : Object {
    
};

class RegularFactory : Factory {
    
};

class AngryFactory : Factory {
    
};

class Bullet : Object {
    
};

class Exit : Object {
    
};

class Wall : Object {
    
};

class Boulder : Object {
    
};

class Hole : Object {
    
};

class Jewel : Object {
    
};

class Goody : Object {
    
};

class RestoreHealthGoody : Goody {
    
};

class ExtraLifeGoody : Goody {
    
};

class AmmoGoody : Goody {
    
};

/* 
 The Player’s avatar
 • SnarlBots (Horizontal and Vertical varieties)
 • KleptoBots
 • Angry KleptoBots
 • Factories (for Regular and Angry KleptoBots)
 • Bullets (that can be shot by both the Player and robots)
 • The Exit for the level
 • Walls
 • Boulders
 • Holes
 • Jewels
 • Restore Health Goodies
 • Extra Life Goodies
 • Ammo Goodies
*/





#endif // ACTOR_H_
