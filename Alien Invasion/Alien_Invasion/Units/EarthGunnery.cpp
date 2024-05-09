#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthGunnery::attack()
{
	Deque<Unit*>* ADEnemies = game->getADEnemies();
	Array<Unit*>* AMEnemies = game->getAMEnemies();
	Unit* attackADFront = nullptr;
	Unit* attackADBack = nullptr;
	Unit* attackAM = nullptr;
	LinkedQueue<Unit*> tempListAD;
	LinkedQueue<Unit*> tempListAM;
	int counter = 0;

	//Setting this unit as a fighting unit for the current timestep
	game->setFightingUnit(this);

	while (counter < getCap() && (!ADEnemies->isEmpty() || AMEnemies->getCount() != 0))
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

		/// attack drones
		if (counter < getCap())
		{
			if (ADEnemies->getCount() == 1 || (getCap() - counter == 1))  // if one drone exist
			{
				if (ADEnemies->dequeue(attackADFront))
				{
					int damageAD = (float(getPower() * getHealth()) / 100) / sqrt(attackADFront->getHealth());
					attackADFront->decHealth(damageAD);
				
					//Set Ta:
					attackADFront->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (attackADFront->getHealth() <= 0) {
						game->addToKilledList(attackADFront);
						attackADFront->setTd(game->getTimestep());
					}
					else
					{
						tempListAD.enqueue(attackADFront); // store at temp list
					}
					counter++;
				}
			}
			else
			{
				if (ADEnemies->dequeue(attackADFront) && ADEnemies->removeLast(attackADBack) && ((getCap() - counter) >= 2))
				{
					int damageADFront = (float(getPower() * getHealth()) / 100) / sqrt(attackADFront->getHealth());
					attackADFront->decHealth(damageADFront);

					int damageADBack = (float(getPower() * getHealth()) / 100) / sqrt(attackADBack->getHealth());
					attackADBack->decHealth(damageADBack);

					//Set Ta:
					attackADFront->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (attackADFront->getHealth() <= 0) {
						game->addToKilledList(attackADFront);
						attackADFront->setTd(game->getTimestep());
					}

					else
					{
						tempListAD.enqueue(attackADFront); // store at temp list
					}
					//Set Ta:
					attackADBack->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (attackADBack->getHealth() <= 0) {
						game->addToKilledList(attackADBack);
						attackADBack->setTd(game->getTimestep());
					}

					else
					{
						tempListAD.enqueue(attackADBack); // store at temp list
					}
					counter += 2;
				}
			}
		}

	}
	while (tempListAM.dequeue(attackAM))  //move all items from the temp list back to thier original list
	{
		AMEnemies->insert(attackAM);
	}
	int i = 0;
	while (tempListAD.dequeue(attackADFront))  //move all items from the temp list back to thier original list
	{
		if (i % 2 == 0)
			ADEnemies->enqueue(attackADFront);
		else
			ADEnemies->addLast(attackADFront);
		i++;
	}

}

