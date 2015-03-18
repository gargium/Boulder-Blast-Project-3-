#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h" 
#include "Level.h"
#include <string>
#include <list>
#include "StudentWorld.h"

using namespace std;
class Base;
class Bullet;
class Player;
class Exit;
class KleptoBot;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld(); 
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void updateDisplayText();
    Base* getObject(int x, int y);
    Base* getObjectNotAt(int x, int y, string ID);
    StudentWorld* getStudentWorld();
    int getAmmo ();
    void incAmmo (int howMuch);
    void addBullet (Bullet* bullet);
    void addKlepto (KleptoBot* k);
    void setExitVisible(Exit* e, bool yesOrNo);
    bool areThereJewelsLeft();
    unsigned int getBonus();
    void decBonus();
    void setBonus(int number);
    bool getPlayerDead();
    void setCompletedLevel(bool isHeDone);
    bool getCompletedLevel();
    bool areObstaclesInBetweenRobotAndPlayer(GraphObject::Direction dir, int x, int y, int px, int py);
    bool isObjectInRowOrColumn(GraphObject::Direction dir, int x, int y, string ID);
    bool isBotFacingPlayer(GraphObject::Direction dir, int x, int y, int px, int py);
    int getPlayerX();
    int getPlayerY();
    void createGoody(int x, int y, string type);
    string levelLoader();

private:
    std::list<Base*> AssetList;
    int m_ammo = 20;
    int m_numJewels = 0;
    Player* m_player;
    Exit* m_exit;
    unsigned int m_bonus = 1000;
    bool m_playerCompletedLevel = false;
};

#endif // STUDENTWORLD_H_
