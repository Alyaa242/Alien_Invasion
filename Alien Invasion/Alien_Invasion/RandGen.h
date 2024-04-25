#pragma once
#include "Units/Unit.h"
#include "Game.h"
class Unit;
class Game;

class RandGen
{
	int* parameters;

	//enum just to make index readable
	enum paramIndex
	{
		n = 0,
		ESPer, ETPer, EGPer,
		ASPer, AMPer, ADPer, 
		prob,
		lowPowE, upPowE,
		lowHealE, upHealE,
		lowCapE, upCapE,
		lowPowA, upPowA,
		lowHealA, upHealA,
		lowCapA, upCapA,
	};

	Game* game;		//pointer to game


public:

	RandGen(int* param, Game* g);
	//We need to pass game ptr to each unit's constructor
	Unit* CreateEarthUnit();	//Create one unit
	Unit* CreateAlienUnit();
	Unit** GenerateEarthUnits();	//Generate array of units pointers (units generated each timestep)
	Unit** GenerateAlienUnits();
	~RandGen();
};

