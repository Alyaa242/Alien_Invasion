#include "EarthTank.h"

EarthTank::EarthTank( int heal, int pow, int cap, int t) : Unit(  heal, pow, cap, t)
{
	setEarthID();
}

void EarthTank::attack()
{
}

