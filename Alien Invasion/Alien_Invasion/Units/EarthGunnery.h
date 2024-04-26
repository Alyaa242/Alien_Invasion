#pragma once
#include "Unit.h"
class Unit;
class EarthGunnery : public Unit
{
public:
	EarthGunnery(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();

};

