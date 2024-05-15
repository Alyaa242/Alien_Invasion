#include "EarthSoldier.h"

int EarthSoldier::infectedCount = 0;
int EarthSoldier::totalInfected = 0;

EarthSoldier::EarthSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setEarthID();
	infected = false;
	immune = false;
}

void EarthSoldier::attack()
{
	LinkedQueue<Unit*>* ASenemies = game->getASEnemies(); // Ask the game to get the list of enemies this class should attack
	LinkedQueue<Unit*>* ESenemies = game->getESEnemies();
	LinkedQueue<Unit*> tempList;
	Unit* enemy;  
	bool attacking = false;

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

	for (int i = 0; i < capacity; i++)
	{
		// attack itself if the unit is infected
		if (infected)
		{
			if (ESenemies->dequeue(enemy))
			{
				// Assume infected units attacks only non-infected units
				if (dynamic_cast<EarthSoldier*>(enemy)->infected)
				{
					tempList.enqueue(enemy);
				}
				else
				{

					long double damage = (long double(power * getHealth()) / 100) / sqrt(enemy->getHealth());

					attacking = true;	//To print if it's shooting at this timestep

					//Adding enemy to attackedByES list
					game->addAttacked(this, enemy);

					//Decrement enemy's health:
					enemy->decHealth(damage);

					//Set Ta:
					enemy->setTa(game->getTimestep());

					//If it's killed, add to killed list:
					if (enemy->getHealth() <= 0) { 
						game->addToKilledList(enemy);
					 
					}
					//If it's injured, add to UML:
					else if (enemy->getHealth() <= 20)
						game->addToUML1(enemy);

					//Otherwise store in a temp list:
					else
					{
						tempList.enqueue(enemy);
					 
					}

				}
			}
			
		}
		 // if not infected ==> attack AS
		else if (ASenemies->dequeue(enemy)) // get a unit from that list and attack it
		{
			long double damage = (long double(power * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Adding enemy to attackedByES list
			game->addAttacked(this, enemy);
			
			attacking = true;

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

	//Setting this unit as a fighting unit for the current timestep
	if (attacking)
		game->setFightingUnit(this);

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
	if (x && !infected) {
		infected = true;
		infectedCount++;
		totalInfected++;
	}
	else if (!x) {
		infected = false;
		infectedCount--;
	}
}

bool EarthSoldier::isInfeced()
{
	return infected;
}

bool EarthSoldier::isImmune()
{
	return immune;
}

void EarthSoldier::decInfectedCount()
{
	infectedCount--;
}

int EarthSoldier::getInfectedCount()
{
	return infectedCount;
}

int EarthSoldier::getTotalInfected()
{
	return totalInfected;
}

void EarthSoldier::setImmuned(bool x)
{
	immune = x;
}

bool EarthSoldier::getInfected()
{
	return infected;

}
