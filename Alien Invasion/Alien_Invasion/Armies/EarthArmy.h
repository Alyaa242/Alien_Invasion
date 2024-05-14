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

	int static totalES;
	int static totalET;
	int static totalEG;
	int static totalHU;
	//priQueue<Unit*> HUList;

public:

	//Getters for each list (return pointer)

	virtual void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();
	virtual bool isKilled();
 
	int gettotCount();
    
	bool pickES(Unit*& unit);
	bool pickET(Unit*& unit);
	bool pickEG(Unit*& unit);
	bool pickHU(Unit*& unit);
	bool RemoveHU(Unit*& unit);
	int getTotES();
	int getTotET();
	int getTotEG();
	int getTotHU();
	LinkedQueue<Unit*>* getESList();
	ArrayStack<Unit*>* getETList();
	priQueue<Unit*>* getEGList();
	ArrayStack<Unit*>* getHUList();
	~EarthArmy();
};

