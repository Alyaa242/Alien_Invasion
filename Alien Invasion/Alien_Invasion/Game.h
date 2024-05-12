#pragma once
#include "Armies/Army.h"
#include "Units/Unit.h"
#include "DS\LinkedQueue.h"
#include "DS\ArrayStack.h"
#include "DS\Deque.h"
#include "DS\PriQueue.h"
#include "DS\Array.h"
#include "RandGen.h"
#include "fstream"
class Unit;
class EarthArmy;
class AlienArmy;
class RandGen;
//UML priQueue

class Game
{
	LinkedQueue<Unit*> killedList;
	priQueue <Unit*> UML1; //soldiers
	LinkedQueue <Unit*> UML2; //tanks
	EarthArmy* earthArmy;
    AlienArmy* alienArmy;
	RandGen* randGen;
	// Average Df , Dd , Db for eath and alien
	int AvgDfEarth, AvgDbEarth, AvgDdEarth;
	int AvgDfAlien, AvgDbAlien, AvgDdAlien;
	int timestep;
	char choosen;
	int healcap=0;
	Unit* picked;


	int tot_des_AD = 0;
	int tot_des_AM = 0;
	int tot_des_AS = 0;
	int tot_des_ES = 0;
	int tot_des_ET = 0;
	int tot_des_EG = 0;
	int tot_des_HU = 0;

	//Units fighting this timestep:
	Unit* fightingES;
	Unit* fightingET;
	Unit* fightingEG;
	Unit* fightingAS;
	Unit* fightingAM;
	Unit* fightingAD1;
	Unit* fightingAD2;

	//Units attacked this timestep:
	LinkedQueue<Unit*>	attackedByES;
	LinkedQueue<Unit*>	attackedByET;
	LinkedQueue<Unit*>	attackedByEG;
	LinkedQueue<Unit*>	attackedByAS;
	LinkedQueue<Unit*>	attackedByAM;
	LinkedQueue<Unit*>	attackedByAD1;
	LinkedQueue<Unit*>	attackedByAD2;

	int n;		//number of units generated each timestep
	bool stop;
	bool SilentM, InteractiveM; 

public:

	Game();
	int* ReadInputParameters();		//Function to read parameters from the input file
	void addToKilledList(Unit* unit);
	void addUnits();	//A function that links between RandGen and each army to add units
	void addToUML1(Unit* unit);
	void UpdateUML();
	Unit* PickHU();
	Unit* RemoveHU();
	void addToUML2(Unit* unit);
	Unit* pickfromUML1();
	Unit* pickfromUML2();
	//void Heal();
	void start();	//The main function that implements the game logic
	void printInter();
	int getTimestep();
	void chooseMode();
	void Display();
	
	void setDfEarth(int t);
	void setDdEarth(int t);
	void setDbEarth(int t);
	void setDfAlien(int t);
	void setDdAlien(int t);
	void setDbAlien(int t);
	void addES(Unit* unit);
	void addET(Unit* unit);

	void setFightingUnit(Unit* unit, int x = 1);	//A function that sets current units fighting
	void addAttacked(Unit* attacking, Unit* attacked, int x = 1);	//A function that adds each attacked unit to the appropriate list
	void resetFightingUnits();	//A function for reseting fighting units each timestep

	//Getters for enemies lists:
	LinkedQueue<Unit*>* getESEnemies();
	ArrayStack<Unit*>* getETEnemies();
	priQueue<Unit*>* getEGEnemies();
	LinkedQueue<Unit*>* getASEnemies();
	Array<Unit*>* getAMEnemies();
	Deque<Unit*>* getADEnemies();
	
	//Add printing UML, Ta, Td...
	//Output file

	~Game();
};
