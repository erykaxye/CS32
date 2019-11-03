#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <list>
#include <cstdlib>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{}

StudentWorld::~StudentWorld()
{
	cleanUp(); 
}

int StudentWorld::init()
{
	m_nAlienShipsDestroyed = 0;
	m_AliensOnScreen = 0;
	for (int i = 0; i < 30; i++) //create the stars
	{
		m_actors.push_back(new Star(randInt(0, VIEW_WIDTH - 1), this));
	}
	player = new NachenBlaster(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{ 
	ostringstream lives;
	lives << getLives();
	ostringstream hp;
	hp << player->getHitPointsPCT();
	ostringstream score;
	score << getScore();
	ostringstream level;
	level << getLevel();
	ostringstream cabbages;
	cabbages << player->getCabbagePCT();
	ostringstream torpedoes;
	torpedoes << player->getFlatTor();
	ostringstream oss;
	oss << "Lives: " << getLives() << "  Health: " << player->getHitPointsPCT()
		<< "%  Score: " << getScore() << "  Level: " << getLevel() << "  Cabbages: "
		<< player->getCabbagePCT() << "%  Torpedoes: " << player->getFlatTor();
	string statusline = oss.str();
	setGameStatText(statusline);

	list<Actor*>::iterator it; 
	for (it = m_actors.begin(); it != m_actors.end(); it++) 
	{
		(*it)->doSomething();
	}	

	player->doSomething();

	for (it = m_actors.begin(); it != m_actors.end();)
	{
		if (!((*it)->isAlive())) //checks if its still alive 
		{
			if ((*it)->isAlien())
				m_AliensOnScreen--;
			delete (*it);
			it = m_actors.erase(it);
		}
		else
			it++;
	}

	//sees if new aliens should be created and creates them 
	newAliens();
	//choose randomly 1/15 chance to create new star
	newStars();

	if (m_nAlienShipsDestroyed == 6 + (4 * getLevel()))
	{
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}

	if (!player->isAlive())
	{
		decLives();
		m_nAlienShipsDestroyed = 0;
		m_AliensOnScreen = 0;
		return GWSTATUS_PLAYER_DIED;
	}

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

Actor* StudentWorld::collision(Actor* a, Actor* b)
{
	if (euclidian_dist(a->getX(), a->getY(), b->getX(), b->getY()) < .75 * (a->getRadius() + b->getRadius()))
		return b;
	return nullptr;
}

Actor* StudentWorld::circleThruActors(Actor *a) //if its looking at itself?  
{
	list<Actor*>::iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++)
	{
		if (a != *it && (*it)->firedByPlayer())
			if (collision(a, *it) != nullptr)
				return *it; //returns first thing it runs into?? 
	}
	return nullptr;
}

double StudentWorld::euclidian_dist(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; 
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}

void StudentWorld::newStars()
{
	if (randInt(1, 15) == 1)
		m_actors.push_back(new Star(VIEW_WIDTH - 1, this));
}

void StudentWorld::newAliens()
{
	double r = 6 + (4 * getLevel()) - m_nAlienShipsDestroyed;
	double m = 4 + (.5 * getLevel());
	if (m_AliensOnScreen < min(m, r))
	{
		double s1 = 60;
		double s2 = 20 + getLevel() * 5;
		double s3 = 5 + getLevel() * 10;
		double s = s1 + s2 + s3;
		int rand = randInt(1, s);
		if (rand <= s1)
			m_actors.push_back(new Smallgon(5 * (1 + (getLevel() - 1) * 0.1), this));
		else if (rand <= s1 + s2)
			m_actors.push_back(new Smoregon(5 * (1 + (getLevel() - 1) * 0.1), this));
		else if (rand <= s1 + s2 + s3)
			m_actors.push_back(new Snagglegon(10 * (1 + (getLevel() - 1)*.1), this));
		m_AliensOnScreen++;
	}
}

void StudentWorld::fireCabbage()
{ 
	m_actors.push_back(new Cabbage(player->getX() + 12, player->getY(), this)); 
	playSound(SOUND_PLAYER_SHOOT);
}

void StudentWorld::fireTurnip(Actor* a)
{
	m_actors.push_back(new Turnip(a->getX() - 14, a->getY(), this)); //make sure it appearscertain distance way
	playSound(SOUND_ALIEN_SHOOT);
}

void StudentWorld::fireTorpedo(Actor* a)
{
	if (a->isAlien())
		m_actors.push_back(new FlatulenceTorpedo(a->getX() - 14, a->getY(), 180, this));
	else
		m_actors.push_back(new FlatulenceTorpedo(a->getX() + 12, a->getY(), 0, this));
	playSound(SOUND_TORPEDO);
}

void StudentWorld::dropExtraLife(Actor* a)
{
	m_actors.push_back(new ExtraLifeGoodie(a->getX(), a->getY(), this));
}

void StudentWorld::dropRepair(Actor* a)
{
	m_actors.push_back(new RepairGoodie(a->getX(), a->getY(), this));
}

void StudentWorld::dropTorpedo(Actor* a)
{
	m_actors.push_back(new TorpedoGoodie(a->getX(), a->getY(), this));
}

void StudentWorld::explosion(Actor *a)
{
	m_actors.push_back(new Explosion(a->getX(), a->getY(), this));
}