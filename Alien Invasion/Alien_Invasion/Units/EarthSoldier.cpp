#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
}

void EarthSoldier::attack()
{
	LinkedQueue<Unit*>* ASenemies = game->getASEnemies(); // Ask the game to get the list of enemies this class should attack
	LinkedQueue<Unit*>* ESenemies = game->getESEnemies();
	LinkedQueue<Unit*> tempList;
	Unit* enemy;  

	//Setting this unit as a fighting unit for the current timestep
	if(getCap() && !ASenemies->isEmpty())
	game->setFightingUnit(this);

	//Infect another ES if infected
	if (infected) {
		int x = rand() % 100 + 1;
		//Check for probability
		if (x <= 2) {
			//Get random ES
			int index = rand() % ESenemies->getCount();
			Unit* temp;
			for (int i = 0; i < ESenemies->getCount(); i++) {
				ESenemies->dequeue(temp);
				if(i == index && !(dynamic_cast<EarthSoldier*>(temp)->immune))
					dynamic_cast<EarthSoldier*>(temp)->setInfected(true);
				ESenemies->enqueue(temp);
			}
		}
	}

	for (int i = 0; i < getCap(); i++)
	{
		// attack itself if the unit is infected
		if (infected)
		{
			if (ESenemies->dequeue(enemy))
			{
				// Assume infected units attacks only non-infected units
				if (dynamic_cast<EarthSoldier*>(enemy)->infected)
				{
					cout << "Add Infected to temp list\n";
					tempList.enqueue(enemy);
				}
				else
				{

					int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

					//Adding enemy to attackedByES list
					game->addAttacked(this, enemy);

					//Decrement enemy's health:
					enemy->decHealth(damage);

					//Set Ta:
					enemy->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (enemy->getHealth() <= 0) {
						cout << "ESKilled infected\n";
						game->addToKilledList(enemy);
						enemy->setTd(game->getTimestep());
					}
					//If it's injured, add to UML:
					else if (enemy->getHealth() <= 20)
						game->addToUML1(enemy);

					//Otherwise store in a temp list:
					else
					{
						tempList.enqueue(enemy);
						cout << "tempES\n";
					}

				}
			}
			
		}
		 // if not infected ==> attack AS
		else if (ASenemies->dequeue(enemy)) // get a unit from that list and attack it
		{
			//Adding enemy to attackedByAS list
			game->addAttacked(this, enemy);

			int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Adding enemy to attackedByES list
			game->addAttacked(this, enemy);

			enemy->decHealth(damage);

			//Set Ta:
			enemy->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				cout << "ASKilled\n";
				game->addToKilledList(enemy);
				enemy->setTd(game->getTimestep());
			}
			else
			{
				tempList.enqueue(enemy); // store at temp list
			}

		}

	}

	while (tempList.dequeue(enemy))  //move all items from the temp list back to thier original list
	{
		if (dynamic_cast<EarthSoldier*>(enemy))
			ESenemies->enqueue(enemy);
		else
			ASenemies->enqueue(enemy);
	}




}

void EarthSoldier::setInfected(bool x)
{
	infected = x;
}

bool EarthSoldier::isInfeced()
{
	return infected;
}

bool EarthSoldier::isImmune()
{
	return immune;
}
