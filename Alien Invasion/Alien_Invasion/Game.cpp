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
	isSUGen = false;
	earthArmy = new EarthArmy;
	alienArmy = new AlienArmy;
	allyArmy = new AllyArmy;
	cout << "Enter File Name: \n";
	cin >> fileName;
	randGen = new RandGen(ReadInputParameters(), this);		//passing the parameters and pointer to game to randGen
}

int* Game::ReadInputParameters()
{
	int* arr = new int[29];

	ifstream InFile;
	InFile.open(fileName);
	if (!InFile.is_open())	return nullptr;
	for (int i = 0; i < 9; i++)
	{
		InFile >> arr[i];
	}
	char c;
	for (int i = 9; i < 27; i++)
	{
		if (i % 2)
			InFile >> arr[i];
		else
			InFile >> c >> arr[i];
	}
	InFile >> arr[27] >> arr[28];
	InFile.close();

	n = arr[0];

	return arr;
}

void Game::addToKilledList(Unit* unit)
{
	killedList.enqueue(unit);

	if (dynamic_cast<AlienSoldier*>(unit)) {
		tot_des_AS++;
		AvgDfAlien += unit->getDf();
	}
	else if (dynamic_cast<AlienMonster*>(unit)) {
		tot_des_AM++;
		AvgDfAlien += unit->getDf();
	}
	else if (dynamic_cast<AlienDrone*>(unit)) {
		tot_des_AD++;
		AvgDfAlien += unit->getDf();
	}

	else if (dynamic_cast<EarthSoldier*>(unit)) {
		tot_des_ES++;
		AvgDfEarth += unit->getDf();
	}
	else if (dynamic_cast<EarthTank*>(unit)) {
		tot_des_ET++;
		AvgDfEarth += unit->getDf();
	}
	else if (dynamic_cast<EarthGunnery*>(unit)) {
		tot_des_EG++;
		AvgDfEarth += unit->getDf();
	}
	else if (dynamic_cast<HealUnit*>(unit))
	{
		tot_des_HU++;
	}


	unit->setTd(timestep);
}

