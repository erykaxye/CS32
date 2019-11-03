#include "Actor.h"
#include "StudentWorld.h"

//DONT FROGET TO RESET TOREPDOS 
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/********************************************
*				Actor						*
********************************************/

bool Actor::isAlive() const
{
	//if off screen or state is false return false else return true 
	if (getX() < 0 || getX() > VIEW_WIDTH - 1)
		return false;
	else if (getY() < 0 || getY() > VIEW_HEIGHT - 1)
		return false;
	else if (m_state == false)
		return false;
	return true;
}

void Actor::setState(bool state)
{
	m_state = state;
}

void Actor::setWhoFired(bool who) 
{ 
	whoFired = who; 
}

void Actor::setAlien() 
{ 
	alien = true; 
}

void Actor::setDmg(int dmg)
{
	m_dmg = dmg; 
}

/********************************************
*			Damageable Object				*
********************************************/

void DamageableObject::increaseHitPoints(double amt)
{
	m_hitPoints += amt; 
	if (m_hitPoints > 50)
		m_hitPoints = 50;
}

// This actor suffers an amount of damage caused by being hit by either
// a ship or a projectile 
void DamageableObject::sufferDamage(double amt)
{
	m_hitPoints -= amt; 
	if (m_hitPoints <= 0)
		setState(false); 
}

/********************************************
*			NachenBlaster					*
********************************************/

void NachenBlaster::doSomething()
{
	if (!isAlive())
		return;
	int n;
	if (getWorld()->getKey(n))
	{
		switch (n)
		{
		case KEY_PRESS_LEFT:
			if (getX() - 6 > 0)
				moveTo(getX() - 6, getY());
			break;
		case KEY_PRESS_RIGHT:
			if (getX() + 6 <= VIEW_WIDTH)
				moveTo(getX() + 6, getY());
			break;
		case KEY_PRESS_UP:
			if (getY() + 6 <= VIEW_HEIGHT)
				moveTo(getX(), getY() + 6);
			break;
		case KEY_PRESS_DOWN:
			if (getY() - 6 > 0)
				moveTo(getX(), getY() - 6);
			break; 
		case KEY_PRESS_SPACE:
			if (m_cabbageEP >= 5)
			{
				getWorld()->fireCabbage(); //creates new cabbage and decrements cabbage energy points
				m_cabbageEP -= 5;
			}
			break;
		case KEY_PRESS_TAB:
			if (m_nFlatTor > 0)
			{
				getWorld()->fireTorpedo(this);
				m_nFlatTor--;
			}
			break; 
		}
	}
	if(m_cabbageEP < 30)
		m_cabbageEP++; 
}

bool NachenBlaster::isAlive() const
{
	if (hitPoints() <= 0)
		return false;
	return true;
}

void NachenBlaster::incFlatTor()
{
	m_nFlatTor += 5;
}

int NachenBlaster::getHitPointsPCT() const 
{ 
	return hitPoints() / 50.0 * 100; //gets percentage of hit points left
}

int NachenBlaster::getCabbagePCT() const 
{ 
	return m_cabbageEP / 30.0 * 100; 
}

/********************************************
*				Alien						*
********************************************/

void Alien::move()
{
	if (getTravelDir() == DOWN_LEFT)
		moveTo(getX() - getTravelSpeed(), getY() - getTravelSpeed());
	else if (getTravelDir() == UP_LEFT)
		moveTo(getX() - getTravelSpeed(), getY() + getTravelSpeed());
	else if (getTravelDir() == DUE_LEFT)
		moveTo(getX() - getTravelSpeed(), getY());
}

void Alien::setFlightPlan()
{
	if (getFlightPlan() == 0 || getY() >= VIEW_HEIGHT - 1 || getY() <= 0)
	{
		if (getY() >= VIEW_HEIGHT - 1)
			m_travelDir = DOWN_LEFT;
		else if (getY() <= 0)
			m_travelDir = UP_LEFT;
		else if (getFlightPlan() == 0)
			m_travelDir = randInt(2001, 2003);
		m_flightPlan = randInt(1, 32);
	}
	else
		m_flightPlan--;
}

bool Alien::isAlive() const
{
	if (hitPoints() <= 0 || getX() < 0 || getState() == false)
		return false;
	return true;
}

bool Alien::inLineOfFire()
{
	if (getX() > getWorld()->getPlayer()->getX()
		&& getY() <= getWorld()->getPlayer()->getY() + 4
		&& getY() >= getWorld()->getPlayer()->getY() - 4)
		return true;
	return false;
}

bool Alien::collision()
{
	if(!isAlive())
		return false;

	if (getWorld()->collision(this, getWorld()->getPlayer()) != nullptr) 
	{
		getWorld()->getPlayer()->sufferDamage(getDmg());
		getWorld()->increaseScore(getScorePoints());
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->incAlienShipsDestroyed();
		getWorld()->explosion(this); 
		setState(false);
		
		return true;
	}

	Actor *p = getWorld()->circleThruActors(this);
	if (p != nullptr && p->isAlien() != true && p->firedByPlayer() == true)
	{
		sufferDamage(p->getDmg());
		p->setState(false); //check if projectile wroks?
		if (!isAlive())
		{
			getWorld()->increaseScore(getScorePoints());
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->explosion(this);
			getWorld()->incAlienShipsDestroyed();
			setState(false);
		}
		else
			getWorld()->playSound(SOUND_BLAST);
		return true; 
	}
	return false;
}

