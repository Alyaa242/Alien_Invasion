#include "AlienDrone.h"

AlienDrone::AlienDrone(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienDrone::attack()
{
}
