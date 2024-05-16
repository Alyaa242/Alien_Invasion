#include "HealUnit.h"
#include "EarthSoldier.h"
int HealUnit::HealedCounter = 0;
void HealUnit::attack()
{
	Unit* unit;
	int max_health;
	long double h;
	LinkedQueue <Unit*> tempList1;
	LinkedQueue <Unit*> tempList2;
	

	game->UpdateUML();
	
	int i = 0;
	for (; i < capacity; i++)
	{
		Unit* healed1 = game->pickfromUML1();
		if (healed1)
		{

			h = (long double((getPower()) * (getHealth()))) / 100 / sqrt(healed1->getHealth());

			if (dynamic_cast <EarthSoldier*> (healed1)->getInfected())
			{
				healed1->incHealth(h / 2); HealedCounter++; // heal the infected ones in double the time
			}
			else
			{
				healed1->incHealth(h); HealedCounter++;
			}


			if (healed1)
				if (healed1->getHealth() <= 20) // if health after incrementation exceeds 20 return it to the battle
					tempList1.enqueue(healed1);
				else
				{

					dynamic_cast <EarthSoldier*> (healed1)->setImmuned(true);
					dynamic_cast <EarthSoldier*> (healed1)->setInfected(false);
					cout << "\n addedddddds" << healed1;
					game->addES(healed1);
				}
			
		}
	}

	for (int j = i; j < capacity; j++)
	{
		Unit* healed2 = game->pickfromUML2();
		if (healed2)
		{

			h = (long double((getPower()) * (getHealth()) / 100)) / sqrt(healed2->getHealth());
			healed2->incHealth(h);

			if (healed2)

				if (healed2->getHealth() <= 20)

					tempList2.enqueue(healed2);
				else
					game->addET(healed2);

		}
	}

	
		
		while (!tempList1.isEmpty())  //Return from templists
		{
			if (tempList1.dequeue(unit))
				game->addToUML1(unit);
		}
		Unit* unit2;
		while (!tempList2.isEmpty())
		{
			if (tempList2.dequeue(unit2))
				game->addToUML2(unit2);

		}

	if (game->RemoveHU()) //Kill the Heal Unit 
	{
		game->addToKilledList(this);

	}
}


HealUnit::HealUnit(int heal, int pow, int cap, int t, Game* g) :  Unit(heal, pow, cap, t, g) 
{
	setEarthID();
}
 

int HealUnit::getHealedCounter()
{
	return HealedCounter;
}

