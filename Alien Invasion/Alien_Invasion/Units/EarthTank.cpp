#include "EarthTank.h"

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
	Unit* attackAS;
	Unit* attackAM;
	bool Npass = true; // check if the percentage of ES reaches 80 of AS to stop attack AS
	LinkedQueue<Unit*> tempListAS;
	LinkedQueue<Unit*> tempListAM;
	int counter = 0;
	float percentage = ((float((ASEnemies->getCount()) - (ESlist->getCount()))) / (ASEnemies->getCount())) * 100;
	while (counter < getCap() && (AMEnemies->getCount() != 0 || (percentage > 0 && percentage < 30)))
	{
		// attack monster
		int count = AMEnemies->getCount();
		int index;
		if (count != 0)
		{
			index = rand() % count;
			if (AMEnemies->remove(index, attackAM))
			{
				int damageAM = (float(getPower() * getHealth()) / 100) / sqrt(attackAM->getHealth());

				attackAM->decHealth(damageAM);

				if (!attackAM->isAttacked())
				{
					attackAM->setAttacked(true);
					attackAM->setTa(game->getTimestep());  //set the first time unit got shot
					attackAM->setDf(attackAM->getTa() - attackAM->getTj());
				}

				if (attackAM->getHealth() <= 0) // ask the game to move it to the killed list
				{
					game->addToKilledList(attackAM);
					attackAM->setTd(game->getTimestep());
					attackAM->setDd(attackAM->getTd() - attackAM->getTa());
					attackAM->setDb(attackAM->getTd() - attackAM->getTj());
				}
				else
				{
					tempListAM.enqueue(attackAM); // store at temp list
				}
				counter++;
			}
		}
		// attack alien soldier
		if (!ASEnemies->isEmpty())
		{
			percentage = ((float((ASEnemies->getCount()) - (ESlist->getCount()))) / (ASEnemies->getCount())) * 100;
			if (percentage > 0 && percentage < 30 && Npass && counter < getCap())
			{
				if (ASEnemies->dequeue(attackAS))
				{
					int damageAS = (float(getPower() * getHealth()) / 100) / sqrt(attackAS->getHealth());

					attackAS->decHealth(damageAS);

					if (!attackAS->isAttacked())
					{
						attackAS->setAttacked(true);
						attackAS->setTa(game->getTimestep());  //set the first time unit got shot
						attackAS->setDf(attackAS->getTa() - attackAS->getTj());
					}

					if (attackAS->getHealth() <= 0) // ask the game to move it to the killed list
					{
						game->addToKilledList(attackAS);
						attackAS->setTd(game->getTimestep());
						attackAS->setDd(attackAS->getTd() - attackAS->getTa());
						attackAS->setDb(attackAS->getTd() - attackAS->getTj());
					}
					else
					{
						tempListAS.enqueue(attackAS); // store at temp list
					}

					counter++;
				}

			}
			if (!ESlist->isEmpty() && (((float((ESlist->getCount()) - (ASEnemies->getCount()))) / (ESlist->getCount())) * 100 >= 80))
			{
				Npass = false;
			}

		}
		if (counter == 0)
			break;
	}
	while (tempListAS.dequeue(attackAS))  //move all items from the temp list back to thier original list
	{
		ASEnemies->enqueue(attackAS);
	}
	while (tempListAM.dequeue(attackAM))  //move all items from the temp list back to thier original list
	{
		AMEnemies->insert(attackAM);
	}

}

