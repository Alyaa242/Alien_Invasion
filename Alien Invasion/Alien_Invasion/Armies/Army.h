#pragma once
#include "..\Units\Unit.h"
class Unit;
class Army
{
protected:

	int totCount;	//Total count of current units in lists

public:

	virtual void addUnit(Unit* unit) = 0;
	virtual void attack() = 0;
	virtual void print() = 0;
	virtual bool isKilled() = 0;	//To know if army has any units left
	virtual int gettotCount() = 0;	//Get total count of army units
};

