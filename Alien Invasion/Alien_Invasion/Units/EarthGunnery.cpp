#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(  int heal, int pow, int cap, int t) : Unit( heal, pow, cap, t)
{
	setEarthID();
}

void EarthGunnery::attack()
{
}

