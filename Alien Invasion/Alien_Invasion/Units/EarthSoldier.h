#pragma once
#include "Unit.h"
class Unit;
class EarthSoldier : public Unit
{
	bool infected;
	bool immune;
	static int infectedCount;

public:
	EarthSoldier(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();
	void setInfected(bool x);
	bool isInfeced();
	bool isImmune();
	static int getInfectedCount();
};

