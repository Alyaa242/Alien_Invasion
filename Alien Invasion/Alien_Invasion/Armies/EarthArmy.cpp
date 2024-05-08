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
	if (ESList.peek(ES))	//Call attack() of the front ES
		ES->attack();

	Unit* ET = nullptr;
	if (ETList.peek(ET))	//Call attack() of the last ET (peek of the stack)
		ET->attack();

	Unit* EG = nullptr;
	int maxpower_health;
	if (EGList.peek(EG, maxpower_health))	//Call attack() of EG with the max power & health
		EG->attack();
		
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
	cout << endl;
	cout << HUList.getCount() << " HU ";
	HUList.print();
	cout << endl << endl;
}

int EarthArmy::gettotCount()
{
	return ESList.getCount() + ETList.getCount() + EGList.getCount()+ HUList.getCount();
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
	if (HUList.peek(unit))
		return true;
	return false;
}

bool EarthArmy::RemoveHU(Unit*& unit)
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

