#pragma once
#include "..\Units\Unit.h"
class Unit;
class Army
{
protected:
	int count;

public:

	Army();
	virtual void addUnit(Unit* unit) = 0;
	virtual void attack() = 0;
	virtual void print() = 0;
	virtual bool isKilled() = 0;
	~Army();
};

