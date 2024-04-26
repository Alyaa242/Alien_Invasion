#include <iostream>
#include "EarthArmy.h"
#include "..\Units\EarthGunnery.h"
#include "..\Units\EarthSoldier.h"
#include "..\Units\EarthTank.h"
#include "..\DS\LinkedQueue.h"
#include "..\DS\ArrayStack.h"
#include "..\DS\Deque.h"
#include "..\DS\PriQueue.h"
#include "..\DS\Array.h"
using namespace std;

void EarthArmy::addUnit(Unit* unit)
{
	if (!unit)
		return;

	if (dynamic_cast<EarthSoldier*>(unit)) {
		ESList.enqueue(unit);
	}
	else if (dynamic_cast<EarthTank*>(unit)) {
		ETList.push(unit);
	}
	else if (dynamic_cast<EarthGunnery*>(unit)) {
		EGList.enqueue(unit, unit->getHealth() + unit->getPower());
	}
	else
	{
		HUList.push(unit);
	}
}

void EarthArmy::attack()
{
	Unit* ES = nullptr;
	if (pickES(ES))
		ES->attack();

	Unit* ET = nullptr;
	if (pickET(ET))
		ET->attack();

	Unit* EG = nullptr;
	if (pickEG(EG))
		EG->attack();

	addUnit(ES);
	addUnit(ET);
	addUnit(EG);
}

LinkedQueue<Unit*> EarthArmy::GetESList()
{
	return ESList;
}

void EarthArmy::print()
{
	cout << ESList.getCount() << " ES ";
	ESList.print();
	cout << endl;
	cout << ETList.getCount() << " ET ";
	ETList.print();
	cout << endl;
	cout << EGList.getCount() << " EG ";
	EGList.print();
	cout << HUList.getCount() << " HU ";
	HUList.print();
	cout << endl << endl;
}

bool EarthArmy::pickES(Unit*& unit)
{
	if (ESList.dequeue(unit))
		return true;
	return false;
}

bool EarthArmy::pickET(Unit*& unit)
{
	if (ETList.pop(unit))
		return true;
	return false;
}

bool EarthArmy::pickEG(Unit*& unit)
{
	int maxpower_health;
	if (EGList.dequeue(unit, maxpower_health))
		return true;
	return false;
}

bool EarthArmy::pickHU(Unit*& unit)
{
	if (HUList.pop(unit))
		return true;
	return false;
}

LinkedQueue<Unit*>* EarthArmy::getESList()
{
	return &ESList;
}

ArrayStack<Unit*>* EarthArmy::getETList()
{
	return &ETList;
}

priQueue<Unit*>* EarthArmy::getEGList()
{
	return &EGList;
}


EarthArmy::~EarthArmy()
{
	Unit* temp;

	while (ESList.dequeue(temp)) {
		delete temp;
	}

	while (ETList.pop(temp)) {
		delete temp;
	}

	int x;
	while (EGList.dequeue(temp, x)) {
		delete temp;
	}

	
	while (HUList.pop(temp)) {
		delete temp;
	}
}

