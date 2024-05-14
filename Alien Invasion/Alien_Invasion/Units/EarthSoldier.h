#pragma once
#include "Unit.h"
class Unit;
class EarthSoldier : public Unit
{
	bool infected;
	bool immune;
	static int infectedCount;
	static int totalInfected;

public:
	EarthSoldier(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();
	void setInfected(bool x);

	void setImmuned(bool x);
	bool getInfected();

	bool isInfeced();
	bool isImmune();
	static int getInfectedCount();

	static int getTotalInfected();


};