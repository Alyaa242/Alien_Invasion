#pragma once
#include "Unit.h"
class Unit;
class EarthTank : public Unit
{
public:
	EarthTank(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();
};

