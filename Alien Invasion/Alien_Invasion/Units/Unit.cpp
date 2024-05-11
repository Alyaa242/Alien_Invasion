#include "Unit.h"
#include "EarthTank.h"
#include "EarthSoldier.h"
#include "EarthGunnery.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"

//Initializing IDs:
int Unit::lastEarthID = 1;
int Unit::lastAlienID = 2000;

Unit::Unit(int heal, int pow, int cap, int t, Game* g)
{ 
	health = heal;
	power = pow;
	capacity = cap;
	Tj = t;
	game = g;
	attacked = false;
}

int Unit::getHealth() const
{
	return health;
}

int Unit::getPower() const
{
	return power;
}

int Unit::getCap() const
{
	return capacity;
}

int Unit::getTj() const
{
	return Tj;
}

int Unit::getTa() const
{
	return Ta;
}

int Unit::getTd() const
{
	return Td;
}

int Unit::getID() const
{
	return ID;
}

int Unit::getDd() const
{
	return Dd;
}

int Unit::getDb() const
{
	return Db;
}

int Unit::getDf() const
{
	return Df;
}

bool Unit::isAttacked() const
{
	return attacked;
}

void Unit::setAttacked(bool x)
{
	attacked = x;
}

void Unit::setTa(int t)
{
	if (!attacked) {
		Ta = t;
		attacked = true;
	}
	Df = Ta - Tj;

	if (dynamic_cast<AlienMonster*>(this) || dynamic_cast<AlienSoldier*>(this) || dynamic_cast<AlienDrone*>(this))
		game->setDfAlien(Df);
	else
		game->setDfEarth(Df);
}

void Unit::setTd(int t)
{
	Td = t;
	Dd = Td - Ta;
	Db = Td - Tj;

	if (dynamic_cast<AlienMonster*>(this) || dynamic_cast<AlienSoldier*>(this) || dynamic_cast<AlienDrone*>(this))
	{
		game->setDdAlien(Dd);
		game->setDbAlien(Db);
	}
	else
	{
		game->setDdEarth(Dd);
		game->setDbEarth(Db);
	}
}

void Unit::setDd(int t)
{
	Dd = t;
}

void Unit::setDb(int t)
{
	Db = t;
}

void Unit::setDf(int t)
{
	Df = t;
}

//Setting IDs:
void Unit::setEarthID()
{
	ID = lastEarthID++;
}

void Unit::setAlienID()
{
	ID = lastAlienID++;
}
//

void Unit::decHealth(int damage)
{
	health -= damage;
}

void Unit::incHealth(int increment)
{
	health += increment;
	return;
}


int Unit::getWait()
{
	return wait;
}

void Unit::setWait(int w)
{
	wait = w;
}


std::ostream& operator<<(std::ostream& out, Unit* u)
{
	out << u->getID();
	if (dynamic_cast<EarthSoldier*>(u)) {
		if(dynamic_cast<EarthSoldier*>(u)->isInfeced())
			out << "*";
	}
	return out;
}
