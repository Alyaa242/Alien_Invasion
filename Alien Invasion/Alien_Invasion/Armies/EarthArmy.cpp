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
	//Check that the unit exists
	if (!unit)
		return;

	//Check the unit's type
	if (dynamic_cast<EarthSoldier*>(unit)) {
		ESList.enqueue(unit);
	}
	else if (dynamic_cast<EarthTank*>(unit)) { 
		ETList.push(unit);
	}
	else if (dynamic_cast<EarthGunnery*>(unit)) { 
		EGList.enqueue(unit, unit->getHealth() + unit->getPower());
	}
	else { 
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

	Unit* HU = nullptr;
	if (HUList.peek(HU))
		HU->attack();		//Call attack() of HU to heal
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


bool EarthArmy::isKilled()
{
	//Check if there are any units in the army
	if (ESList.isEmpty() && ETList.isEmpty() && EGList.isEmpty() && HUList.isEmpty())
		return true;

	else
		return false;
}

int EarthArmy::gettotCount()
{
	return ESList.getCount() + ETList.getCount() + EGList.getCount()+ HUList.getCount();
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

ArrayStack<Unit*>* EarthArmy::getHUList()
{
	return &HUList;
}


EarthArmy::~EarthArmy()
{
	Unit* temp;

	//Dequeue each unit in each list and delete it

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

