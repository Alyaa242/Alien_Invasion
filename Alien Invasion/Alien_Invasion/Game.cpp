#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "Armies/AllyArmy.h"
#include "Units\EarthGunnery.h"
#include "Units\EarthSoldier.h"
#include "Units\EarthTank.h"
#include "Units\AlienDrone.h"
#include "Units\AlienMonster.h"
#include "Units\AlienSoldier.h"

using namespace std;

Game::Game()
{
	AvgDbAlien = 0;
	AvgDbEarth = 0;
	AvgDdAlien = 0;
	AvgDdEarth = 0;
	AvgDfEarth = 0;
	AvgDfAlien = 0;
	timestep = 0;
	stop = true; 
	InteractiveM = false;
	noMoreSU = false;
	earthArmy = new EarthArmy
		;
	alienArmy = new AlienArmy;
	allyArmy = new AllyArmy;
	randGen = new RandGen(ReadInputParameters(), this);		//passing the parameters and pointer to game to randGen
}

int* Game::ReadInputParameters()
{
	int* arr = new int[29];

	ifstream InFile;
	InFile.open("read.txt");
	if (!InFile.is_open())	return nullptr;
	for (int i = 0; i < 9; i++)
	{
		InFile >> arr[i];
	}
	char c;
	for (int i = 9; i < 27; i++)
	{
		if (i % 2) InFile >> arr[i];
		else InFile >> c >> arr[i];
	}
	InFile >> arr[27] >> arr[28];
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
	Unit** arrSaver = nullptr;

	if(!noMoreSU)
		arrSaver = randGen->GenerateSaverUnits(EarthSoldier::getInfectedCount() / float(earthArmy->gettotCount()) * 100);
	

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

	if (arrSaver)	//Check that GenerateAlienUnits() was performed successfully
		for (int i = 0; i < n; i++)
		{
			if (arrSaver)//Check there are alien units generated at this timestep
				allyArmy->addUnit(arrSaver[i]);
		}

	delete[] arrEarth;
	delete[] arrAlien;
	delete[] arrSaver;



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
	
	if (UML1.dequeue(unit, max_health))
		return unit;
	else return nullptr;
}

Unit* Game::pickfromUML2()
{
	Unit* unit;
	
	if (UML2.dequeue(unit))
		return unit;
	else return nullptr;
}

