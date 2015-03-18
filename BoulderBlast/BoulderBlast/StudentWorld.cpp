
#include "StudentWorld.h" 
#include "Actor.h"
#include <sstream>
#include <iomanip>
StudentWorld:: StudentWorld (std::string assetDir) : GameWorld(assetDir) {
    
}

StudentWorld* StudentWorld:: getStudentWorld() {
    return this;
}

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

bool StudentWorld:: isObjectInRowOrColumn(GraphObject::Direction dir, int x, int y, string ID) {
    bool objectInRowOrColumn = false;
    
    if (dir == GraphObject::right || dir == GraphObject::left) {
        list<Base*>::iterator it = AssetList.begin();
        while (it != AssetList.end()) {
            Base *b = *it;
            if (b->getY() == x && b->getClass() == ID)
                objectInRowOrColumn = true;
            it++;
        }
    }
    else if (dir == GraphObject::up || dir == GraphObject::down) {
        list<Base*>::iterator it = AssetList.begin();
        while (it != AssetList.end()) {
            Base *b = *it;
            if (b->getX() == y && b->getClass() == ID)
                objectInRowOrColumn = true;
            it++;
        }
    }
    
    return objectInRowOrColumn;
}

bool StudentWorld:: areObstaclesInBetweenRobotAndPlayer(GraphObject::Direction dir, int x, int y, int px, int py) {
    bool obstacles = false;
    if (dir == GraphObject::right) {
        for (int i = x+1; i < px; i++) {
            Base *b = getObject(i, y);
            if (b && b->isAttackable()) {
                obstacles = true;
                break;
            }
        }
    }
    else if (dir == GraphObject::left) {
        for (int i = x-1; i > px; i--) {
            Base *b = getObject(i, y);
            if (b && b->isAttackable()) {
                obstacles = true;
                break;
            }
        }
    }
    else if (dir == GraphObject::up) {
        for (int i = y+1; i < py; i++) {
            Base *b = getObject(x, i);
            if (b && b->isAttackable()) {
                obstacles = true;
                break;
            }
        }
    }
    else if (dir == GraphObject::down) {
        for (int i = y-1; i > py; i--) {
            Base *b = getObject(x, i);
            if (b && b->isAttackable()) {
                obstacles = true;
                break;
            }
        }
    }
    
    return obstacles;

}


int StudentWorld:: getPlayerX() {
    return m_player->getX();
}

int StudentWorld:: getPlayerY() {
    return m_player->getY();
}


bool StudentWorld:: isBotFacingPlayer(GraphObject::Direction dir, int x, int y, int px, int py) {
  
    switch (dir) {
        case GraphObject::right: {
                for (int i = x; i < VIEW_WIDTH; i++) {
                    if (i == px)
                        return true;
                }
            }
            break;
        case GraphObject::left: {
                for (int i = 0; i < x; i++) {
                    if (i == px)
                        return true;
                }
            }
            break;
        case GraphObject::up: {
                for (int i = y; i < VIEW_WIDTH; i++) {
                    if (i == py)
                        return true;
                }
            }
            break;
        case GraphObject::down: {
                for (int i = 0; i < y; i++) {
                    if (i == py)
                        return true;
                }
            }
            break;
        default:
            break;
    }
    
    return false;
    
}


bool StudentWorld:: getPlayerDead() {
    return !(m_player->isAlive());
}
void StudentWorld::  setCompletedLevel(bool isHeDone) {
    m_playerCompletedLevel = isHeDone;
}
bool StudentWorld:: getCompletedLevel() {
    return m_playerCompletedLevel;
}

StudentWorld::~StudentWorld(){
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base* b = *it;
        delete b;
        AssetList.erase(it);
        it++;
    }
}
int StudentWorld:: getAmmo() {
    return m_ammo;
}

void StudentWorld:: incAmmo(int howMuch) {
    m_ammo += howMuch;
}

void StudentWorld:: addBullet (Bullet* bullet) {
    AssetList.push_front(bullet);
}

void StudentWorld:: addKlepto(KleptoBot *k) {
    AssetList.push_front(k);
}

