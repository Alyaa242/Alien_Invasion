#include "EarthTank.h"

EarthTank::EarthTank(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthTank::attack()
{
}

