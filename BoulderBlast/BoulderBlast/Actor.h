#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Base : public GraphObject {
public:
    Base (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething() = 0;
    bool isAlive ();
    void setAliveorDead (bool alive);
    StudentWorld* getWorld() ;
    int getHealth ();
    void setHealth (int hp);
    void changeHealth(int howMuch);
    virtual bool isBlocked();
    virtual bool isAttackable();
    virtual void damage();
    virtual ~Base() = 0;
    string getClass();

private:
//    int m_IID;
//    Direction m_dir;
    int m_health;
    bool m_alive;
    StudentWorld* m_world;
    string m_name;
};

class Actor : public Base {
public:
    Actor (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething () = 0;
};

class Object : public Base {
public:
    Object (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething () = 0;
};

class Player : public Actor {
public:
    Player (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething ();
    virtual bool isAttackable();
    void keyPressMovement(int x, int y, Direction dir);
    virtual void damage();
    virtual bool isBlocked();
};

class Robot : public Actor {
public:
    Robot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual bool isAttackable();
    virtual bool isBlocked();
    int getTicks();
    void incrementTicksByOne();
    bool linearMove();
    bool moveWithSpecifiedDirection(Direction dir);
    bool isCorrectTick();
    bool shoot();
    virtual void doSomething() = 0;
private:
    int m_ticksPassed = 0;
};

class SnarlBot : public Robot {
public:
    SnarlBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual void damage();
};

class KleptoBot : public Robot {
public:
    KleptoBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    Direction randomDirectionGenerator();
    void setDistanceBeforeTurning(int rand);
    int getDistanceBeforeTurning();
    bool pickedUpAGoody();
    bool getHoldingGoody();
    string getGoodyType();
    bool moveWithoutObstacles();
    bool getFoundObstacle();
    bool moveWithObstacles();

private:
    int distanceBeforeTurning = 0;
    bool m_pickedUpGoody = false;
    string goodyType;
    bool foundObstacle = false;
    int distanceMoved = 0;
    bool consideredRight = false;
    bool consideredLeft = false;
    bool consideredUp = false;
    bool consideredDown = false;

};

class RegularKleptoBot : public KleptoBot {
public:
    RegularKleptoBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual void damage();

};

class AngryKleptoBot: public KleptoBot {
public:
    AngryKleptoBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void damage();
    virtual void doSomething();
};


class Factory : public Object {
public:
    Factory (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name, string type);
    virtual bool isAttackable();
    virtual void doSomething();
    virtual bool isBlocked();
    int getKleptos(int x, int y);
    bool createKlepto();
private:
    string m_typeOfFactory;
    int m_count;
};


class Bullet : public Object {
public:
    Bullet (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
    void move();
};

class Exit : public Object {
public:
    Exit (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
};

class Wall : public Object {
public:
    Wall (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
    virtual bool isAttackable();
};

class Boulder : public Object {
public:
    Boulder (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
    virtual bool isAttackable();
    void push(int x, int y);
    virtual void damage();
};

class Hole : public Object {
public:
    Hole (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
};

class Goody : public Object {
public:
    Goody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
};

class Jewel : public Goody {
public:
    Jewel (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
};


class RestoreHealthGoody : public Goody {
public:
    RestoreHealthGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
};

class ExtraLifeGoody : public Goody {
public:
    ExtraLifeGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
};

class AmmoGoody : public Goody {
public:
    AmmoGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name);
    virtual void doSomething();
};




#endif // ACTOR_H_
