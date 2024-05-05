#include "AlienDrone.h"
#include "EarthGunnery.h"
#include "EarthTank.h"

AlienDrone::AlienDrone(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienDrone::attack()
{
	ArrayStack<Unit*>* ETEnemies = game->getETEnemies();
	priQueue<Unit*>* EGEnemies = game->getEGEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> temp;
	int dummy;	//Dummy int to take pri value

	int i = 0;
	while (i < getCap() && !(ETEnemies->isEmpty() || EGEnemies->isEmpty())) {

		//Check there is an enemy in the list:
		if (ETEnemies->pop(enemy)) {

			int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Decrement enemy's health:
			enemy->decHealth(damage);

			//Check if it's not attacked before to set Ta:
			if (!enemy->isAttacked()) {
				enemy->setAttacked(true);
				enemy->setTa(game->getTimestep());
			}

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				game->addToKilledList(enemy);
				enemy->setTd(game->getTimestep());
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
		if (EGEnemies->dequeue(enemy, dummy) && i < getCap()) {

			int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Decrement enemy's health:
			enemy->decHealth(damage);

			//Check if it's not attacked before to set Ta:
			if (!enemy->isAttacked()) {
				enemy->setAttacked(true);
				enemy->setTa(game->getTimestep());
			}

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				game->addToKilledList(enemy);
				enemy->setTd(game->getTimestep());
			}

			//Otherwise store in a temp list:
			else
				temp.enqueue(enemy);

			i++;
		}
	}

	//Add enemies back to their original lists:
	while (temp.dequeue(enemy)) {
		if (dynamic_cast<EarthGunnery*>(enemy))
			EGEnemies->enqueue(enemy, dummy);
		else
			ETEnemies->push(enemy);
	}


}