void Game::UpdateUML()
{
	Unit* unit;int max_health;
	//cout << "UUUMMMMMMMMMMMMLLLLLLLLL";
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





Unit* Game::PickHU()
{
	
	Unit* picked;
	if (earthArmy->pickHU(picked))
		return picked;
	else return nullptr;
}

Unit* Game::RemoveHU()
{
	Unit* picked;
	if (earthArmy->RemoveHU(picked))
		return picked;
	else return nullptr;
}

//
//void Game::Heal()
//{
//	Unit* unit;
//	int max_health;
//	int h; 
//	LinkedQueue <Unit*> tempList1;
//	LinkedQueue <Unit*> tempList2;
//	Unit* picked;
//	UpdateUML();
//	
//
//
//	if (healcap)
//	{
//		if (!UML1.isEmpty())
//		{
//           picked->attack();
//		  if (UML1.dequeue(unit, max_health))
//			
//			if (unit->getHealth() <= 20)
//
//			{
//				tempList1.enqueue(unit);cout << "MMMMMMMMMMMMMMMMMMM";
//			}
//			else
//			{
//				earthArmy->addUnit(unit);cout << "loooooolllllllllllllllll";
//			}
//		}
//		else
//
//		{
//			picked->attack();
//			if (UML2.dequeue(unit))
//			
//			if (unit->getHealth() <= 20)
//
//			{
//				tempList2.enqueue(unit);cout << "MMMMMMMMMMMMMMMMMMM";
//			}
//			else
//			{
//				earthArmy->addUnit(unit);cout << "loooooolllllllllllllllll";
//			}
//
//		}
//	}
//		else
//
//	{
//	 //cout << "lllllllllllllllllllllllll\n";
//		if	(earthArmy->RemoveHU(picked))
//	//if (!UML1.isEmpty() ||!UML2.isEmpty())
//
//		addToKilledList(picked);
//
//		while (!tempList1.isEmpty())
//		{
//			if (tempList1.dequeue(unit))
//				UML1.enqueue(unit, -unit->getHealth());
//		}
//
//		while (!tempList2.isEmpty())
//		{
//			if (tempList2.dequeue(unit))
//				UML2.enqueue(unit);
//
//		}
//	}
//	
//
//	
//
//
//}

void Game::start()
{ 
	while (stop)
	{

		addUnits();		//Adding units generated from randGen	

		if (InteractiveM) {
			printInter();
			cin.get();	//Wait for user to press enter
		}

		resetFightingUnits();	//Reset current fighting units to null

		//Call attack for each army	
		earthArmy->attack();
		alienArmy->attack();
		UpdateUML();
	 
		if (timestep >= 40)
		{
			if (InteractiveM) {
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
			else {
				if (alienArmy->isKilled() || earthArmy->isKilled()) {
					cout << "Simulation ended...\n";
					Display();
					cout << "Output File created.\n";
					stop = false;
				}
			}
		}


		timestep++;

	}
}

void Game::printInter()
{
	cout << "Current TimeStep " << timestep << endl;
	cout << "=========================== Earth Army Alive Units ===========================\n";
	earthArmy->print();
	cout << "=========================== Alien Army Alive Units ===========================\n";
    alienArmy->print();
	if (allyArmy) {
		cout << "=========================== Ally Army Alive Units ===========================\n";
		allyArmy->print();
	}
	cout << "=========================== Killed/Destructed Units ===========================\n";
	cout<< killedList.getCount()<<" units ";
	killedList.print();
	cout << endl;


	cout << "=========================== Units fighting at current step ===========================\n";
	if (fightingAS) 
	{
		cout << "AS " << fightingAS->getID() << " shots ";
		while (!attackedByAS.isEmpty())
		{
			Unit* unit;
			attackedByAS.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;
	if (fightingAM)
	{
		cout << "AM " << fightingAM->getID() << " shots ";
		while (!attackedByAM.isEmpty())
		{
			Unit* unit;
			attackedByAM.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;

	if (fightingAD1)
	{
		cout << "AD1 " << fightingAD1->getID() << " shots ";
		while (!attackedByAD1.isEmpty())
		{
			Unit* unit;
			attackedByAD1.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;
	if (fightingAD2)
	{
		cout << "AD2 " << fightingAD2->getID() << " shots ";
		while (!attackedByAD2.isEmpty())
		{
			Unit* unit;
			attackedByAD2.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;


	if (fightingEG)
	{
		cout << "EG " << fightingEG->getID() << " shots ";
		while (!attackedByEG.isEmpty())
		{
			Unit* unit;
			attackedByEG.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;
	if (fightingET)
	{
		cout << "ET " << fightingET->getID() << " shots ";
		while (!attackedByET.isEmpty())
		{
			Unit* unit;
			attackedByET.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	cout << endl;
	if (fightingES)
	{
		cout << "ES " << fightingES->getID() << " shots ";
		while (!attackedByES.isEmpty())
		{
			Unit* unit;
			attackedByES.dequeue(unit);
			cout << unit->getID() << " ";


		}
	}
	
	

	cout << endl;

	cout << "=========================== UML1 ===========================\n";
	UML1.print();cout << endl;
	cout << "=========================== UML2 ===========================\n";
	UML2.print();cout << endl;

	cout << endl << endl;

}

int Game::getTimestep()
{
	return timestep;
}

void Game::chooseMode()
{
	cout << "=========================== Select Mode ===========================\n";
	cout << "Press S for Silent Mode\n";
	cout << "Press I for Interactive Mode\n";

	cin >> choosen;
	if (choosen == 'S')
	{
		cout << "Silent Mode\nSimulationStarts . . .\n";
	}
	else
		InteractiveM = true;

}


void Game::Display()
{
	ofstream outfile;
	outfile.open("output.txt");
	outfile << "Td    ID    Tj    Df    Dd    Db\n";
	int countKL = killedList.getCount();
	while (countKL--)
	{
		Unit* unit;
		killedList.dequeue(unit);
		outfile << unit->getTd() << "    " << unit->getID() << "    " << unit->getTj() << "     " << unit->getDf() << "     " << unit->getDd() << "     " << unit->getDb() << "\n";
	}

	outfile << "Battle Result . . .\n";//
	if (alienArmy->isKilled())
		outfile << "EARTH ARMY WIN ! ! !";
	else
		outfile << "ALIEN ARMY WIN ! ! !";
	outfile << "For Earth Army\n";
	outfile << "Total number of ES : " << earthArmy->getESList()->getCount() << endl;
	outfile << "Total number of ET : " << earthArmy->getETList()->getCount() << endl;
	outfile << "Total number of EG : " << earthArmy->getEGList()->getCount() << endl;
	outfile << "Total number of HU : ";
	outfile << " Total Destructed_ES \ Total ES" << tot_des_ES << " \ " << earthArmy->getESList()->getCount() << endl;
	outfile << " Total Destructed_ET \ Total ET" << tot_des_ET << " \ " << earthArmy->getETList()->getCount() << endl;
	outfile << " Total Destructed_EG \ Total EG" << tot_des_ES << " \ " << earthArmy->getEGList()->getCount() << endl;
	outfile << " Total Destructed_HU \ Total HU";
	outfile << "Total Destructed Units \ Total Units ";
	int tot_des_earth = tot_des_ET + tot_des_ES + tot_des_EG + tot_des_HU;
	outfile << tot_des_earth << " \ " << earthArmy->gettotCount() << endl;
	outfile << "Df/Db = " <<AvgDfEarth <<" / "<< AvgDbEarth << "     " << "Dd/Db = "<<AvgDdEarth<<" / "<<AvgDbEarth ;

	outfile << endl << endl << endl;

	outfile << "For Alien Army\n";
	outfile << "Total number of AD : " << alienArmy->getADList()->getCount() << endl;
	outfile << "Total number of AM : " << alienArmy->getAMList()->getCount() << endl;
	outfile << "Total number of AS : " << alienArmy->getASList()->getCount() << endl;
	outfile << " Total Destructed_AS \ Total AD" << tot_des_AD << " \ " << alienArmy->getADList()->getCount();
	outfile << " Total Destructed_AM \ Total AM" << tot_des_AM << " \ " << alienArmy->getAMList()->getCount();
	outfile << " Total Destructed_AG \ Total AS" << tot_des_AS << " \ " << alienArmy->getASList()->getCount();
	outfile << "Total Destructed Units \ Total Units ";
	int tot_des_alien = tot_des_AD + tot_des_AM + tot_des_AS;
	outfile << tot_des_alien << " \ " << alienArmy->gettotCount() << endl;
	outfile << "Df/Db = " << AvgDfAlien << " / " << AvgDbAlien << "     " << "Dd/Db = " << AvgDdAlien << " / " << AvgDbAlien;

	outfile.close();
}


void Game::setFightingUnit(Unit* unit, int x)
{
	if (dynamic_cast<EarthSoldier*>(unit)) {
		fightingES = unit;
	}
	else if (dynamic_cast<EarthTank*>(unit)) {
		fightingET = unit;
	}
	else if (dynamic_cast<EarthGunnery*>(unit)) {
		fightingEG = unit;
	}
	else if (dynamic_cast<AlienSoldier*>(unit)) {
		fightingAS = unit;
	}
	else if (dynamic_cast<AlienMonster*>(unit)) {
		fightingAM = unit;
	}
	else if (dynamic_cast<AlienDrone*>(unit) && x == 1) {
		fightingAD1 = unit;
	}
	else {
		fightingAD2 = unit;
	}
}

void Game::addAttacked(Unit* attacking, Unit* attacked, int x)
{
	if (dynamic_cast<EarthSoldier*>(attacking)) {
		attackedByES.enqueue(attacked);
	}
	else if (dynamic_cast<EarthTank*>(attacking)) {
		attackedByET.enqueue(attacked);
	}
	else if (dynamic_cast<EarthGunnery*>(attacking)) {
		attackedByEG.enqueue(attacked);
	}
	else if (dynamic_cast<AlienSoldier*>(attacking)) {
		attackedByAS.enqueue(attacked);
	}
	else if (dynamic_cast<AlienMonster*>(attacking)) {
		attackedByAM.enqueue(attacked);
	}
	else if (dynamic_cast<AlienDrone*>(attacking) && x == 1) {
		attackedByAD1.enqueue(attacked);
	}
	else {
		attackedByAD2.enqueue(attacked);
	}
}

void Game::resetFightingUnits()
{
	fightingES = nullptr;
	fightingET = nullptr;
	fightingEG = nullptr;
	fightingAS = nullptr;
	fightingAM = nullptr;
	fightingAD1 = nullptr;
	fightingAD2 = nullptr;

	Unit* temp;
	while (!attackedByET.isEmpty())
		attackedByET.dequeue(temp);
	while (!attackedByES.isEmpty())
		attackedByES.dequeue(temp);
	while (!attackedByEG.isEmpty())
		attackedByEG.dequeue(temp);
	while (!attackedByAS.isEmpty())
		attackedByAS.dequeue(temp);
	while (!attackedByAM.isEmpty())
		attackedByAM.dequeue(temp);
	while (!attackedByAD1.isEmpty())
		attackedByAD1.dequeue(temp);
	while (!attackedByAD2.isEmpty())
		attackedByAD2.dequeue(temp);
}



void Game::setDfEarth(int t)
{
	AvgDfEarth += t;
}

void Game::setDdEarth(int t)
{
	AvgDdEarth += t;
}

void Game::setDbEarth(int t)
{
	AvgDbEarth += t;
}

void Game::setDfAlien(int t)
{
	AvgDfAlien += t;
}

void Game::setDdAlien(int t)
{
	AvgDdAlien += t;
}

void Game::setDbAlien(int t)
{
	AvgDbAlien += t;
}

void Game::addES(Unit* unit)
{
	earthArmy->addUnit(unit);//cout << "addddddddddd";
}

void Game::addET(Unit* unit)
{
	earthArmy->addUnit(unit);
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

	Unit* temp;
	int dummy;

	while (killedList.dequeue(temp)) {
		delete temp;
	}

	while (UML1.dequeue(temp, dummy)) {
		delete temp;
	}

	while (UML2.dequeue(temp)) {
		delete temp;
	}

}
