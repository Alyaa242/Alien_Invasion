#pragma once
#include "Unit.h"
class Unit;
class AlienSoldier : public Unit
{
public:

	AlienSoldier(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();

};

