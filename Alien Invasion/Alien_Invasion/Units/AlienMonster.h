#pragma once
#include "Unit.h"
class Unit;
class AlienMonster : public Unit
{
	int prob;	//Infection probability

public:

	AlienMonster(int heal, int pow, int cap, int t, Game* g, int p);
	virtual void attack();

};