bool StudentWorld:: areThereJewelsLeft() {
    bool areThereJewels = false;
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base *b = *it;
        if (b->getClass() == "jewel")
            areThereJewels = true;
        it++;
    }
    return areThereJewels;
}

void StudentWorld:: setExitVisible(Exit* e, bool yesOrNo) {
        e->setVisible(yesOrNo);
}

void StudentWorld:: createGoody(int x, int y, string type ) {
    
    if (type == "ammo") {
        AmmoGoody *a = new AmmoGoody(IID_AMMO, x , y, Base::none, this, type);
        AssetList.push_back(a);
    }
    else if (type == "extra_life") {
        ExtraLifeGoody *l = new ExtraLifeGoody(IID_EXTRA_LIFE, x, y, Base::none, this, type);
        AssetList.push_back(l);
    }
    else if (type == "restore_health") {
        RestoreHealthGoody *r = new RestoreHealthGoody(IID_RESTORE_HEALTH, x, y, Base::none, this, type);
        AssetList.push_back(r);
    }
    
}

string StudentWorld:: levelLoader() {
    stringstream oss;
    oss << "level" << setw(2);
    oss.fill('0');
    oss << getLevel() << ".dat";
    return oss.str();
}

int StudentWorld:: init () {

    string curLevel = levelLoader();
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (getLevel() > 99) return GWSTATUS_PLAYER_WON;
    if (result == Level::load_fail_file_not_found) {
        cerr << curLevel << "not found!";
        return GWSTATUS_PLAYER_WON;
    }
    else if (result == Level:: load_fail_bad_format) {
        cerr << curLevel << " bad format!";
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level:: load_success) {
        cerr << curLevel << " loaded successfully.";
        for (int i = 0; i < VIEW_WIDTH; i++) {
            for (int j = 0; j < VIEW_HEIGHT; j++) {
                Level::MazeEntry item = lev.getContentsOf(i, j);
                switch (item) {
                    case Level::player: {
                        Player *p = new Player (IID_PLAYER, i, j, Base::right, this, "player");
                        m_player = p;
                        AssetList.push_front(p);
                        break;
                    }
                    case Level::wall: {
                        Wall *w = new Wall (IID_WALL, i ,j, Base::none, this, "wall");
                        AssetList.push_back(w);
                        break;
                    }
                    case Level::boulder: {
                        Boulder *b = new Boulder (IID_BOULDER, i , j, Base::none, this, "boulder");
                        AssetList.push_front(b);
                        break;
                    }
                    case Level::hole: {
                        Hole *x = new Hole (IID_HOLE, i ,j, Base::none, this, "hole");
                        AssetList.push_back(x);
                        break;
                    }
                    case Level::jewel: {
                        Jewel *a = new Jewel(IID_JEWEL, i, j, Base::none, this, "jewel");
                        m_numJewels++;
                        AssetList.push_back(a);
                        break;
                    }
                    case Level::extra_life: {
                        ExtraLifeGoody *l = new ExtraLifeGoody(IID_EXTRA_LIFE, i, j, Base::none, this, "extra_life");
                        AssetList.push_back(l);
                        break;
                    }
                    case Level::restore_health: {
                        RestoreHealthGoody *r = new RestoreHealthGoody(IID_RESTORE_HEALTH, i, j, Base::none, this, "restore_health");
                        AssetList.push_back(r);
                        break;
                    }
                    case Level::ammo: {
                        AmmoGoody *a = new AmmoGoody(IID_AMMO, i , j, Base::none, this, "ammo");
                        AssetList.push_back(a);
                        break;
                    }
                    case Level::exit: {
                        Exit *e = new Exit (IID_EXIT, i, j, Base::none, this, "exit");
                        AssetList.push_back(e);
                        m_exit = e;
                        break;
                    }
                    case Level::horiz_snarlbot: {
                        SnarlBot *hs = new SnarlBot (IID_SNARLBOT, i, j, Base::right, this, "horiz_snarlbot");
                        AssetList.push_back(hs);
                        break;
                    }
                    case Level::vert_snarlbot: {
                        SnarlBot *vs = new SnarlBot (IID_SNARLBOT, i, j, Base::down, this, "vert_snarlbot");
                        AssetList.push_back(vs);
                        break;
                    }
                    case Level::kleptobot_factory: {
                        Factory *f = new Factory (IID_ROBOT_FACTORY, i, j, Base::none, this, "kleptobot_factory", "regular");
                        AssetList.push_back(f);
                        break;
                    }
                    case Level::angry_kleptobot_factory: {
                        Factory *a = new Factory (IID_ROBOT_FACTORY, i, j, Base::none, this, "angry_kleptobot_factory", "angry");
                        AssetList.push_back(a);
                        break;
                    }
                    case Level::empty:
                    default:
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld:: move() {
    
    //update the game status line
    updateDisplayText();

    //asks all active actors to do something
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base *b = *it;
        if (b->isAlive()) {
            //ask each thing to do something
           // cout << b->getClass() << endl;
            b->doSomething();
            //if the player died return
            if(getPlayerDead()) return GWSTATUS_PLAYER_DIED;
            if (getCompletedLevel()) {
                increaseScore(getBonus());
                setBonus(1000);
                setCompletedLevel(false);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
        it++;
//        if (!b->isAlive()) {
//            delete *it;
//            it = AssetList.erase(it);
//        }
//        it++;
        
        /*else {
            delete *it;
            it = AssetList.erase(it);
        }*/
    }
    
    list<Base*>::iterator itr = AssetList.begin();
    while (itr != AssetList.end()) {
        Base *b = *itr;
        if (!b->isAlive()) {
           // cout << b->getClass();
            delete *itr;
            itr = AssetList.erase(itr);
        }
        itr++;
        
    }
    
    decBonus();
    
    if (!areThereJewelsLeft() && !m_exit->isVisible()) {
      //  setExitVisible(m_exit, true);
        m_exit->setVisible(true);
        playSound(SOUND_REVEAL_EXIT);
    }
    
    if (getPlayerDead()) return GWSTATUS_PLAYER_DIED;
    
    if (getCompletedLevel()) {
        increaseScore(getBonus());
        setBonus(1000);
        setCompletedLevel(false);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld:: cleanUp() {
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base* b = *it;
        delete b;
        AssetList.erase(it);
        it++;
    }
}

unsigned int StudentWorld:: getBonus() {
    return m_bonus;
}

void StudentWorld:: decBonus() {
    if (m_bonus > 0) m_bonus--;
}

void StudentWorld:: setBonus(int number) {
    m_bonus = number;
}


void StudentWorld:: updateDisplayText () {
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int ammo = getAmmo();
    unsigned int bonus = getBonus();
    int health = m_player->getHealth() * 100/20;
    
    ostringstream scoreStream;
    scoreStream << "Score: " << setw(7);
    scoreStream.fill('0');
    scoreStream << score;
    
    ostringstream levelStream;
    levelStream << "Level: " << setw(2);
    levelStream.fill('0');
    levelStream << level;
    
    ostringstream livesStream;
    livesStream << "Lives: " << setw(2);
    livesStream.fill(' ');
    livesStream << lives;
    
    ostringstream healthStream;
    healthStream << "Health: " << setw(3);
    healthStream.fill(' ');
    healthStream << health;
    healthStream << "%";
    
    ostringstream ammoStream;
    ammoStream << "Ammo: " << setw(3);
    ammoStream.fill(' ');
    ammoStream << ammo;
    
    ostringstream bonusStream;
    bonusStream << "Bonus: " << setw(4);
    bonusStream.fill(' ');
    bonusStream << bonus;
    
    string s = scoreStream.str() + "  " + levelStream.str() + "  " + livesStream.str() + "  " + healthStream.str() + "  " + ammoStream.str() + "  " + bonusStream.str();
    setGameStatText(s);
    
}

Base* StudentWorld:: getObject(int x, int y) {
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base *b = *it;
        if (b->getX() == x && b->getY() == y) {
            return *it;
        }
        it++;
    }
    return nullptr;
}


Base* StudentWorld:: getObjectNotAt(int x, int y, string ID) {
    list<Base*>::iterator it = AssetList.begin();
    while (it != AssetList.end()) {
        Base *b = *it;
        if (b->getX() == x && b->getY() == y && b->getClass() != ID) {
            return *it;
        }
        it++;
    }
    return nullptr;
}