void Alien::changeFlightPlan(int n) 
{
	m_flightPlan = n; 
}

void Alien::changeTravelDir(int dir) 
{ 
	m_travelDir = dir; 
}

void Alien::setTravelSpeed(double speed) 
{
	m_travelSpeed = speed; 
}

/********************************************
*				Smallgon					*
********************************************/

void Smallgon::doSomething()
{
	if (!isAlive())
		return;

	if (collision())
		return;

	if (isAlive())
	{
		setFlightPlan();

		if (inLineOfFire())
			if (randInt(1, (20 / getWorld()->getLevel()) + 5) == 1)
				getWorld()->fireTurnip(this);

		if (getFlightPlan() > 0)
			move();
	}

	if (collision())
		return; 
}

/********************************************
*				Smoregon					*
********************************************/

void Smoregon::doSomething()
{
	if (!isAlive())
		return;
	
	if (collision())
		return;

	setFlightPlan();

	if (inLineOfFire())
	{
		int rand = randInt(1, (20 / getWorld()->getLevel()) + 5);
		if (rand == 1)
			getWorld()->fireTurnip(this);
		else if (rand == 2)
		{
			changeTravelDir(DUE_LEFT);
			changeFlightPlan(VIEW_WIDTH);
			setTravelSpeed(5.0);
		}
	}

	if (getFlightPlan() > 0)
		move();

	if (collision())
		return;
}

void Smoregon::dropGoodie()
{
	if (randInt(1, 3) == 1) //drops goodie 
	{
		if (randInt(1, 2) == 1)
			getWorld()->dropRepair(this);
		else
			getWorld()->dropTorpedo(this);
	}
}

/********************************************
*				Snagglegon					*
********************************************/

void Snagglegon::doSomething()
{
	if (!isAlive())
		return;

	if (getY() >= VIEW_HEIGHT - 1)
		changeTravelDir(DOWN_LEFT);
	else if (getY() <= 0)
		changeTravelDir(UP_LEFT);

	if (collision())
		return;

	if (inLineOfFire())
		if (randInt(1, (15 / getWorld()->getLevel()) + 10) == 1)
			getWorld()->fireTorpedo(this);

	move();

	if (collision())
		return;
}

void Snagglegon::dropGoodie()
{
	if (randInt(1, 6) == 1)
		getWorld()->dropExtraLife(this);
}

/********************************************
*				Goodie						*
********************************************/

void Goodie::doSomething()
{
	if (!isAlive())
		return;

	if (collision())
		return;

	moveOffScreen();

	if (collision())
		return;
}

void Goodie::moveOffScreen()
{
	moveTo(getX() - .75, getY() - .75);
}

bool Goodie::collision()
{
	if (!isAlive())
		return false;
	Actor *p = getWorld()->collision(this, getWorld()->getPlayer());
	if (p != nullptr)
	{
		getWorld()->increaseScore(getScorePoints()); 
		value();
		setState(false);
		getWorld()->playSound(SOUND_GOODIE);
		return true;
	}
	return false;
}

/********************************************
*			Repair Goodie					*
********************************************/

void RepairGoodie::value()
{
	getWorld()->getPlayer()->increaseHitPoints(10);
}

/********************************************
*			Extra Life Goodie				*
********************************************/

void ExtraLifeGoodie::value()
{
	getWorld()->incLives();
}

/********************************************
*			Torpedo Goodie					*
********************************************/

void TorpedoGoodie::value()
{
	getWorld()->getPlayer()->incFlatTor();
}

/********************************************
*			Projectile						*
********************************************/

bool Projectile::collision() 
{
	if (!isAlive())
		return false;
	Actor *p = getWorld()->collision(this, getWorld()->getPlayer());
	if (p != nullptr && p->firedByPlayer() != true)
	{
		getWorld()->getPlayer()->sufferDamage(getDmg());
		setState(false);
		getWorld()->playSound(SOUND_BLAST);
		return true;
	}
	return false;
}


/********************************************
*				Cabbage						*
********************************************/

void Cabbage::doSomething()
{
	if (!isAlive())
		return;

	moveTo(getX() + 8, getY());
	setDirection(getDirection() + 20); 
}

/********************************************
*				Turnip						*
********************************************/

void Turnip::doSomething()
{
	if (!isAlive())
		return;

	if (collision())
		return;

	moveTo(getX() - 6, getY());
	setDirection(getDirection() + 20);
		
	if (collision())
		return;
}

/********************************************
*				Torpedo						*
********************************************/

void FlatulenceTorpedo::doSomething()
{
	if (!isAlive())
		return;
	
	if (collision())
		return;

	if(firedByPlayer())
		moveTo(getX() + 8, getY());	
	else
		moveTo(getX() - 8, getY());
	
	if (collision())
		return;
}

/********************************************
*				Star						*
********************************************/

void Star::doSomething()
{
	moveTo(getX() - 1, getY()); 	//move star
}

/********************************************
*				Explosion					*
********************************************/

void Explosion::doSomething()
{
	if (!isAlive())
		return;
	if(nTicks == 0)
		getWorld()->playSound(SOUND_BLAST); //idk??
	setSize(getSize()*1.5);
	nTicks++;
	if (nTicks > 4) 
		setState(false);
}
