#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "Units\EarthGunnery.h"
#include "Units\EarthSoldier.h"
#include "Units\EarthTank.h"
#include "Units\AlienDrone.h"
#include "Units\AlienMonster.h"
#include "Units\AlienSoldier.h"

using namespace std;

Game::Game()
{
	timestep = 0;
	earthArmy = new EarthArmy ;
	alienArmy = new AlienArmy;
	randGen = new RandGen(ReadInputParameters(), this);		//passing the parameters and pointer to game to randGen
}

int* Game::ReadInputParameters()
{
	int* arr = new int[21];

	ifstream InFile;
	InFile.open("read.txt");
	if (!InFile.is_open())	return nullptr;
	for (int i = 0; i < 9; i++)
	{
		InFile >> arr[i];
	}
	char c;
	for (int i = 9; i < 21; i++)
	{
		if (i % 2) InFile >> arr[i];
		else InFile >> c >> arr[i];
	}
	InFile.close();

	n = arr[0];

	return arr;
}

void Game::addToKilledList(Unit* unit)
{
	killedList.enqueue(unit);
}

void Game::addUnits()
{
	Unit** arrEarth = randGen->GenerateEarthUnits();	//To get array of created earth units at this timestep
	Unit** arrAlien = randGen->GenerateAlienUnits();		//To get array of created alien units at this timestep
	

	//Adding each unit to its army:

	if (arrEarth)	//Check that GenerateEarthUnits() was performed successfully
		for (int i = 0; i < n; i++)
		{
			if (arrEarth[i])	//Check there are earth units generated at this timestep
				earthArmy->addUnit(arrEarth[i]);
		}

	if (arrAlien)	//Check that GenerateAlienUnits() was performed successfully
		for (int i = 0; i < n; i++)
		{
			if (arrAlien[i])//Check there are alien units generated at this timestep
		          alienArmy->addUnit(arrAlien[i]);
		}

	delete arrEarth;
	delete arrAlien;
}

void Game::addToUML(Unit* unit)
{
 	UML.enqueue(unit,unit->getCap());
}


void Game::UpdateUML()
{
	//for (int i{};i<)
}

void Game::Heal()
{
	Unit* unit;
	int max_cap;
	UML.dequeue(unit,max_cap);



}

void Game::start()
{
	while (timestep < 50) {

		//Call attack for each army

		addUnits();		//Adding units generated from randGen

		int x = rand() % 100 + 1;

		if (x < 10) {
			Unit* ES;
			if(earthArmy->pickES(ES))
				earthArmy->addUnit(ES);
		}
		else if (x < 20) {
			Unit* ET;
			if(earthArmy->pickET(ET))
				killedList.enqueue(ET);
		}
		else if (x < 30) {
			Unit* EG;
			if (earthArmy->pickEG(EG)) {
				EG->decHealth(EG->getHealth() / 2);
				if (EG->getHealth() <= 0)
					addToKilledList(EG);
				else
					earthArmy->addUnit(EG);
			}
		}
		else if (x < 40) {
			Unit* arr[5] = {};
			for (int i = 0; i < 5; i++) {
				Unit* AS;
				if (alienArmy->pickAS(AS)) {
					AS->decHealth(AS->getHealth() / 2);
					if (AS->getHealth() <= 0)
						addToKilledList(AS);
					arr[i] = AS;
				}
			}
			for (int i = 0; i < 5; i++) {
				if (arr[i])
					alienArmy->addUnit(arr[i]);
			}
		}
		else if (x < 50) {
			Unit* AM;
			for (int i = 0; i < 5; i++) {
				if (alienArmy->pickAM(AM))
					alienArmy->addUnit(AM);
			}
		}
		else if (x < 60) {
			Unit* frontAD;
			Unit* backAD;
			for (int i = 0; i < 3; i++) {
				if (alienArmy->pickFrontAD(frontAD))
					killedList.enqueue(frontAD);
				if (alienArmy->pickBackAD(backAD))
					killedList.enqueue(backAD);
			}
		}
		earthArmy->attack();
		print();
		timestep++;
		cin.get();	//Wait for user to press enter
	}
}

void Game::print()
{
	cout << "Current TimeStep " << timestep << endl;
	cout << "=========================== Earth Army Alive Units ===========================\n";
	earthArmy->print();
	cout << "=========================== Alien Army Alive Units ===========================\n";
    alienArmy->print();
	cout << "=========================== Killed/Destructed Units ===========================\n";
	cout<< killedList.getCount()<<" units ";
	killedList.print();
	cout << endl << endl;
}

int Game::getTimestep()
{
	return timestep;
}

LinkedQueue<Unit*>* Game::getESEnemies()
{
	return earthArmy->getESList();
}

ArrayStack<Unit*>* Game::getETEnemies()
{
	return earthArmy->getETList();
}

priQueue<Unit*>* Game::getEGEnemies()
{
	return earthArmy->getEGList();
}

LinkedQueue<Unit*>* Game::getASEnemies()
{
	return alienArmy->getASList();
}

Array<Unit*>* Game::getAMEnemies()
{
	return alienArmy->getAMList();
}

Deque<Unit*>* Game::getADEnemies()
{
	return alienArmy->getADList();
}

Game::~Game()
{
	cout << "DESTRUCTING GAME .... \n";
	delete alienArmy;
	delete earthArmy;
	delete randGen;
}
