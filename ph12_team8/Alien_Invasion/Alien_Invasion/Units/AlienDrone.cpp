#include "AlienDrone.h"

AlienDrone::AlienDrone( int heal, int pow, int cap, int t) : Unit( heal, pow, cap, t)
{
	setAlienID();
}

void AlienDrone::attack()
{
}
