#include "AlienMonster.h"

AlienMonster::AlienMonster(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienMonster::attack()
{
}