void Game::addUnits()
{
	Unit** arrEarth = randGen->GenerateEarthUnits();	//To get array of created earth units at this timestep
	Unit** arrAlien = randGen->GenerateAlienUnits();		//To get array of created alien units at this timestep
	Unit** arrSaver = nullptr;

	 
	if (!SUwithdrawal()) {
		arrSaver = randGen->GenerateSaverUnits(EarthSoldier::getInfectedCount() / float(earthArmy->gettotCount()) * 100);
		isSUGen = true;
	}
	
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
			if (arrAlien[i])	//Check there are alien units generated at this timestep
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

	while (stop)

	{
		if (timestep == 8)
			int x = 0;

		resetFightingUnits();	//Reset current fighting units to null

		addUnits();		//Adding units generated from randGen	

		//Call attack for each army	
		earthArmy->attack();
		alienArmy->attack();
		allyArmy->attack();
		UpdateUML();
	 
		if (InteractiveM) {
			printInter();
			cin.get();	//Wait for user to press enter
		}

		if (timestep >= 40)
		{
			if (InteractiveM) {
				if (alienArmy->isKilled() && earthArmy->isKilled())
				{
					cout << "=========================== The Earth Army Parity with The Alien Army ===========================\n";
					Display();
					stop = false;
				}
				else if (alienArmy->isKilled())
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
					cout << "Simulation ended . . .\n";
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

	cout << "=========================== Ally Army Alive Units ===========================\n";
	allyArmy->print();

	cout << "=========================== Units fighting at current step ===========================\n";

	if (fightingAD1 || fightingAD2 || fightingAS|| fightingAM|| fightingES|| fightingEG|| fightingET || fightingSU)

	{
		if (fightingES)
		{
			cout << "ES " << fightingES->getID() << " shots ";
			attackedByES.print();
			cout << endl;
		}

		if (fightingET)
		{
			cout << "ET " << fightingET->getID() << " shots ";

			attackedByET.print();
			cout << endl;
		}

		if (fightingEG)
		{
			cout << "EG " << fightingEG->getID() << " shots ";
			attackedByEG.print();
			cout << endl;
		}

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

		if (fightingSU)
		{
			cout << "SU " << fightingSU->getID() << " shots ";
			attackedBySU.print();
			cout << endl;

		}

	}
	else
		cout << "NO Units Attacking at this timestep\n";
	cout << endl;

	cout << "=========================== Killed/Destructed Units ===========================\n";
	cout << killedList.getCount() << " units ";
	killedList.print();
	cout << endl << endl;
	
	cout << "=========================== UML1 ===========================\n";
	UML1.print();
	cout << endl << endl;
	cout << "=========================== UML2 ===========================\n";
	UML2.print();
	cout << endl << endl;

	cout << "============= Current Percentage of Infected Soldiers =============\n";
	if (total_ES())
		cout << (float(EarthSoldier::getInfectedCount()) / (total_ES()+ UML1.getCount()) * 100) <<"%\n";
	else
		cout << "There is No EarthSoldiers \n";

	cout << endl << endl;

}


int Game::getTimestep()
{
	return timestep;
}


bool Game::SUwithdrawal()
{
	if (EarthSoldier::getInfectedCount() == 0 && isSUGen)
	{ 
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
	outfile << "Td";outfile << setw(6);
	outfile << "ID";outfile << setw(6);
	outfile << "Tj";outfile << setw(6);
	outfile << "Df";outfile << setw(6);
	outfile << "Dd";outfile << setw(6);
	outfile << "Db";
	outfile << endl;

	Unit* unit;

	while (killedList.dequeue(unit))
	{
		outfile << unit->getTd(); outfile << setw(6);
		outfile << unit->getID(); outfile << setw(6);
		outfile << unit->getTj(); outfile << setw(6);
		outfile << unit->getDf(); outfile << setw(6);
		outfile << unit->getDd(); outfile << setw(6);
		outfile << unit->getDb() << "\n";
	}
 
	outfile << endl << endl;
	outfile << "Battle Result . . .\n\n\n";
 
	if (alienArmy->isKilled())
		outfile << "EARTH ARMY WIN ! ! !\n";
	else
		outfile << "ALIEN ARMY WIN ! ! !\n";


	outfile << "For Earth Army\n";

	outfile << "Total number of ES : " << earthArmy->getTotES() << endl;
	outfile << "Total number of ET : " << earthArmy->getTotET() << endl;
	outfile << "Total number of EG : " << earthArmy->getTotEG() << endl;
	outfile << "Total number of HU : " << earthArmy->getTotHU() << endl;

	if (earthArmy->getTotES())
		outfile << "Total Destructed_ES / Total ES "<<  setw(10) << float(tot_des_ES *1.0/ earthArmy->getTotES()) * 100 << "%" << setw(10) << endl;
	else
		outfile << "There is no EarthSoldiers \n";

	if  (earthArmy->getTotET())
		outfile << "Total Destructed_ET / Total ET " << setw(10) << float(tot_des_ET*1.0 / earthArmy->getTotET()) * 100 << "%" << setw(10) << endl;
	else
		outfile << "There is no EarthTanks \n";

	if (earthArmy->getTotEG())
		outfile << "Total Destructed_EG / Total EG " << setw(10) << float(tot_des_ES*1.0 / earthArmy->getTotEG()) * 100 << "%" << setw(10) << endl;
	else
		outfile << "There is no EarthGunnery \n";

	if (earthArmy->getTotHU())
		outfile << "Total Destructed_HU / Total HU " << setw(10) << float(tot_des_HU *1.0 / earthArmy->getTotHU()) * 100 << "%" << endl;
	else
		outfile << "There is no HealUnits\n";

	outfile << "Total Destructed Units / Total Units ";
	int tot_des_earth = tot_des_ET + tot_des_ES + tot_des_EG + tot_des_HU;
	int tot_earth = earthArmy->getTotES()+ earthArmy->getTotET()+ earthArmy->getTotEG()+ earthArmy->getTotHU();

	if (tot_earth)
		outfile << float(tot_des_earth*1.0 / tot_earth ) * 100<<"%" << endl;
	else
		outfile << "There is no Earth Army\n";

	AvgDfEarth /= (tot_des_earth- tot_des_HU);
	AvgDbEarth /= (tot_des_earth - tot_des_HU);
	AvgDdEarth /= (tot_des_earth- tot_des_HU);

	outfile << "Average of Df : " << AvgDfEarth<<endl;
	outfile << "Average of Dd : " << AvgDdEarth<<endl;
	outfile << "Average of Db : " << AvgDbEarth<<endl;

	if (AvgDbEarth)
		outfile << "Df/Db = " << float(AvgDfEarth*1.0 / AvgDbEarth) *100 << "%     ";
	if (AvgDbEarth)
		outfile << "Dd/Db = " << float(AvgDdEarth*1.0 / AvgDbEarth) *100<<"%" << endl;

	if (tot_earth)
		outfile << "Total Successful Healed Units / Total EarthUnits" << setw(10)  << float(HealUnit::getHealedCounter()*1.0 / tot_earth) * 100<<"%\n";
	else
		outfile << "There is no Earth Army\n";

	if (earthArmy->getTotES())
		outfile << "Percentage of Infected to earthsoldiers" << setw(8) << float(EarthSoldier::getTotalInfected() * 1.0 / earthArmy->getTotES()) * 100 << "%";



	outfile << endl << endl << endl;




	outfile << "For Alien Army\n";
	outfile << "Total number of AD : " << alienArmy->getTotAD() << endl;
	outfile << "Total number of AM : " << alienArmy->getTotAM() << endl;
	outfile << "Total number of AS : " << alienArmy->getTotAS() << endl;
	if (alienArmy->getTotAD())
		outfile << "Total Destructed_AS / Total AS " << setw(10) << float(tot_des_AD*1.0 / alienArmy->getTotAD()) * 100 <<  "%" << endl;
	else
		outfile << "There is no AlienSoldiers \n";

	if (alienArmy->getTotAM())
		outfile << "Total Destructed_AM / Total AM " << setw(10) << float(tot_des_AM*1.0 / alienArmy->getTotAM() ) * 100 << "%" << endl;
	else
		outfile << "There is no AlienMonster \n";

	if (alienArmy->getTotAS())
		outfile << "Total Destructed_AG / Total AG " << setw(10)<< float(tot_des_AS*1.0 / alienArmy->getTotAS()) * 100 << "%" << endl;
	else
		outfile << "There is no AlienGunnery \n";

	outfile << "Total Destructed Units / Total Units ";
	int tot_des_alien = tot_des_AD + tot_des_AM + tot_des_AS;
	int tot_alien = alienArmy->getTotAD() + alienArmy->getTotAS() + alienArmy->getTotAM();
	if (tot_alien)
		outfile << float (tot_des_alien*1.0 / tot_alien) * 100<<"%" << endl;
	else
		outfile << "There is no Alien Army\n";


	AvgDfAlien/=tot_des_alien ;
	AvgDbAlien/= tot_des_alien;
	AvgDdAlien/= tot_des_alien ;

	outfile << "Average of Df : " << AvgDfAlien<<endl;
	outfile << "Average of Dd : " << AvgDdAlien<<endl;
	outfile << "Average of Db : " << AvgDbAlien<<endl;

	if (AvgDbAlien)
		outfile << "Df/Db = " << float (AvgDfAlien*1.0 / AvgDbAlien )*100  << "%     ";
	if (AvgDbAlien)
		outfile << "Dd/Db = " << float (AvgDdAlien*1.0 / AvgDbAlien)*100<<"%\n";


	
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
	earthArmy->addUnit(unit); 
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
	
	delete alienArmy;
	delete earthArmy;
	delete allyArmy;
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
