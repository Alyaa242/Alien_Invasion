#pragma once
#include "Unit.h"
class Unit;
class AlienDrone : public Unit
{

public:
	AlienDrone( int heal, int pow, int cap, int t);
	virtual void attack();

};

