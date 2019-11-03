/*
implement each class first, like make them appear when neccessary
then work on collisons (aka explosions and hit points and goodies? and points) and sounds 
work on smoregon, snaggle, 
check if sounds ok, and appearing in correct places
the text at the top?
*/

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"  
#include <iostream>
#include <list>
using namespace std;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

//Constants
const int DOWN_LEFT = 2001;
const int UP_LEFT = 2002; 
const int DUE_LEFT = 2003;

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, StudentWorld* world, int dmg = 0, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
		: GraphObject(imageID, startX, startY, dir, size, depth)
	{
		m_world = world;
		m_state = true;
		alien = false; 
		m_dmg = dmg; 
		whoFired = false;
	}
	virtual ~Actor() {}
	virtual void doSomething() = 0;
	virtual bool isAlive() const; 
	virtual void setState(bool state);
	virtual bool firedByPlayer() { return whoFired; }  //returns true if fired by nachenblaster, false for every other actor const
	virtual bool collision() { return false; } 
	bool getState() const { return m_state; } 
	void setWhoFired(bool who);
	StudentWorld* getWorld() const { return m_world; }
	bool isAlien() { return alien; } //const
	void setAlien();
	int getDmg() { return m_dmg; } //const
	void setDmg(int dmg); 
private:
	StudentWorld* m_world;
	bool m_state; 
	bool alien; 
	int m_dmg; 
	bool whoFired; 
};

class DamageableObject : public Actor
{
public:
	DamageableObject(int imageID, double startX, double startY, StudentWorld* world, double hitPoints, int dmg = 0, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
		: Actor (imageID, startX, startY, world, dmg, dir, size, depth)
	{
		m_hitPoints = hitPoints;
	}
	virtual ~DamageableObject() {} //
	double hitPoints() const { return m_hitPoints; }
	void increaseHitPoints(double amt);
	void sufferDamage(double amt);
private:
	double m_hitPoints; 
};

class NachenBlaster : public DamageableObject
{
public:
	NachenBlaster(StudentWorld* world, double hitPoints = 50.0, int cabbageEP = 30)
		: DamageableObject(IID_NACHENBLASTER, 0, 128, world, hitPoints, 0, 1.0, 0)
	{
		m_cabbageEP = cabbageEP;
		m_nFlatTor = 0; 
	}
	virtual void doSomething();
	virtual bool isAlive() const;
	int getHitPointsPCT() const;
	int getCabbagePCT() const;
	int getFlatTor() const { return m_nFlatTor; }
	void incFlatTor();
private: 
	int m_cabbageEP; 
	int m_nFlatTor;
};

class Alien : public DamageableObject
{
public:
	Alien(int imageID, StudentWorld* world, double hitPoints, int dmg = 0, int score = 250, double travelSpeed = 2.0, int flightPlanLength = 0, int travelDir = DOWN_LEFT)
		: DamageableObject(imageID, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), world, hitPoints, dmg, 0, 1.5, 1)
	{
		setAlien();
		m_flightPlan = flightPlanLength; 
		m_travelSpeed = travelSpeed;
		m_travelDir = travelDir; 
		m_score = score;
	}
	virtual ~Alien() {}
	virtual void doSomething() = 0; 
	virtual void dropGoodie() { return; }
	virtual bool isAlive() const;
	void setFlightPlan(); 
	int getFlightPlan() const { return m_flightPlan; }
	int getTravelDir() const { return m_travelDir; }
	double getTravelSpeed() const { return m_travelSpeed; }
	void changeFlightPlan(int n);
	void changeTravelDir(int dir);
	void setTravelSpeed(double speed); 
	void move(); 
	bool inLineOfFire();
	virtual bool collision();
	int getScorePoints() { return m_score; } //const
private:
	int m_damageAmt;
	int m_flightPlan; 
	int m_travelDir; 
	double m_travelSpeed;
	int m_score; 
};

