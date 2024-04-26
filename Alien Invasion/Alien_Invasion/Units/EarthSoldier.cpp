#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthSoldier::attack()
{

}
