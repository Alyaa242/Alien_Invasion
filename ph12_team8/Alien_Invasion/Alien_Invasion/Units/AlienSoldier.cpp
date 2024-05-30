#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(  int heal, int pow, int cap, int t) : Unit( heal, pow, cap, t)
{
	setAlienID();
}

void AlienSoldier::attack()
{
}
