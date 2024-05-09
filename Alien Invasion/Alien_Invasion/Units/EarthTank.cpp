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

	//Setting this unit as a fighting unit for the current timestep
	game->setFightingUnit(this);

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

				//Set Ta:
				attackAM->setTa(game->getTimestep());

				//If it's killed, add to killed list:
				if (attackAM->getHealth() <= 0) {
					game->addToKilledList(attackAM);
					attackAM->setTd(game->getTimestep());
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

					//Set Ta:
					attackAS->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (attackAS->getHealth() <= 0) {
						game->addToKilledList(attackAS);
						attackAS->setTd(game->getTimestep());
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

