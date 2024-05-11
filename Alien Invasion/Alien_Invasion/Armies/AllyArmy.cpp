#include "AllyArmy.h"

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
	cout << SUList.getCount() << " HU ";
	SUList.print();
	cout << endl << endl;
}
