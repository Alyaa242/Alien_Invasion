#include "AlienMonster.h"

AlienMonster::AlienMonster(  int heal, int pow, int cap, int t) : Unit( heal, pow, cap, t)
{
	setAlienID();
}

void AlienMonster::attack()
{
}
