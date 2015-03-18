#include "Actor.h"
#include "GameConstants.h"
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
///////////////////////////////////////////////
//////////DESTRUCTOR IMPLEMENTATIONS//////////
///////////////////////////////////////////////
Base::~Base() {
    setVisible(false);
}
///////////////////////////////////////////////
//////////CONSTRUCTOR IMPLEMENTATIONS//////////
///////////////////////////////////////////////

Base:: Base (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : GraphObject (IID, x, y, dir), m_world(studWorld) {
//    m_IID = IID;
//    m_dir = dir;
    setVisible(true);
    m_alive = true;
    m_name = name;
}

Actor:: Actor (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Base (IID, x, y, dir, studWorld, name) {
    
}

Object:: Object (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Base(IID, x, y, dir, studWorld, name) {
    
}

Player:: Player (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Actor(IID = IID_PLAYER, x , y, dir = right, studWorld, name) {
    setHealth(20);
    
}

Wall:: Wall (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID = IID_WALL, x, y, dir = none, studWorld, name) {
}

Boulder:: Boulder (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID = IID_BOULDER, x, y, dir = none, studWorld, name) {
    setHealth(10);
}

Hole:: Hole (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID = IID_HOLE, x, y, dir = none, studWorld, name)  {
    
}

Jewel:: Jewel (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Goody(IID = IID_JEWEL, x , y, dir = none, studWorld, name) {
    
}

Goody:: Goody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID, x, y, dir = none, studWorld, name) {
    
}

RestoreHealthGoody:: RestoreHealthGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Goody(IID = IID_RESTORE_HEALTH, x, y, dir = none, studWorld, name) {
    
}

ExtraLifeGoody:: ExtraLifeGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Goody(IID= IID_EXTRA_LIFE, x , y, dir = none, studWorld, name) {
    
}

AmmoGoody:: AmmoGoody (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Goody(IID = IID_AMMO, x ,y , dir = none, studWorld, name) {
    
}

Bullet:: Bullet (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID = IID_BULLET, x, y, dir, studWorld, name) {
    if (dir == right) {
        moveTo(getX()+1, getY());
    }
    else if (dir == left) {
        moveTo(getX()-1, getY());
    }
    else if (dir == up) {
        moveTo(getX(), getY()+1);
    }
    else if (dir == down) {
        moveTo(getX(), getY()-1);
    }
}

Exit:: Exit (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Object(IID = IID_EXIT, x, y, dir, studWorld, name) {
    setVisible(false);
}

Robot:: Robot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Actor(IID, x, y, dir, studWorld, name) {
}

SnarlBot:: SnarlBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Robot(IID = IID_SNARLBOT, x, y, dir, studWorld, name) {
    setHealth(10);
}


KleptoBot:: KleptoBot(int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : Robot(IID, x, y, dir = right, studWorld, name) {
    setDistanceBeforeTurning((rand() % 6) + 1);
}

RegularKleptoBot:: RegularKleptoBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : KleptoBot(IID = IID_KLEPTOBOT, x, y, dir = right, studWorld, name) {
    setHealth(5);
}

Factory:: Factory (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name, string typeOfFactory) : Object(IID_ROBOT_FACTORY, x, y, dir = none, studWorld, name) {
    m_typeOfFactory = typeOfFactory;
}

AngryKleptoBot:: AngryKleptoBot (int IID, int x, int y, Direction dir, StudentWorld *studWorld, string name) : KleptoBot(IID = IID_ANGRY_KLEPTOBOT, x, y, dir = right, studWorld, name) {
    setHealth(8);
}

//////////////////////////////////////////////
//////////FACTORY MEMBER FUNCTIONS////////////
//////////////////////////////////////////////

bool Factory:: isAttackable() {
    return true;
}

bool Factory:: isBlocked() {
    return true;
}

bool Factory:: createKlepto() {
    bool created = false;
    if (m_typeOfFactory == "angry") {
        AngryKleptoBot *a = new AngryKleptoBot(IID_ANGRY_KLEPTOBOT, getX(), getY(), right, getWorld(), "angry_kleptobot");
        getWorld()->addKlepto(a);
        created = true;
    }
    else if (m_typeOfFactory == "regular") {
        RegularKleptoBot *r = new RegularKleptoBot(IID_ANGRY_KLEPTOBOT, getX(), getY(), right, getWorld(), "regular_kleptobot");
        getWorld()->addKlepto(r);
        created = true;
    }
    return created;
}

int Factory:: getKleptos(int x, int y) {
    m_count = 0;
    int upperBound = y + 3;
    int lowerBound = y - 3;
    int leftBound = x - 3;
    int rightBound = x + 3;
    
    if (upperBound >= VIEW_HEIGHT) upperBound = VIEW_HEIGHT - 1;
    if (lowerBound <= 0) lowerBound = 0;
    if (leftBound <= 0) leftBound = 0;
    if (rightBound >= VIEW_WIDTH) rightBound = VIEW_WIDTH - 1;
    
    for (int i = lowerBound; i <= upperBound; i++) {
        for (int j = leftBound; j <= rightBound; j++) {
            if (getWorld()->getObject(i, j)) {
                if (getWorld()->getObject(i, j)->getClass() == "regular_kleptobot" ||
                    getWorld()->getObject(i, j)->getClass() == "angry_kleptobot") {
                    m_count++;
                }
            }
        }
    }
    return m_count;
}

void Factory:: doSomething() {
    if (getKleptos(getX(), getY()) < 3
        && (getWorld()->getObject(getX(), getY())->getClass() != "angry_kleptobot")
        && (getWorld()->getObject(getX(), getY())->getClass() != "regular_kleptobot")) {
        if (rand() % 50 == 1) {
            if (createKlepto()) {
                getWorld()->playSound(SOUND_ROBOT_BORN);
                return;
            }
        }
    }
    
    
}

//////////////////////////////////////////////
//////////ROBOT MEMBER FUNCTIONS//////////////
//////////////////////////////////////////////
bool Robot:: shoot() {
    bool shot = false;
    if ((getWorld()->isObjectInRowOrColumn(getDirection(), getY(), getX(), "player")) &&
        (getWorld()->isBotFacingPlayer(getDirection(), getX(), getY(), getWorld()->getPlayerX(), getWorld()->getPlayerY())) &&
        !(getWorld()->areObstaclesInBetweenRobotAndPlayer(getDirection(), getX(), getY(), getWorld()->getPlayerX(), getWorld()->getPlayerY())))
    {
        Bullet *b = new Bullet(IID_BULLET, getX(), getY(), this->getDirection(), this->getWorld(), "bullet");
        getWorld()->playSound(SOUND_ENEMY_FIRE);
        getWorld()->addBullet(b);
        shot = true;
    }
    return shot;
}

bool Robot:: isCorrectTick() {
    incrementTicksByOne();
    //rest during ticks
    int ticks = (28 - getWorld()->getLevel()) / 4;
    if (ticks < 3) ticks = 3;
    if (getTicks() % ticks != 0)
        return false;
    return true;
}

bool Robot:: isAttackable() {
    return true;
}

bool Robot:: isBlocked() {
    return true;
}
void Robot:: incrementTicksByOne() {
    m_ticksPassed++;
}

int Robot:: getTicks() {
    return m_ticksPassed;
}

bool Robot:: linearMove() {
    int dx =0; int dy =0;
    switch (getDirection()) {
        case GraphObject::right:
            dx = 1;
            break;
        case GraphObject::left:
            dx = -1;
            break;
        case GraphObject::up:
            dy = 1;
            break;
        case GraphObject::down:
            dy = -1;
            break;
        default:
            break;
    }
    Base* afterPlayer = getWorld()->getObject(getX()+dx, getY()+dy);
    if ((afterPlayer == nullptr) || !afterPlayer->isBlocked()) {
        moveTo(getX()+dx, getY()+dy);
        return true;
    }
   
    return  false;
}

bool Robot:: moveWithSpecifiedDirection(Direction dir) {
    int dx =0; int dy =0;
    switch (dir) {
        case GraphObject::right:
            dx = 1;
            break;
        case GraphObject::left:
            dx = -1;
            break;
        case GraphObject::up:
            dy = 1;
            break;
        case GraphObject::down:
            dy = -1;
            break;
        default:
            break;
    }
    Base* afterPlayer = getWorld()->getObject(getX()+dx, getY()+dy);
    if ((afterPlayer == nullptr) || !afterPlayer->isBlocked()) {
        moveTo(getX()+dx, getY()+dy);
        return true;
    }
    
    return  false;
}

//////////////////////////////////////////////
//////////SNARLBOT MEMBER FUNCTIONS///////////
//////////////////////////////////////////////
void SnarlBot:: damage() {
    changeHealth(-2);
    if (getHealth() <= 0) {
        setAliveorDead(false);
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
    }
    else {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
}

void SnarlBot:: doSomething() {
    if (!isAlive())
        return;
    else if (!isCorrectTick()) return;
    else if (shoot()) return;
    else {
        if (!linearMove()) {
            if (getDirection() == right)  {
                setDirection(left);
                return;
            }
            else if (getDirection() == left) {
                setDirection(right);
                return;
            }
            else if (getDirection() == up) {
                setDirection(down);
                return;
            }
            else if (getDirection() == down){
                setDirection(up);
                return;
            }
        }
    }
}

//////////////////////////////////////////////
//////////KLEPTOBOT MEMBER FUNCTIONS//////////
//////////////////////////////////////////////

void KleptoBot:: setDistanceBeforeTurning(int rand) {
    distanceBeforeTurning = rand;
}
int KleptoBot:: getDistanceBeforeTurning() {
    return distanceBeforeTurning;
}

Actor::Direction KleptoBot:: randomDirectionGenerator() {
    int newDir = rand() % 4;
    if (newDir == 0) return right;
    else if (newDir == 1) return left;
    else if (newDir == 2) return up;
    else if (newDir == 3) return down;
    return none;
}

bool KleptoBot:: pickedUpAGoody() {
    Base* first = getWorld()->getObject(getX(), getY());
      if (rand() % 10 == 1) {
        if ((first->getClass() == "extra_life" || first->getClass() == "restore_health" || first->getClass() == "ammo") && !m_pickedUpGoody) {
           // cout << "hi";
            if (first->getClass() == "extra_life" ) {
                goodyType = "extra_life";
            }
            else if (first->getClass() == "restore_health") {
                goodyType = "restore_health";
            }
            else if (first->getClass() == "ammo") {
                goodyType = "ammo";
            }
            getWorld()->playSound(SOUND_ROBOT_MUNCH);
            m_pickedUpGoody = true;
            first->setAliveorDead(false);
            return true;
        }
    }
    return false;
}

bool KleptoBot:: getHoldingGoody() {
    return m_pickedUpGoody;
}

string KleptoBot:: getGoodyType() {
    return goodyType;
}


bool KleptoBot:: moveWithoutObstacles() {
    bool check = false;
    if (distanceMoved < getDistanceBeforeTurning() && !foundObstacle) {
        if (linearMove()) {
            distanceMoved++;
            check = true;
        }
        else {
            foundObstacle = true;
        }
    }
    return check;
}

bool KleptoBot:: getFoundObstacle() {
    return foundObstacle;
}

bool KleptoBot:: moveWithObstacles() {
    if (distanceMoved >= getDistanceBeforeTurning() || foundObstacle) {
        setDistanceBeforeTurning((rand() % 6) + 1);
        distanceMoved = 0;
        Direction d = randomDirectionGenerator();
        foundObstacle = false;
        consideredDown = false;
        consideredLeft = false;
        consideredRight = false;
        consideredUp = false;
        
        //        do {
        if (d == right && !consideredRight) {
            //if no obstruction move, set direction
            if (moveWithSpecifiedDirection(right)) {
                setDirection(right);
                distanceMoved++;
                consideredRight = true;
                return true;
            }
        }
        else if (d==left && !consideredLeft) {
            if (moveWithSpecifiedDirection(left)) {
                setDirection(left);
                distanceMoved++;
                consideredLeft = true;
                return true;
            }
        }
        else if (d==up && !consideredUp) {
            if (moveWithSpecifiedDirection(up)) {
                setDirection(up);
                distanceMoved++;
                consideredUp = true;
                return true;
            }
        }
        else if (d==down && !consideredDown) {
            if (moveWithSpecifiedDirection(down)) {
                setDirection(down);
                distanceMoved++;
                consideredDown = true;
                return true;
            }
        }
        if (consideredUp && consideredDown && consideredLeft && consideredRight){
            setDirection(d);
            return true;
        }
        else {
            setDirection(d);
            return true;
        }
    }
    return false; //while (!(consideredUp && consideredDown && consideredLeft && consideredRight));
}
//    return false;
//}

//////////////////////////////////////////////
////////REG KLEPTOBOT MEMBER FUNCTIONS////////
//////////////////////////////////////////////

void RegularKleptoBot:: damage() {
    changeHealth(-2);
    if (getHealth() <= 0) {
        setAliveorDead(false);
        if (getHoldingGoody()) {
            getWorld()->createGoody(getX(), getY(), getGoodyType());
        }
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(10);
    }
    else {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
}

void RegularKleptoBot:: doSomething() {
    if (!isAlive())
        return;
    else if (!isCorrectTick()) return;
    else if (pickedUpAGoody()) return;
    else if (moveWithoutObstacles()) return;
    else if (moveWithObstacles()) return;
}


//////////////////////////////////////////////
////////ANG KLEPTOBOT MEMBER FUNCTIONS////////
//////////////////////////////////////////////
void AngryKleptoBot::doSomething() {
    if (!isAlive())
        return;
    else if (!isCorrectTick()) return;
    else if (shoot()) return;
    else if (pickedUpAGoody()) return;
    else if (moveWithoutObstacles()) return;
    else if (moveWithObstacles()) return;
}

void AngryKleptoBot:: damage() {
    changeHealth(-2);
    if (getHealth() <= 0) {
        setAliveorDead(false);
        if (getHoldingGoody()) {
            getWorld()->createGoody(getX(), getY(), getGoodyType());
        }
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(20);
    }
    else {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
}


//////////////////////////////////////////////
//////////BASE MEMBER FUNCTIONS///////////////
//////////////////////////////////////////////
void Base:: setAliveorDead(bool isAlive) {
    m_alive = isAlive;
}

bool Base:: isAlive() {
    return m_alive;
}

int Base::getHealth() {
    return m_health;
}

void Base::setHealth (int hp) {
    m_health = hp;
}

void Base::changeHealth(int howMuch) {
    m_health = m_health + howMuch;
}

void Base::damage() {
    return;
}

StudentWorld* Base:: getWorld() {
   // StudentWorld *sw = new StudentWorld("");
  //  return sw->getStudentWorld();
    return m_world;
}

string Base::getClass() {
    return m_name;
}

bool Base:: isAttackable() {
    return false;
}

bool Base:: isBlocked() {
    return false;
}


//////////////////////////////////////////////
//////////WALL MEMBER FUNCTIONS///////////////
//////////////////////////////////////////////
void Wall:: doSomething() {
    return;
}

bool Wall:: isBlocked() {
    return true;
}

bool Wall:: isAttackable() {
    return true;
}


//////////////////////////////////////////////
//////////BOULDER MEMBER FUNCTIONS////////////
//////////////////////////////////////////////
void Boulder:: doSomething() {
    return;
}

bool Boulder:: isBlocked() {
    return true;
}

void Boulder:: push(int x, int y) {
    moveTo(getX() + x, getY() + y);
}

void Boulder:: damage() {
    changeHealth(-2);
    if (getHealth() <= 0) {
        setAliveorDead(false);
    }
}

bool Boulder:: isAttackable() {
    return true;
}
//////////////////////////////////////////////
//////////ACTOR MEMBER FUNCTIONS//////////////
//////////////////////////////////////////////



//////////////////////////////////////////////
//////////BULLET MEMBER FUNCTIONS/////////////
//////////////////////////////////////////////
bool Bullet:: isBlocked() {
    return true;
}

void Bullet:: move() {
    
    if (getDirection() == right) {
        moveTo(getX()+1, getY());
    }
    else if (getDirection() == left) {
        moveTo(getX()-1, getY());
    }
    else if (getDirection() == up) {
        moveTo(getX(), getY()+1);
    }
    else if (getDirection() == down) {
        moveTo(getX(), getY()-1);
    }

}

void Bullet:: doSomething() {
    if (!isAlive()) return;
    
    Base* b = getWorld()->getObjectNotAt(getX(), getY(), "bullet");
    if (b && b->isAttackable()) {
        b->damage();
        setAliveorDead(false);
        return;
    }
    move();
    Base* b2 = getWorld()->getObjectNotAt(getX(), getY(), "bullet");
    if (b2 && b2->isAttackable()) {
        b2->damage();
        setAliveorDead(false);
        return;
    }

}


//////////////////////////////////////////////
///////////HOLE MEMBER FUNCTIONS//////////////
//////////////////////////////////////////////
bool Hole:: isBlocked() {
    return true;
}

void Hole:: doSomething() {
    if (!isAlive()) return;
    //if boulder on the same x or y
    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "boulder") {
        setAliveorDead(false);
        first->setAliveorDead(false);
    }
}

//////////////////////////////////////////////
///////////JEWEL MEMBER FUNCTIONS/////////////
//////////////////////////////////////////////

void Jewel:: doSomething() {
    if (!isAlive()) return;
    //if boulder on the same x or y
    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "player") {
        getWorld()->increaseScore(50);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        setAliveorDead(false);
    }
}

//////////////////////////////////////////////
//////////GOODY MEMBER FUNCTIONS//////////////
//////////////////////////////////////////////


//////////////////////////////////////////////
///////EXTRA LIFE GOODY MEMBER FUNCTIONS//////
//////////////////////////////////////////////
void ExtraLifeGoody:: doSomething() {
    if (!isAlive()) return;
    //if boulder on the same x or y
    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "player") {
        getWorld()->increaseScore(1000);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incLives();
        setAliveorDead(false);
    }
}


//////////////////////////////////////////////
/////RESTORE HEALTH GOODY MEMBER FUNCTIONS////
//////////////////////////////////////////////
void RestoreHealthGoody:: doSomething() {
    if (!isAlive()) return;
    //if boulder on the same x or y
    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "player") {
        getWorld()->increaseScore(500);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        first->setHealth(20);
        setAliveorDead(false);
    }
}

//////////////////////////////////////////////
/////////AMMO GOODY MEMBER FUNCTIONS//////////
//////////////////////////////////////////////

void AmmoGoody:: doSomething() {
    if (!isAlive()) return;
    //if boulder on the same x or y
    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "player") {
        getWorld()->increaseScore(100);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incAmmo(20);
        setAliveorDead(false);
    }
}


//////////////////////////////////////////////
///////////EXIT  MEMBER FUNCTIONS/////////////
//////////////////////////////////////////////

void Exit:: doSomething() {

    Base* first = getWorld()->getObject(getX(), getY());
    if (first->getClass() == "player" && isVisible()) {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->setCompletedLevel(true);
        getWorld()->increaseScore(2000);
        setVisible(false);
    }
}


//////////////////////////////////////////////
//////////PLAYER MEMBER FUNCTIONS/////////////
//////////////////////////////////////////////
bool Player:: isBlocked() {
    return true;
}

void Player:: damage() {
    changeHealth(-2);
    if (getHealth() <= 0) {
        setAliveorDead(false);
        getWorld()->playSound(SOUND_PLAYER_DIE);
        getWorld()->decLives();
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    }
}

bool Player:: isAttackable() {
    return true;
}

void Player:: keyPressMovement(int x, int y, Direction dir) {
   // if (!(getWorld()->getObject(getX()+x, getY()+y)->isBlocked())) {
    Base* afterPlayer = getWorld()->getObject(getX()+x, getY()+y);
    Base* afterObject = getWorld()->getObject(getX()+x+x, getY()+y+y);
    if ((afterPlayer == nullptr) || !afterPlayer->isBlocked()) {
        moveTo(getX()+x, getY()+y);
        setDirection(dir);
        return;
    }
    if (afterPlayer != nullptr) {
        if (afterPlayer->getClass() == "boulder") {
            Boulder* bp = static_cast<Boulder*>(afterPlayer);
            //make sure the square after isnt blocked (later check to make sure "OR its a hole", "OR its a goody", "OR basically anything that the player can't move through")
            if ((afterObject == nullptr) || !afterObject->isBlocked() || afterObject->getClass() == "hole") {
                if (afterObject && afterObject->getClass() == "exit") return;
                moveTo(getX()+x, getY()+y);
                setDirection(dir);
                bp->push(x, y);
                return;

            }
        }
        setDirection(dir);
    }
}

void Player::doSomething() {
    if (!isAlive()) return;
    int ch;
        if (getWorld()->getKey(ch)) {
            switch (ch) {
                case KEY_PRESS_ESCAPE:
                    break;
                case KEY_PRESS_SPACE: {
                    //create bullet, passing in direction
                    if (getWorld()->getAmmo() > 0) {
                        Bullet *b = new Bullet(IID_BULLET, getX(), getY(), this->getDirection(), this->getWorld(), "bullet");
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        getWorld()->incAmmo(-1);
                        getWorld()->addBullet(b);
                    }
                }
                    break;
                case KEY_PRESS_DOWN:
                    keyPressMovement(0, -1, down);
                    break;
                case KEY_PRESS_UP:
                    keyPressMovement(0, 1, up);
                    break;
                case KEY_PRESS_LEFT:
                    keyPressMovement(-1, 0, left);
                    break;
                case KEY_PRESS_RIGHT:
                    keyPressMovement(1, 0, right);
                    break;
                default:
                    break;
       }
    }
}
