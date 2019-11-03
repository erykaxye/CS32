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
	NachenBlaster* getPlayer() { return player; }
	void newStars();
	void newAliens(); 
	void incAlienShipsDestroyed() { m_nAlienShipsDestroyed++; }
	Actor* collision(Actor* a, Actor* b); //idk
	double euclidian_dist(double x1, double y1, double x2, double y2);
	void fireCabbage(); 
	void fireTurnip(Actor *a); //do i need a pointer??? to tell if its alien or not?? 
	void fireTorpedo(Actor *a); 
	void dropExtraLife(Actor *a);
	void dropRepair(Actor *a);
	void dropTorpedo(Actor *a);
	void explosion(Actor *a); 
	Actor* circleThruActors(Actor *a); 

private:
	list<Actor*> m_actors; 
	NachenBlaster* player; 
	int m_nAlienShipsDestroyed; 
	int m_AliensOnScreen; 
};

#endif // STUDENTWORLD_H_
