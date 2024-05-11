#pragma once
#include "Unit.h"

class SaverUnit : public Unit
{
public:
	SaverUnit(int heal, int pow, int cap, int t, Game* g);
	virtual void attack();
};