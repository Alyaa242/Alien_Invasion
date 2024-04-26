#include "Unit.h"
#include "EarthTank.h"
#include "EarthSoldier.h"
#include "EarthGunnery.h"

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

int Unit::decHealth(int damage)
{
	return (health-damage);
}

std::ostream& operator<<(std::ostream& out, const Unit& u)
{
	out << u.getID();
	return out;
}
