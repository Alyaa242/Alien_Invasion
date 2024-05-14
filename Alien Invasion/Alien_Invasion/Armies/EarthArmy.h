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
	//Lists of units
	LinkedQueue<Unit*> ESList;
	ArrayStack<Unit*> ETList;
	priQueue<Unit*> EGList;
	ArrayStack<Unit*> HUList;

	int static totalES;
	int static totalET;
	int static totalEG;
	int static totalHU;

public:

	virtual void addUnit(Unit* unit);
	virtual void attack();
	virtual void print();
	virtual bool isKilled();
	virtual int gettotCount();

	bool pickHU(Unit*& unit);
	bool RemoveHU(Unit*& unit);
 
	int getTotES();
	int getTotET();
	int getTotEG();
	int getTotHU();

	//Getters for each list
	LinkedQueue<Unit*>* getESList();
	ArrayStack<Unit*>* getETList();
	priQueue<Unit*>* getEGList();
	ArrayStack<Unit*>* getHUList();

	~EarthArmy();
};

