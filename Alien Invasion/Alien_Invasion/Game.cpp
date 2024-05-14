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
#include "Units/HealUnit.h"
#include "iomanip"

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
	IsSUgen = false;
	earthArmy = new EarthArmy;
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
	unit->setTd(timestep);
}

void Game::addUnits()
{
	Unit** arrEarth = randGen->GenerateEarthUnits();	//To get array of created earth units at this timestep
	Unit** arrAlien = randGen->GenerateAlienUnits();		//To get array of created alien units at this timestep
	Unit** arrSaver = nullptr;

	SUwithdrawal();

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


void Game::start()
{ 
	while (timestep<40)
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
					Display();
					stop = false;
				}
				else if (earthArmy->isKilled())
				{
					cout << "=========================== The winner is the Alien Army ===========================\n";
					Display();
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
	if (fightingAD1 || fightingAD2 || fightingAS|| fightingAM|| fightingES|| fightingEG|| fightingET)
	{
		if (fightingAS)
		{
			cout << "AS " << fightingAS->getID() << " shots ";
			attackedByAS.print();
			cout << endl;
		}

		if (fightingAM)
		{
			cout << "AM " << fightingAM->getID() << " shots ";
			attackedByAM.print();
			cout << endl;
		}


		if (fightingAD1)
		{
			cout << "AD1 " << fightingAD1->getID() << " shots ";
			attackedByAD1.print();
			cout << endl;
		}

		if (fightingAD2)
		{
			cout << "AD2 " << fightingAD2->getID() << " shots ";
			attackedByAD2.print();
			cout << endl;
		}



		if (fightingEG)
		{
			cout << "EG " << fightingEG->getID() << " shots ";
			attackedByEG.print();
			cout << endl;
		}

		if (fightingET)
		{
			cout << "ET " << fightingET->getID() << " shots ";
			
			attackedByET.print();
			cout << endl;
		}

		if (fightingES)
		{
			cout << "ES " << fightingES->getID() << " shots ";
			attackedByES.print();
			cout << endl;
		}


	}
	else
	cout << "NO Units Attacking at this timestep\n";
	

	cout << "=========================== UML1 ===========================\n";
	UML1.print();cout << endl;
	cout << "=========================== UML2 ===========================\n";
	UML2.print();cout << endl;
	cout << "=============Current percentage of infected soldiers=============\n";
	if (total_ES())
		cout << float(EarthSoldier::getInfectedCount() * 1.0 / (total_ES()+ UML1.getCount() +UML2.getCount()))*100 <<"%";
	else
		cout << "There is No EarthSoldiers \n";

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

bool Game::SUwithdrawal()
{
	if (EarthSoldier::getInfectedCount() == 0 && IsSUgen)
	{
		noMoreSU = true;
		LinkedQueue<Unit*>* Sulist = allyArmy->getSUList();
		Unit* unit;
		while (Sulist->dequeue(unit))
		{
			addToKilledList(unit);
		}
		return true;
	}
	return false;
}

 

void Game::Display()
{
	ofstream outfile;
	outfile.open("output.txt");
	//outfile << setw(6);
	outfile << "Td";outfile << setw(6);
	outfile << "ID";outfile << setw(6);
	outfile << "Tj";outfile << setw(6);
	outfile << "Df";outfile << setw(6);
	outfile << "Dd";outfile << setw(6);
	outfile << "Db";outfile << setw(6);
	outfile << endl;

	int countKL = killedList.getCount();
	while (countKL--)
	{
		Unit* unit;
		killedList.dequeue(unit);
		outfile << unit->getTd();outfile << setw(6);
		outfile << unit->getID();outfile << setw(6);
		outfile << unit->getTj();outfile << setw(6);
		outfile << unit->getDf();outfile << setw(6);
		outfile << unit->getDd();outfile << setw(6);
		outfile<< unit->getDb() << "\n";
	}
	outfile << endl << endl;
	outfile << "Battle Result . . .\n\n\n";//
	if (alienArmy->isKilled())
		outfile << "EARTH ARMY WIN ! ! !\n";
	else
		outfile << "ALIEN ARMY WIN ! ! !\n";

	outfile << "For Earth Army\n";

	outfile << "Total number of ES : " << earthArmy->getESList()->getCount() << endl;
	outfile << "Total number of ET : " << earthArmy->getETList()->getCount() << endl;
	outfile << "Total number of EG : " << earthArmy->getEGList()->getCount() << endl;
	outfile << "Total number of HU : " << earthArmy->getHUList()->getCount() << endl;

	if (earthArmy->getESList()->getCount())
		outfile << "Total Destructed_ES / Total ES " << float(tot_des_ES *1.0/ earthArmy->getESList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no EarthSoldiers \n";

	if (earthArmy->getETList()->getCount())
		outfile << "Total Destructed_ET / Total ET " << float(tot_des_ET*1.0 / earthArmy->getETList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no EarthTanks \n";

	if (earthArmy->getEGList()->getCount())
		outfile << "Total Destructed_EG / Total EG " << float(tot_des_ES*1.0 / earthArmy->getEGList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no EarthGunnery \n";

	if (earthArmy->getHUList()->getCount())
		outfile << "Total Destructed_HU / Total HU " << float(tot_des_HU *1.0 / earthArmy->getHUList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no HealUnits\n";

	outfile << "Total Destructed Units / Total Units ";
	int tot_des_earth = tot_des_ET + tot_des_ES + tot_des_EG + tot_des_HU;
	if (earthArmy->gettotCount())
		outfile << float(tot_des_earth*1.0 / earthArmy->gettotCount()) * 100 << endl;
	else
		outfile << "There is no Earth Army\n";

	if (AvgDbEarth)
		outfile << "Df/Db = " << float(AvgDfEarth*1.0 / AvgDbEarth) * 100 << "     ";
	if (AvgDbEarth)
		outfile << "Dd/Db = " << float(AvgDdEarth*1.0 / AvgDbEarth) * 100;

	if (earthArmy->gettotCount())
		outfile << " Total Successful Healed Units / Total EarthUnits " << float(HealUnit::getHealedCounter()*1.0 / earthArmy->gettotCount()) * 100;
	else
		outfile << "There is no Earth Army\n";

	outfile << endl << endl << endl;

	outfile << "For Alien Army\n";
	outfile << "Total number of AD : " << alienArmy->getADList()->getCount() << endl;
	outfile << "Total number of AM : " << alienArmy->getAMList()->getCount() << endl;
	outfile << "Total number of AS : " << alienArmy->getASList()->getCount() << endl;
	if (alienArmy->getADList()->getCount())
		outfile << " Total Destructed_AS \ Total AS " << float(tot_des_AD*1.0 / alienArmy->getADList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no AlienSoldiers \n";

	if (alienArmy->getAMList()->getCount())
		outfile << "Total Destructed_AM \ Total AM " << float(tot_des_AM*1.0 / alienArmy->getAMList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no AlienMonster \n";

	if (alienArmy->getASList()->getCount())
		outfile << "Total Destructed_AG \ Total AG " << float(tot_des_AS*1.0 / alienArmy->getASList()->getCount()) * 100 << "%" << endl;
	else
		outfile << "There is no AlienGunnery \n";

	outfile << "Total Destructed Units \ Total Units ";
	int tot_des_alien = tot_des_AD + tot_des_AM + tot_des_AS;

	if (alienArmy->gettotCount())
		outfile << float (tot_des_alien*1.0 / alienArmy->gettotCount()) * 100<<"%" << endl;
	else
		outfile << "There is no Alien Army\n";

	if (AvgDbAlien)
		outfile << "Df/Db = " << float (AvgDfAlien*1.0 / AvgDbAlien) * 100 << "%     ";
	if (AvgDbAlien)
		outfile << "Dd/Db = " << float (AvgDdAlien*1.0 / AvgDbAlien)*100;

	outfile.close();

	//SU ATTACK WHO
	//PERCENT OF INFECTED
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
	else if (dynamic_cast<AlienDrone*>(unit) && x == 2) {
		fightingAD2 = unit;
	}
	else {
		fightingSU = unit;
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
	else if (dynamic_cast<AlienDrone*>(attacking) && x == 2) {
		attackedByAD2.enqueue(attacked);
	}
	else {
		attackedBySU.enqueue(attacked);
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

int Game::total_ES()
{
	return earthArmy->getESList()->getCount();
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

LinkedQueue<Unit*>* Game::getSUEnemies()
{
	return allyArmy->getSUList();
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
