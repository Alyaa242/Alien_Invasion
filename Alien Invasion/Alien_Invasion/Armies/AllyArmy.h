#pragma once
#include "Army.h"
#include "../Units/SaverUnit.h"

class Unit;
class Army;
class SaverUnit;

class AllyArmy : public Army
{
	LinkedQueue<Unit*> SUList;

public:

	virtual void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();

};