#include "EarthTank.h"
#include "AlienSoldier.h"
EarthTank::EarthTank(int heal, int pow, int cap, int t, Game* g) : Unit(heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthTank::attack()
{
	// attack AS if the count of ES less than AS with 30% until ES reaches 80% of AS then back to attack AM randomly
	LinkedQueue<Unit*>* ASEnemies = game->getASEnemies();
	LinkedQueue<Unit*>* ESlist = game->getESEnemies();
	Array<Unit*>* AMEnemies = game->getAMEnemies();
	Unit* enemy;
	float percentage = (ASEnemies->getCount() != 0) ? ((float((ASEnemies->getCount()) - (ESlist->getCount()))) / (ASEnemies->getCount())) * 100 : INT_MIN;
	bool Npass; // check if the percentage of ES reaches 80 of AS to stop attack AS
	LinkedQueue<Unit*> tempList;
	int counter = 0;

	if ((percentage > 0 && percentage < 30))
		Npass = true;
	else
		Npass = false;

	while (counter < getCap() && (AMEnemies->getCount() != 0 || Npass))
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

				if (!enemy->isAttacked())
				{
					enemy->setAttacked(true);
					enemy->setTa(game->getTimestep());  //set the first time unit got shot
					enemy->setDf(enemy->getTa() - enemy->getTj());
				}

				if (enemy->getHealth() <= 0) // ask the game to move it to the killed list
				{
					game->addToKilledList(enemy);
					enemy->setTd(game->getTimestep());
					enemy->setDd(enemy->getTd() - enemy->getTa());
					enemy->setDb(enemy->getTd() - enemy->getTj());
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

			if (ASEnemies->dequeue(enemy) && Npass)
			{
				int damageAS = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

				enemy->decHealth(damageAS);

				if (!enemy->isAttacked())
				{
					enemy->setAttacked(true);
					enemy->setTa(game->getTimestep());  //set the first time unit got shot
					enemy->setDf(enemy->getTa() - enemy->getTj());
				}

				if (enemy->getHealth() <= 0) // ask the game to move it to the killed list
				{
					game->addToKilledList(enemy);
					enemy->setTd(game->getTimestep());
					enemy->setDd(enemy->getTd() - enemy->getTa());
					enemy->setDb(enemy->getTd() - enemy->getTj());
				}
				else
				{
					tempList.enqueue(enemy); // store at temp list
				}

				counter++;
			}

			if (!ESlist->isEmpty() && (((float((ESlist->getCount()) - (ASEnemies->getCount()))) / (ESlist->getCount())) * 100 >= 80))
			{
				Npass = false;
			}

			if (counter == 0)
				break;
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

