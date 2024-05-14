#include "SaverUnit.h"

SaverUnit::SaverUnit(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setAllyID();
}

void SaverUnit::attack() 
{
	LinkedQueue<Unit*>* ASenemies = game->getASEnemies(); // Ask the game to get the list of enemies this class should attack
	LinkedQueue<Unit*> tempList;
	Unit* enemy;

	//Setting this unit as a fighting unit for the current timestep
	if (capacity && !ASenemies->isEmpty())
		game->setFightingUnit(this);
 
	 
	for (int i = 0; i < capacity; i++)
	{
		 
		// if not infected ==> attack AS
		if (ASenemies->dequeue(enemy)) // get a unit from that list and attack it
		{
			//Adding enemy to attackedByAS list
			game->addAttacked(this, enemy);

			float damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Adding enemy to attackedByES list
			game->addAttacked(this, enemy);

			enemy->decHealth(damage);

			//Set Ta:
			enemy->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) { 
				game->addToKilledList(enemy);
				 
			}
			else
			{
				tempList.enqueue(enemy); // store at temp list
			}
		}
	}

	while (tempList.dequeue(enemy))  //move all items from the temp list back to thier original list
	{ 
		ASenemies->enqueue(enemy);
	}
}

 
