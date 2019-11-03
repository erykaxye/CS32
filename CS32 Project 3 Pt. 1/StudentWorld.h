#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h" //is this ok?
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	~StudentWorld(); 
    virtual int init();
    virtual int move();
    virtual void cleanUp(); 
	void deleteActor(list<Actor*>::iterator &it); 

private:
	list<Actor*> m_actors; 
	NachenBlaster* player; 
	int m_level;
	int m_nAlienShipsDestroyed; 
};

#endif // STUDENTWORLD_H_
