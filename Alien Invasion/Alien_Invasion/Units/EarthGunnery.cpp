#include "EarthGunnery.h"
#include "AlienMonster.h"
EarthGunnery::EarthGunnery(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthGunnery::attack()
{
	Deque<Unit*>* ADEnemies = game->getADEnemies();
	Array<Unit*>* AMEnemies = game->getAMEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> tempList;
	int counter = 0;
	int ADflag = 0;

	//Setting this unit as a fighting unit for the current timestep
	if(capacity && (!AMEnemies->isEmpty() || !ADEnemies->isEmpty()))
		game->setFightingUnit(this);

	while (counter < capacity && (!AMEnemies->isEmpty() || !ADEnemies->isEmpty()))
	{
		// attack monster
		int count = AMEnemies->getCount();
		int index;
		if (count != 0)
		{
			index = rand() % count;
			if (AMEnemies->remove(index, enemy))
			{
				float damageAM = (float(power * getHealth()) / 100) / sqrt(enemy->getHealth());

				//Adding enemy to attackedByEG list
				game->addAttacked(this, enemy);

				enemy->decHealth(damageAM);
				//Set Ta:
				enemy->setTa(game->getTimestep());

				//If it's killed, add to killed list:
				if (enemy->getHealth() <= 0)
				{ 
					game->addToKilledList(enemy); 
				}
				else
				{
					tempList.enqueue(enemy); // store at temp list
				}
				counter++;
			}
		}

		/// attack drones
		if (counter < capacity)
		{
			bool fromlast = false;
			bool fromfront = false;

			if (ADflag % 2 == 0)
			{
				fromfront = ADEnemies->dequeue(enemy);
			}
			else
			{
				fromlast = ADEnemies->removeLast(enemy);
			}

			if (fromlast || fromfront)
			{
				float damageAD = (float(power * getHealth()) / 100) / sqrt(enemy->getHealth());

				//Adding enemy to attackedByEG list
				game->addAttacked(this, enemy);

				enemy->decHealth(damageAD);

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
				counter++;
				ADflag++;
			}


		}

	}

	while (tempList.dequeue(enemy))  //move all items from the temp list back to thier original list
	{
		if (dynamic_cast<AlienMonster*>(enemy))
			AMEnemies->insert(enemy);
		else
			ADEnemies->insert(enemy);

	}

}
