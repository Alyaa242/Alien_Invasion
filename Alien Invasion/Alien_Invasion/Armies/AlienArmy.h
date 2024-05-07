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
	LinkedQueue<Unit*> ASList;
	Array<Unit*> AMList;
	Deque<Unit*> ADList;

public:

	//Getters for each list (return pointer)

	virtual void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();
	virtual bool isKilled();
	bool pickAS(Unit*& unit);
	bool pickAM(Unit*& unit);
	bool pickFrontAD(Unit*& front);
	bool pickBackAD(Unit*& back);
	int gettotCount();
	LinkedQueue<Unit*>* getASList();
	Array<Unit*>* getAMList();
	Deque<Unit*>* getADList();
	~AlienArmy();
};

