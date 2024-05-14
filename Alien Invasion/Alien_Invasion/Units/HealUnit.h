#pragma once
#include "Unit.h"
class HealUnit : public Unit
{

	//int cap;
	static int HealedCounter ;

public:
	virtual void attack();
	HealUnit(int heal, int pow, int cap, int t, Game* g);
	 

	static int getHealedCounter();

};

