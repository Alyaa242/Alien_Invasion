#pragma once

#include "..\Units\Unit.h"
#include "Army.h"

class Unit;
class Army;
class EarthGunnery;
class EarthSoldier;
class EarthTank;

class EarthArmy : public Army
{

	LinkedQueue<Unit*> ESList;
	ArrayStack<Unit*> ETList;
	priQueue<Unit*> EGList;

public:

	void addUnit(Unit* unit);
	LinkedQueue<Unit*> GetESList();
	virtual void print();
	bool pickES(Unit*& unit);
	bool pickET(Unit*& unit);
	bool pickEG(Unit*& unit);
	~EarthArmy();
};

