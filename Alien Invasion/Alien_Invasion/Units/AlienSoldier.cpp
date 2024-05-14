#include "AlienSoldier.h"
#include"EarthSoldier.h"

AlienSoldier::AlienSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienSoldier::attack()
{
	LinkedQueue<Unit*>* ESEnemies = game->getESEnemies();
	LinkedQueue<Unit*>* SUEnemies = game->getSUEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> temp;

	//Setting this unit as a fighting unit for the current timestep
	if(capacity && !ESEnemies->isEmpty())
		game->setFightingUnit(this);

	int i = 0;
	while (i < capacity && (!ESEnemies->isEmpty() || !SUEnemies->isEmpty())) {

		//Check there is an enemy in the list:
		if (ESEnemies->dequeue(enemy)) {

			//Adding enemy to attackedByAS list
			game->addAttacked(this, enemy);

			float damage = (float(power * getHealth()) / 100) / sqrt(enemy->getHealth());

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
				temp.enqueue(enemy);
		}

		//Check there is an enemy in the list:

		if (i < capacity && SUEnemies->dequeue(enemy)) {
			
			//Adding enemy to attackedByAM list
			game->addAttacked(this, enemy);

			float damage = (float(power * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Decrement enemy's health:
			enemy->decHealth(damage);

			//Set Ta:
			enemy->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				game->addToKilledList(enemy);
			}

			//Otherwise store in a temp list:
			else
				temp.enqueue(enemy);

			i++;
		}
	}

	//Add enemies back to their original lists:
	while (temp.dequeue(enemy)) {
		if (dynamic_cast<EarthSoldier*>(enemy))
			ESEnemies->enqueue(enemy);
		else
			SUEnemies->enqueue(enemy);
	}
}
