#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthGunnery::attack()
{
}

