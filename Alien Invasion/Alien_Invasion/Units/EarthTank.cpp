#include "EarthTank.h"
#include "AlienSoldier.h"
EarthTank::EarthTank(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthTank::attack()
{
	LinkedQueue<Unit*>* ASEnemies = game->getASEnemies();
	LinkedQueue<Unit*>* ESlist = game->getESEnemies();
	Array<Unit*>* AMEnemies = game->getAMEnemies();
	LinkedQueue<Unit*> tempList;

	Unit* enemy;
	float percentage = (ASEnemies->getCount() != 0)? ((float((ESlist->getCount()))) / (ASEnemies->getCount())) * 100 : INT_MIN;

	bool Npass; // check if the percentage of ES reaches 80 of AS to stop attack AS


	if ((percentage > 0 && percentage < 30))
		Npass = true;
	else
		Npass = false;

	int counter = 0;

	//Setting this unit as a fighting unit for the current timestep
	if (getCap() && (!AMEnemies->isEmpty() || (Npass && !ASEnemies->isEmpty())))
		game->setFightingUnit(this);
	
	while (counter < getCap() && (!AMEnemies->isEmpty() || (Npass && !ASEnemies->isEmpty())))
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

				//Adding enemy to attackedByET list
				game->addAttacked(this, enemy);

				enemy->decHealth(damageAM);

				enemy->setTa(game->getTimestep());  //set the first time unit got shot

				if (enemy->getHealth() <= 0) // ask the game to move it to the killed list
				{
					cout << "AMKilled\n";
					game->addToKilledList(enemy);
					 
					cout << "AM destroyed at " << enemy->getTd() << " " << game->getTimestep() << endl;
				}

				else
				{
					tempList.enqueue(enemy); // store at temp list
				}
				counter++;
			}
		}
		// attack alien soldier
		if (counter < getCap())
		{
			if (Npass) {
				if (ASEnemies->dequeue(enemy))
				{
					int damageAS = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

					//Adding enemy to attackedByET list
					game->addAttacked(this, enemy);

					enemy->decHealth(damageAS);

					enemy->setTa(game->getTimestep());  //set the first time unit got shot


					if (enemy->getHealth() <= 0) // ask the game to move it to the killed list
					{
						cout << "ASKilled\n";
						game->addToKilledList(enemy);
			
						cout << "AS destroyed at " << enemy->getTd() << " " << game->getTimestep() << endl;
					}
					else


					{
						tempList.enqueue(enemy); // store at temp list
					}

					counter++;
				}
			}

			if (!ASEnemies->isEmpty() && ((float((ESlist->getCount())) / (ASEnemies->getCount())) * 100 >= 80))
			{
				Npass = false;
			}

		}
	}
	while (tempList.dequeue(enemy))  //move all items from the temp list back to thier original list
	{
		if (dynamic_cast<AlienSoldier*>(enemy))
			ASEnemies->enqueue(enemy);
		else
			AMEnemies->insert(enemy);

	}
}
