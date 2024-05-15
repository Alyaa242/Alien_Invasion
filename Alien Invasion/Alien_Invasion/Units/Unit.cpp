#include "Unit.h"
#include "EarthTank.h"
#include "EarthSoldier.h"
#include "EarthGunnery.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"
#include "HealUnit.h"

//Initializing IDs:
int Unit::lastEarthID = 1;
int Unit::lastAlienID = 2000;
int Unit::lastAllyID = 4000;

Unit::Unit(int heal, int pow, int cap, int t, Game* g)
{ 
	health = heal;
	power = pow;
	capacity = cap;
	Tj = t;
	game = g;
	attacked = false;
}

long double Unit::getHealth() const
{
	return health;
}

long double Unit::getPower() const
{
	return power;
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
	else if (dynamic_cast<EarthGunnery*>(this) || dynamic_cast<EarthSoldier*>(this) || dynamic_cast<EarthTank*>(this))
	
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
void Unit::setAllyID()
{
	ID = lastAllyID++;
}
//

void Unit::decHealth(long double damage)
{
	health -= damage;
}

void Unit::incHealth(long double increment)
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

int Unit::getLastEarthID()
{
	return lastEarthID;
}

int Unit::getLastAlienID()
{
	return lastAlienID;
}

std::ostream& operator<<(std::ostream& out, Unit* u)
{
	if (dynamic_cast<EarthSoldier*>(u) && dynamic_cast<EarthSoldier*>(u)->isInfeced()) {
		out << "\033[31m" << u->getID() << "*" << "\033[0m";		//Color infected ES red
	}
	else if(dynamic_cast<HealUnit*>(u))
		out << "\033[32m" << u->getID() << "\033[0m";		//Color HU green
	else
		out << u->getID();
	return out;
}
