#pragma once
#include "Unit.h"
class Unit;
class AlienDrone : public Unit
{
	bool isSecond;	//Bool to know if this AD is currently used as the second one in attack()

public:

	AlienDrone(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();
	void setIsSecond(bool x);

};

