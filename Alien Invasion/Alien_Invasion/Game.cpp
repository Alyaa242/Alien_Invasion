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
	stop = true;
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

void Game::addToUML1(Unit* unit)
{
  	UML1.enqueue(unit,-unit->getHealth());
	//setWait();

}
void Game::addToUML2(Unit* unit)
{
	UML2.enqueue(unit);
}

Unit* Game::pickfromUML1()
{
	Unit* unit;
	int max_health;
	
	UML1.dequeue(unit, max_health);
	return unit;
}

Unit* Game::pickfromUML2()
{
	Unit* unit;
	
	UML2.dequeue(unit);
	return unit;
}

void Game::UpdateUML()
{
	Unit* unit;int max_health;
	for (int i{};i< UML1.getCount();i++)
	
	{
		UML1.peek(unit, max_health);
		if (getWait(unit) > 10)
		{
			UML1.dequeue(unit,max_health);
			addToKilledList(unit);
		}
	}


	for (int i{};i < UML2.getCount();i++)

	{
		UML2.peek(unit);
		if (getWait(unit) > 10)
		{
			UML2.dequeue(unit);
			addToKilledList(unit);
		}
	}
}

int Game::getWait(Unit* unit)
{
	return wait ;
}

void Game::Heal()
{
	Unit* unit;
	int max_health;
	int h; 
	LinkedQueue <Unit*> tempList1;
	LinkedQueue <Unit*> tempList2;
	Unit* picked;
	earthArmy->pickHU(picked);
	int healcap= picked->getCap();

	while (healcap--)
	{
		if (!UML1.isEmpty())
		{

			UML1.dequeue(unit, max_health);
			picked->attack();
			if (unit->getHealth() <= 20)
			
				tempList1.enqueue(unit);
		}
		else

		{
			
			UML2.dequeue(unit);
			picked->attack();
			if (unit->getHealth() <= 20)

				tempList2.enqueue(unit);


		}
	}
	while (!tempList1.isEmpty())
	{
		tempList1.dequeue(unit);
		UML1.enqueue(unit,max_health);
	}

	while (!tempList2.isEmpty())
	{
		tempList2.dequeue(unit);
		UML2.enqueue(unit);
	}

	addToKilledList(picked);

}

void Game::start()
{ 
	while (stop)
	{
		addUnits();		//Adding units generated from randGen
		alienArmy->attack();
		earthArmy->attack();
		printInter();
		if (timestep >= 40)
		{
			if (alienArmy->isKilled())
			{
				cout << "=========================== The winner is the Earth Army ===========================\n";
				stop = false;
			}
			else if (earthArmy->isKilled())
			{
				cout << "=========================== The winner is the Alien Army ===========================\n";
				stop = false;
			}
		}
		timestep++;
		cin.get();	//Wait for user to press enter

	}
}

void Game::printInter()
{
	cout << "Current TimeStep " << timestep << endl;
	cout << "=========================== Earth Army Alive Units ===========================\n";
	earthArmy->print();
	cout << "=========================== Alien Army Alive Units ===========================\n";
    alienArmy->print();
	cout << "=========================== Killed/Destructed Units ===========================\n";
	cout<< killedList.getCount()<<" units ";
	killedList.print();
	cout << endl;


	cout << "=========================== UML1 ===========================\n";
	UML1.print();
	cout << "=========================== UML2 ===========================\n";
	UML2.print();
	cout << endl << endl;

}

void Game::printSilent()
{
	cout << "Silent Mode\n SimulationStarts . . . \n Simulation ends, Output file is created \n";
}

int Game::getTimestep()
{
	return timestep;
}

void Game::chooseMode()
{
	cout << "=========================== Select Mode ===========================\n";
	cout << " Press 1 for Silent Mode\n";
	cout << " Press 2 for Interactive Mode\n";
	
	cin >> choosen;
	if (choosen==1) 
	 printSilent();
}

void Game::Display()
{
	ofstream outfile;
	outfile.open("output.txt");
	outfile << "Td   ID   Tj   Df   Dd   Db\n";
	

}

void Game::setWait(int w)
{
	wait = w;
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
