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

void Game::addToUML1(Unit* unit)
{
  	UML1.enqueue(unit,-unit->getHealth());

	unit->setWait(timestep);



}
void Game::addToUML2(Unit* unit)
{
	UML2.enqueue(unit);

	unit->setWait(timestep);
}

Unit* Game::pickfromUML1()
{
	Unit* unit;
	int max_health;
	
	if (UML1.peek(unit, max_health))
		return unit;
	else return nullptr;
}

Unit* Game::pickfromUML2()
{
	Unit* unit;
	
	if (UML2.peek(unit))
		return unit;
	else return nullptr;
}

void Game::UpdateUML()
{
	Unit* unit;int max_health;
	for (int i{};i< UML1.getCount();i++)
	
	{
		UML1.peek(unit, max_health);
		if (timestep- unit->getWait() > 9)
		{
			UML1.dequeue(unit,max_health);
			addToKilledList(unit);
		}
	}


	for (int i{};i < UML2.getCount();i++)

	{
		UML2.peek(unit);
		if (timestep-unit->getWait() > 9)
		{
			UML2.dequeue(unit);
			addToKilledList(unit);
		}
	}
}





void Game::PickHU()
{
	
	
	if (healcap)
	{
		if (!UML1.isEmpty() || !UML2.isEmpty() )
		healcap--;
	}
	
		else
	
	{
		if (!earthArmy->pickHU(picked))
		{

			return;
		}

		else
			healcap = picked->getCap();
	}
		
}





void Game::Heal()
{
	Unit* unit;
	int max_health;
	int h; 
	LinkedQueue <Unit*> tempList1;
	LinkedQueue <Unit*> tempList2;
	//Unit* picked;
	UpdateUML();
	PickHU();
	
	if (!picked)
		return;


	if (healcap)
	{
		if (!UML1.isEmpty())
		{
           picked->attack();
		  if (UML1.dequeue(unit, max_health))
			
			if (unit->getHealth() <= 20)

				tempList1.enqueue(unit);
			else
				earthArmy->addUnit(unit);
		}
		else

		{
			picked->attack();
			if (UML2.dequeue(unit))
			
			if (unit->getHealth() <= 20)

				tempList2.enqueue(unit);
			else
				earthArmy->addUnit(unit);

		}
	}
		else

	{
		earthArmy->RemoveHU(picked);
		addToKilledList(picked);cout << "lllllllllllllllllllllllll\n";
	

		while (!tempList1.isEmpty())
		{
			if (tempList1.dequeue(unit))
				UML1.enqueue(unit, -unit->getHealth());
		}

		while (!tempList2.isEmpty())
		{
			if (tempList2.dequeue(unit))
				UML2.enqueue(unit);

		}
	}

}

void Game::start()
{
	while (timestep < 50) {

		//Call attack for each army	
		addUnits();		//Adding units generated from randGen
		alienArmy->attack();
		Heal();
		/*int x = rand() % 100 + 1;

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
			Unit* frontAD = nullptr;
			Unit* backAD = nullptr;
			for (int i = 0; i < 3; i++) {
				if (alienArmy->pickFrontAD(frontAD))
					killedList.enqueue(frontAD);

				if (alienArmy->pickBackAD(backAD))
					killedList.enqueue(backAD);
			}
		}

		earthArmy->attack();
		if (choosen == 2)
			printInter();

		earthArmy->attack();*/
		printInter();


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
	UML1.print();cout << endl;
	cout << "=========================== UML2 ===========================\n";
	UML2.print();cout << endl;
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
	int countKL= killedList.getCount();
	while (countKL--)
	{
		Unit* unit;
		killedList.dequeue(unit);
	    outfile << unit->getTd() <<" "<<unit->getID()<<" "<<unit->getTj()<<"\n";
	}

	outfile << "Battle Result . . .\n";
	outfile << "For Earth Army\n";
	outfile << "Total number of ES : ";
	outfile << "Total number of ET : ";
	outfile << "Total number of EG : ";
	outfile << "Total number of HU : ";
	outfile << " Total Destructed_ES \ Total ES";
	outfile << " Total Destructed_ET \ Total ET";
	outfile << " Total Destructed_EG \ Total EG";
	outfile << " Total Destructed_HU \ Total HU";
	outfile << "Total Destructed Units \ Total Units ";outfile <<killedList.getCount() <<" \ "<<  earthArmy->gettotCount() + alienArmy->gettotCount();
	

	outfile << "For Alien Army\n";
	outfile << "Total number of AS : ";
	outfile << "Total number of AT : ";
	outfile << "Total number of AG : ";
	outfile << " Total Destructed_AS \ Total AS";
	outfile << " Total Destructed_AT \ Total AT";
	outfile << " Total Destructed_AG \ Total AG";
	outfile << "Total Destructed Units \ Total Units ";outfile << killedList.getCount() << " \ " << earthArmy->gettotCount() + alienArmy->gettotCount();
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
