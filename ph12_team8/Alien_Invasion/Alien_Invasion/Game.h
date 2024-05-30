#pragma once
#include "Armies/Army.h"
#include "Units/Unit.h"
#include "DS\LinkedQueue.h"
#include "DS\ArrayStack.h"
#include "DS\Deque.h"
#include "DS\PriQueue.h"
#include "DS\Array.h"
#include "RandGen.h"

class Unit;
class EarthArmy;
class AlienArmy;
class RandGen;

class Game
{
	LinkedQueue<Unit*> killedList;
	EarthArmy* earthArmy;
    AlienArmy* alienArmy;
	RandGen* randGen;
	int timestep;
	int n;		//number of units generated each timestep

public:

	Game();
	int* ReadInputParameters();		//Function to read parameters from the input file
	void addToKilledList(Unit* unit);
	void addUnits();	//A function that links between RandGen and each army to add units
	void start();	//The main function that implements the game logic
	void print();
	int getTimestep();
	~Game();
};
