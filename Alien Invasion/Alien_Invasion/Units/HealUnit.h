#pragma once
#include "Unit.h"
class HealUnit : public Unit
{

	//int cap;


public:
	virtual void attack();
	HealUnit(int heal, int pow, int cap, int t, Game* g);
	void UpdateHU();



};

