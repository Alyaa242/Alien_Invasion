#include "AlienMonster.h"
#include "EarthSoldier.h"
#include "EarthTank.h"

AlienMonster::AlienMonster(int heal, int pow, int cap, int t, Game* g, int p) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
	prob = p;
}

void AlienMonster::attack()
{

	ArrayStack<Unit*>* ETEnemies = game->getETEnemies();
	LinkedQueue<Unit*>* ESEnemies = game->getESEnemies();
	Unit* enemy;
	LinkedQueue<Unit*> temp;
	
	//Setting this unit as a fighting unit for the current timestep
	if (getCap() && (!ETEnemies->isEmpty() || !ESEnemies->isEmpty()))
		game->setFightingUnit(this);
	
	int i = 0;
	while(i < getCap() && (!ETEnemies->isEmpty() || !ESEnemies->isEmpty())) {

		//Check there is an enemy in the list:
		if (ETEnemies->pop(enemy)) {

			//Adding enemy to attackedByAM list
			game->addAttacked(this, enemy);

			int damage = (float(getPower() * getHealth()) / 100) / sqrt(enemy->getHealth());

			//Decrement enemy's health:
			enemy->decHealth(damage);

			//Set Ta:
			enemy->setTa(game->getTimestep());

			//If it's killed, add to killed list:
			if (enemy->getHealth() <= 0) {
				cout << "ETKilled\n";
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
		if (i < getCap()) {
			if (ESEnemies->dequeue(enemy)) {

				//Adding enemy to attackedByAM list
				game->addAttacked(this, enemy);

				//Infect ES by probability prob
				int x = rand() % 100 + 1;

				if (x <= prob && !(dynamic_cast<EarthSoldier*>(enemy)->isImmune())) {
					dynamic_cast<EarthSoldier*>(enemy)->setInfected(true);
					cout << "ES ==> infected\n";
				}

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

				i++;
			}
		}
	}

	//Add enemies back to their original lists:
	while (temp.dequeue(enemy)) {
		if (dynamic_cast<EarthSoldier*>(enemy))
			ESEnemies->enqueue(enemy);
		else
			ETEnemies->push(enemy);
	}
}
