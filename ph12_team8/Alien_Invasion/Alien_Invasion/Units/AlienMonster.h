#pragma once
#include "Unit.h"
class Unit;
class AlienMonster : public Unit
{

public:
	AlienMonster( int heal, int pow, int cap, int t);
	virtual void attack();

};

