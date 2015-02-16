#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init()
	{
        /*
         A. Initialize the data structures used to keep track of your game’s world.
         B. Load the current maze details from a level data file.
         C. Allocate and insert a valid Player object into the game world.
         D. Allocate and insert any SnarlBots objects, Wall objects, Boulder objects, Factory
         objects, Jewel objects, Goodie objects, or Exit objects into the game world, as required by the specification in the current level’s data file.
         */
        
        
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{
	}

private:
};

#endif // STUDENTWORLD_H_
