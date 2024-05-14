#include "AlienDrone.h"
#include "EarthGunnery.h"
#include "EarthTank.h"

AlienDrone::AlienDrone(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
	isSecond = false;
}

void AlienDrone::attack()
{
	ArrayStack<Unit*>* ETEnemies = game->getETEnemies();
	priQueue<Unit*>* EGEnemies = game->getEGEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> temp;
	int dummy;	//Dummy int to take pri value

	//Setting this unit as a fighting unit for the current timestep
	if (capacity && (!ETEnemies->isEmpty() || !EGEnemies->isEmpty())) {
		if (isSecond)
			game->setFightingUnit(this, 2);
		else
			game->setFightingUnit(this);
	}
	

	int i = 0;
	while (i < capacity && (!ETEnemies->isEmpty() || !EGEnemies->isEmpty())) {

		//Check there is an enemy in the list:
		if (ETEnemies->pop(enemy)) {

			//Adding enemy to attackedByAD list
			if (isSecond)
				game->addAttacked(this, enemy, 2);
			else
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
				game->addToUML2(enemy);

			//Otherwise store in a temp list:
			else
				temp.enqueue(enemy);

			i++;
		}

		//Check there is an enemy in the list:
		if (i < capacity) {
			if (EGEnemies->dequeue(enemy, dummy)) {

				//Adding enemy to attackedByAD list
				if (isSecond)
					game->addAttacked(this, enemy, 2);
				else
					game->addAttacked(this, enemy);

				if (game->getTimestep() == 700)
					int x = 0;
				
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
	}

	//Add enemies back to their original lists:
	while (temp.dequeue(enemy)) {
		if (dynamic_cast<EarthGunnery*>(enemy))
			EGEnemies->enqueue(enemy, enemy->getHealth() + enemy->getPower());
		else
			ETEnemies->push(enemy);
	}
}

void AlienDrone::setIsSecond(bool x)
{
	isSecond = x;
}
