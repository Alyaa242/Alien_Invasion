#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int heal, int pow, int cap, int t, Game* g) : Unit( heal, pow, cap, t, g)
{
	setAlienID();
}

void AlienSoldier::attack()
{
	LinkedQueue<Unit*>* ESEnemies;

	/*game->getESList();
	LinkedQueue<Unit*>* ESEnemies;
	LinkedQueue<Unit*> temp;
	Unit* enemy;
	for (int i = 0; i < getCap(); i++) {

		int damage;

		if (ESEnemies->dequeue(enemy)) {
			enemy->decHealth(damage);
			
			if (enemy->getHealth() <= 0)
				//game->addToKilled(enemy);

			else if (enemy->getHealth() <= 20)
				game->addToUML(enemy);

			else
				temp.enque(enemy);
			
	
		}
		

	}*/
}
