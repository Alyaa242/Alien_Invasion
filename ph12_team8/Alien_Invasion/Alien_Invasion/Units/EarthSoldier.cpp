#include "EarthSoldier.h"

EarthSoldier::EarthSoldier( int heal, int pow, int cap, int t) : Unit( heal, pow, cap, t)
{
	setEarthID();
}

void EarthSoldier::attack()
{

}
