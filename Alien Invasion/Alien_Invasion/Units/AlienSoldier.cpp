#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienSoldier::attack()
{
	LinkedQueue<Unit*>* ESEnemies = game->getESEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> temp;

	//Setting this unit as a fighting unit for the current timestep
	if(getCap() && !ESEnemies->isEmpty())
		game->setFightingUnit(this);

	for (int i = 0; i < getCap(); i++) {

		//Check there is an enemy in the list:
		if (ESEnemies->dequeue(enemy)) {

			//Adding enemy to attackedByAS list
			game->addAttacked(this, enemy);

			int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Decrement enemy's health:
			enemy->decHealth(damage);

			//Set Ta:
			enemy->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				cout << "ESKilled\n";
				game->addToKilledList(enemy);
				enemy->setTd(game->getTimestep());
			}

			//If it's injured, add to UML:
			else if (enemy->getHealth() <= 20)
				game->addToUML1(enemy);

			//Otherwise store in a temp list:
			else
				temp.enqueue(enemy);
		}
		else
			break;
	}

	//Add enemies back to their original lists:
	while (temp.dequeue(enemy)) {
		ESEnemies->enqueue(enemy);
	}
}
