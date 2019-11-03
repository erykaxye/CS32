#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"  
#include <iostream>
#include <list>
using namespace std; 

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

/****************************************************************
* Actor															*
/***************************************************************/

class StudentWorld;

class Actor: public GraphObject
{
public: 
	Actor(int imageID, double startX, double startY, StudentWorld* world, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
		: GraphObject(imageID, startX, startY, dir, size, depth) 
	{
		m_world = world; 
	}
	virtual ~Actor() {}
	virtual void doSomething() = 0; 
	virtual bool isAlive() const;
	StudentWorld* getWorld() { return m_world; }
private: 
	StudentWorld* m_world; 
};

class NachenBlaster : public Actor
{
public:
	NachenBlaster(StudentWorld* world)
		: Actor (IID_NACHENBLASTER, 0, 128, world, 0, 1.0, 0)
	{}
	virtual void doSomething();
	virtual bool isAlive() const;
	int getHealth() { return m_health; }
	void setHealth(int n);
	int getCabbageEP() { return m_cabbageEP; }
	void setCabbageEP(int n); 
private: 
	int m_health; //50 
	int m_cabbageEP; //30? 
};

class Alien : public Actor
{
public: 
	int getHealth(); 
	void setHealth(int n);
private:
	int health; 
};

class Smallgons : public Alien
{

};

class Smoregons : public Alien
{

};

class Snagglegons : public Alien
{

};

class Projectile : public Actor
{

};

class Cabbage : public Projectile
{

};

class Turnip : public Projectile
{

};

class FlatulenceTorpedo : public Projectile
{

};

class Star : public Actor
{
public:
	Star(double startX, double startY, StudentWorld* world)
		: Actor(IID_STAR, startX, startY, world, 0, randInt(5, 50)/100.0, 3)
	{}
	virtual ~Star() {}
	virtual void doSomething();
};

class Explosion : public Actor
{

};

class Goodie : public Actor
{

}; 

class RepairGoodie : public Goodie
{

};

class ExtraLifeGoodie : public Goodie
{

};

class FlatulenceTorpedoGoodie : public Goodie
{

};


#endif // ACTOR_H_
