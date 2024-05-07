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
	ArrayStack<Unit*> HUList;


	//priQueue<Unit*> HUList;

public:

	//Getters for each list (return pointer)

	void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();
	virtual bool isKilled();
	bool pickES(Unit*& unit);
	bool pickET(Unit*& unit);
	bool pickEG(Unit*& unit);
	bool pickHU(Unit*& unit);
	LinkedQueue<Unit*>* getESList();
	ArrayStack<Unit*>* getETList();
	priQueue<Unit*>* getEGList();
	~EarthArmy();
};

