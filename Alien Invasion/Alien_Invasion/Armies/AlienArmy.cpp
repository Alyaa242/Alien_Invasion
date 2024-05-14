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

int AlienArmy::totalAS=0;
int AlienArmy::totalAM=0;
int AlienArmy::totalAD=0;

void AlienArmy::addUnit(Unit* unit)
{
	//Check that the unit exists
	if (!unit)
		return;

	//Check the unit's type
	if (dynamic_cast<AlienSoldier*>(unit)) {
		totalAS++;
		ASList.enqueue(unit);
	}
	else if (dynamic_cast<AlienMonster*>(unit)) {
		totalAM++;
		AMList.insert(unit);
	}
	else {
		totalAD++;
		ADList.insert(unit);
	}
}

void AlienArmy::attack()
{
	Unit* AS = nullptr;
	if(ASList.peek(AS))		//Call attack() of the front AS
		AS->attack();
	
	Unit* AM = nullptr;
	int count = AMList.getCount();
	//Call attack() of random AM
	if (count) {
		int index = rand() % count;
		if (AMList.atIndx(index, AM))
			AM->attack();
	}

	Unit* AD1 = nullptr;
	Unit* AD2 = nullptr;
	//Call attack() of the front and back ADs
	if (ADList.peek(AD1) && ADList.peekBack(AD2) && AD1 != AD2) {
		AD1->attack();
		dynamic_cast<AlienDrone*>(AD2)->setIsSecond(true);
		AD2->attack();
		dynamic_cast<AlienDrone*>(AD2)->setIsSecond(false);
	}
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

bool AlienArmy::isKilled()
{
	if (ASList.isEmpty() && AMList.isEmpty() && ADList.isEmpty())
		return true;

	else
		return false;
}
int AlienArmy::getTotAS()
{
	return totalAS;
}
int AlienArmy::getTotAM()
{
	return totalAM;
}
int AlienArmy::getTotAD()
{
	return totalAD;
}
int AlienArmy::gettotCount()
{
	return ASList.getCount() + AMList.getCount() + ADList.getCount();
}

LinkedQueue<Unit*>* AlienArmy::getASList()
{
	return &ASList;
}

Array<Unit*>* AlienArmy::getAMList()
{
	return &AMList;
}

Deque<Unit*>* AlienArmy::getADList()
{
	return &ADList;
}

AlienArmy::~AlienArmy()
{
	Unit* temp;

	//Dequeue each unit in each list and delete it

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

