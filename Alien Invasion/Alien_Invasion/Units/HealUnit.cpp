#include "HealUnit.h"

void HealUnit::attack()
{
	int h;
	Unit* unit= game->pickfromUML1();
	if (!unit)
		unit = game->pickfromUML2();
	if (!unit)
		return;
	h = ((getPower()) * (getHealth()) / 100) / sqrt(unit->getHealth());
	unit->incHealth(h);

}


HealUnit::HealUnit(int heal, int pow, int cap, int t, Game* g) :  Unit(heal, pow, cap, t, g) 
{
	setEarthID();
}

void HealUnit::UpdateHU()
{
	//if (getTj() +10 < game->getTimestep())
	//	game->addToKilledList(this);
}

