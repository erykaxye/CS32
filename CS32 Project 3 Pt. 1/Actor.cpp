#include "Actor.h"
#include "StudentWorld.h"


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

bool Actor::isAlive() const
{
	//if off screen return false else return true 
	if (getX() < 0 || getX() > VIEW_WIDTH - 1)
		return false;
	else if (getY() < 0 || getY() > VIEW_HEIGHT - 1)
		return false;
	return true;
}

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
		}
	}
}

bool NachenBlaster::isAlive() const
{
	/*
	if (getHealth() <= 0)
		return false;
		*/
	return true;
}

void NachenBlaster::setHealth(int n)
{
	m_health += n;
	if (m_health >= 50)
		m_health = 50;
}

void Star::doSomething()
{
	moveTo(getX() - 1, getY()); 	//move star
}