class Smallgon : public Alien
{
public:
	Smallgon(double hitPoints, StudentWorld* world)
		: Alien(IID_SMALLGON, world, hitPoints, 5) 
	{}
	virtual void doSomething(); 
};

class Smoregon : public Alien
{
public:
	Smoregon(double hitPoints, StudentWorld* world)
		: Alien(IID_SMOREGON, world, hitPoints, 5)  
	{}
	virtual ~Smoregon() { dropGoodie(); }
	virtual void doSomething();
	virtual void dropGoodie(); 
};

class Snagglegon : public Alien
{
public: 
	Snagglegon(double hitPoints, StudentWorld* world)
		: Alien(IID_SNAGGLEGON, world, hitPoints, 15, 1000, 1.75)
	{}
	virtual ~Snagglegon() { dropGoodie(); }
	virtual void doSomething();
	virtual void dropGoodie(); 
};

class Projectile : public Actor
{
public:
	Projectile(int imageID, double startX, double startY, StudentWorld* world, int dmg = 0,  Direction dir = 0, double size = 1.0, unsigned int depth = 0)
		: Actor(imageID, startX, startY, world, dmg, dir, size, depth)
	{}
	virtual void doSomething() = 0;
	virtual bool collision();
};

class Cabbage : public Projectile
{
public:
	Cabbage(double startX, double startY, StudentWorld* world)
		:Projectile(IID_CABBAGE, startX, startY, world, 2, 0, .5, 1)
	{} 
	virtual void doSomething();  
	virtual bool firedByPlayer() { return true; }
};

class Turnip : public Projectile
{
public:
	Turnip(double startX, double startY, StudentWorld* world)
		:Projectile(IID_TURNIP, startX, startY, world, 2, 0, .5, 1)
	{}
	virtual void doSomething();
};

class FlatulenceTorpedo : public Projectile
{
public:
	FlatulenceTorpedo(double startX, double startY, Direction dir, StudentWorld* world)
		:Projectile(IID_TORPEDO, startX, startY, world, 8, dir, .5, 1)
	{
		if (dir == 0)
			setWhoFired(true); //Nachenblaster
		else
			setWhoFired(false); //alien shouldnt b anything else but just incase? 
	}
	virtual void doSomething();
};

class Star : public Actor
{
public:
	Star(double startX, StudentWorld* world)
		: Actor(IID_STAR, startX, randInt(0, VIEW_HEIGHT - 1), world, 0, 0, randInt(5, 50)/100.0, 3)
	{}
	virtual void doSomething();
};

class Explosion : public Actor
{
public:
	Explosion(double startX, double startY, StudentWorld* world)
		: Actor(IID_EXPLOSION, startX, startY, world, 0, 0, 1, 0)
	{
		nTicks = 0;
	}
	virtual void doSomething(); 
private:
	int nTicks;
};

class Goodie : public Actor
{
public:
	Goodie(int imageID, double startX, double startY, StudentWorld *world, int score = 100, int dmg = 0)
		: Actor(imageID, startX, startY, world, dmg, 0, 0.5, 1)
	{
		m_score = score;
	}
	virtual void doSomething();
	virtual void value() = 0;
	void moveOffScreen();
	virtual bool collision();
	int getScorePoints() { return m_score; } //const
private:
	int m_score; 
}; 

class RepairGoodie : public Goodie
{
public:
	RepairGoodie(double startX, double startY, StudentWorld *world)
		: Goodie(IID_REPAIR_GOODIE, startX, startY, world)
	{}
	virtual void value();
};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(double startX, double startY, StudentWorld *world)
		: Goodie(IID_LIFE_GOODIE, startX, startY, world) 
	{}
	virtual void value();
};

class TorpedoGoodie : public Goodie
{
public:
	TorpedoGoodie(double startX, double startY, StudentWorld *world)
		: Goodie(IID_TORPEDO_GOODIE, startX, startY, world)
	{}
	virtual void value();
};


#endif // ACTOR_H_
