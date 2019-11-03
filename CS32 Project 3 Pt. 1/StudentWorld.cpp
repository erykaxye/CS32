#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <list>
#include <cstdlib>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{

}

StudentWorld::~StudentWorld()
{
	cleanUp(); 
}

int StudentWorld::init()
{
	double amt; 
	ostringstream oss; 
	oss << setw(10) << "Lives: " << START_PLAYER_LIVES;
	oss << "  Health: 100%  Score: 0  Level: 1  Cabbages: 100%  Torpedoes: 4";
	string s = oss.str(); 
	for (int i = 0; i < 30; i++) //create the stars
	{
		//choose randomly the size and y value 
		m_actors.push_back(new Star(randInt(0, VIEW_WIDTH - 1), randInt(0, VIEW_HEIGHT - 1), this));
	}
	player = new NachenBlaster(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
	player->doSomething(); 
	list<Actor*>::iterator it; 
	for (it = m_actors.begin(); it != m_actors.end();) //makes each actor doSomething
	{
		(*it)->doSomething();
		if (!((*it)->isAlive())) //checks if its still alive 
		{
			delete (*it); //delete out of the list 
			it = m_actors.erase(it);
		}
		else
			it++;
	}
	if (randInt(1, 15) == 1) //choose randomly 1/15 chance to create new star 
	{
		m_actors.push_back(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this)); //choose randomly y value 
	}
	//return GWSTATUS_PLAYER_DIED;
	return GWSTATUS_CONTINUE_GAME; 

}

void StudentWorld::cleanUp()
{
	delete player; 
	player = nullptr; 
	list<Actor*>::iterator it;
	for (it = m_actors.begin(); it != m_actors.end();)
	{
		delete *it;
		it = m_actors.erase(it);
	}
}

void StudentWorld::deleteActor(list<Actor*>::iterator &it)
{

}