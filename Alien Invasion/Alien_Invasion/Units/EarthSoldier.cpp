#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthSoldier::attack()
{
	LinkedQueue<Unit*>* ASenemies = game->getASEnemies(); // Ask the game to get the list of enemies this class should attack
	LinkedQueue<Unit*> tempList;
	Unit* attack;  

	//Setting this unit as a fighting unit for the current timestep
	game->setFightingUnit(this);

	for (int i = 0; i < getCap(); i++)
	{
		if (ASenemies->dequeue(attack)) // get a unit from that list and attack it
		{
			int damage = (float(getPower() * getHealth()) / 100) / sqrt(attack->getHealth());
			attack->decHealth(damage);
			//Set Ta:
			attack->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (attack->getHealth() <= 0) {
				game->addToKilledList(attack);
				attack->setTd(game->getTimestep());
			}
			else
			{
				tempList.enqueue(attack); // store at temp list
			}
		}
		else
			break;
	}
	while (tempList.dequeue(attack))  //move all items from the temp list back to thier original list
	{
		ASenemies->enqueue(attack);
	}
}
