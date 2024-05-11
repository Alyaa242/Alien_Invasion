#include "SaverUnit.h"

SaverUnit::SaverUnit(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setAllyID();
}

void SaverUnit::attack()
{
}
