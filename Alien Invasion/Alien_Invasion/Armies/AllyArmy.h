#pragma once
#include "Army.h"
#include "../Units/Unit.h"

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
	virtual bool isKilled();
	virtual int gettotCount();

	LinkedQueue<Unit*>* getSUList();	//Getter for SUList

	~AllyArmy();
};