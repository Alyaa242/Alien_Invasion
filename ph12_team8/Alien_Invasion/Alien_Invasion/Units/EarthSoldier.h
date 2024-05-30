#pragma once
#include "Unit.h"
class Unit;
class EarthSoldier : public Unit
{
public:
	EarthSoldier( int heal, int pow, int cap, int t);
	virtual void attack();

};

