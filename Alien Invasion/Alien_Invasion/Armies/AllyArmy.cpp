#include <iostream>
#include "AllyArmy.h"
#include "..\DS\LinkedQueue.h"
using namespace std;

void AllyArmy::addUnit(Unit* unit)
{
	if (unit)
		SUList.enqueue(unit);
}

void AllyArmy::attack()
{
	Unit* SU = nullptr;
	if (SUList.peek(SU))
		SU->attack();
}

void AllyArmy::print()
{
	cout << SUList.getCount() << " SU ";
	SUList.print();
	cout << endl << endl;
}

bool AllyArmy::isKilled()
{
	return false;
}

int AllyArmy::gettotCount()
{
	return SUList.getCount();
}

LinkedQueue<Unit*>* AllyArmy::getSUList()
{
	return &SUList;
}

AllyArmy::~AllyArmy()
{
	Unit* temp;

	while (SUList.dequeue(temp)) {
		delete temp;
	}
}
