#include <iostream>
#include "AlienArmy.h"
#include "..\Units\AlienDrone.h"
#include "..\Units\AlienMonster.h"
#include "..\Units\AlienSoldier.h"
#include "..\DS\LinkedQueue.h"
#include "..\DS\ArrayStack.h"
#include "..\DS\Deque.h"
#include "..\DS\PriQueue.h"
#include "..\DS\Array.h"
using namespace std;

void AlienArmy::addUnit(Unit* unit)
{
	if (!unit)
		return;

	if (dynamic_cast<AlienSoldier*>(unit)) {
		ASList.enqueue(unit);
	}
	else if (dynamic_cast<AlienMonster*>(unit)) {
		AMList.insert(unit);
	}
	else {
		ADList.enqueue(unit);
	}
}

void AlienArmy::attack()
{
	Unit* AS = nullptr;
	if(pickAS(AS))
		AS->attack();
	
	Unit* AM = nullptr;
	if(pickAM(AM))
		AM->attack();
	
	Unit* AD1 = nullptr;
	Unit* AD2 = nullptr;
	if (pickFrontAD(AD1) && pickBackAD(AD2)) {
		AD1->attack();
		AD2->attack();
	}
	else if (AD1)
		ADList.enqueue(AD1);

	addUnit(AS);
	addUnit(AM);
	addUnit(AD1);
	addUnit(AD2);
}

void AlienArmy::print()
{
	cout << ASList.getCount() << " AS ";
	ASList.print();
	cout << endl;
	cout << AMList.getCount() << " AM ";
	AMList.print();
	cout << endl;
	cout << ADList.getCount() << " AD ";
	ADList.print();
	cout << endl << endl;
}

LinkedQueue<Unit*> AlienArmy::GetASList()
{
	return ASList;
}

bool AlienArmy::pickAS(Unit*& unit)
{
	if (ASList.dequeue(unit)) {
		return true;
	}
	return false;
}

bool AlienArmy::pickAM(Unit*& unit)
{
	int count = AMList.getCount();
	if (count == 0)
		return false;
	int index = rand() % count;
	if (AMList.remove(index, unit))
		return true;
	return false;
}

bool AlienArmy::pickFrontAD(Unit*& front)
{
	if (ADList.dequeue(front))
		return true;
	return false;
}

bool AlienArmy::pickBackAD(Unit*& back)
{
	if (ADList.removeLast(back))
		return true;
	return false;
}

AlienArmy::~AlienArmy()
{
	Unit* temp;

	while (ASList.dequeue(temp)) {
		delete temp;
	}

	int i = 0;
	while (AMList.remove(i, temp)) {
		delete temp;
		i++;
	}
	
	while (ADList.dequeue(temp)) {
		delete temp;
	}
}

