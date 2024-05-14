#pragma once
#include "Army.h"
#include "..\Units\Unit.h"


class Unit;
class Army;
class AlienDrone;
class AlienSoldier;
class AlienMonster;

class AlienArmy : public Army
{
	//Lists of units
	LinkedQueue<Unit*> ASList;
	Array<Unit*> AMList;
	Deque<Unit*> ADList;

public:

	virtual void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();
	virtual bool isKilled();
	virtual int gettotCount();

	//Getters for each list
	LinkedQueue<Unit*>* getASList();
	Array<Unit*>* getAMList();
	Deque<Unit*>* getADList();

	~AlienArmy();
};

