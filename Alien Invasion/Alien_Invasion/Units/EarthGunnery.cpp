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
	while (counter < getCap() && (!AMEnemies->isEmpty() || !ADEnemies->isEmpty()))
	{
		// attack monster
		int count = AMEnemies->getCount();
		int index;
		if (count != 0)
		{
			index = rand() % count;
			if (AMEnemies->remove(index, enemy))
			{
				int damageAM = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());
				enemy->decHealth(damageAM);
				//Set Ta:
				enemy->setTa(game->getTimestep());

				//If it's killed, add to killed list:
				if (enemy->getHealth() <= 0)
				{
					cout << "AMKilled\n";
					game->addToKilledList(enemy);
					enemy->setTd(game->getTimestep());
				}
				else
				{
					tempList.enqueue(enemy); // store at temp list
				}
				counter++;
			}
		}

		/// attack drones
		if (counter < getCap())
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
				int damageAD = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());
				enemy->decHealth(damageAD);

				//Set Ta:
				enemy->setTa(game->getTimestep());

				//If it's killed, add to killed list:
				if (enemy->getHealth() <= 0) {
					cout << "ADKilled\n";
					game->addToKilledList(enemy);
					enemy->setTd(game->getTimestep());
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
