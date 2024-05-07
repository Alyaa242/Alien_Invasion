#pragma once
#include "..\Units\Unit.h"
class Unit;
class Army
{
protected:
	int count;
	int totCount;

public:

	Army();
	virtual void addUnit(Unit* unit) = 0;
	virtual void attack() = 0;
	virtual void print() = 0;
	virtual bool isKilled() = 0;
	virtual int gettotCount()=0 ;
	~Army();
};

