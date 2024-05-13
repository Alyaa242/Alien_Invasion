#include "HealUnit.h"
#include "EarthSoldier.h"
int HealUnit::HealedCounter = 0;
void HealUnit::attack()
{

	Unit* unit;
	int max_health;
	int h;

	LinkedQueue <Unit*> tempList1;
	LinkedQueue <Unit*> tempList2;
	Unit* picked;
	game->UpdateUML();
	picked = game->PickHU();
	if (!picked)
		return;
	int healcap = picked->getCap();




	int i = 0;
	for (; i < healcap; i++)
	{
		Unit* healed1 = game->pickfromUML1();
		if (healed1)
		{

	    	h = (float((getPower()) * (getHealth()))) / 100 / sqrt(healed1->getHealth());

			if (dynamic_cast <EarthSoldier*> (healed1)->getInfected())
			{
				
				healed1->incHealth(h / 2); HealedCounter++;
			

			}
			else
			
			{
				
				healed1->incHealth(h); HealedCounter++;

			}


			if (healed1)

				if (healed1->getHealth() <= 20)

					tempList1.enqueue(healed1);
				else
				{
					dynamic_cast <EarthSoldier*> (healed1)->setImmuned(true);
					game->addES(healed1);
				}
		}
	}
	for (int j = i; j < healcap; j++)
	{
		Unit* healed2 = game->pickfromUML2();
		if (healed2)

		{
			{
				h = (float((getPower()) * (getHealth()) / 100)) / sqrt(healed2->getHealth());
				healed2->incHealth(h);
			}


			if (healed2)

				if (healed2->getHealth() <= 20)

					tempList2.enqueue(healed2);
				else
					game->addET(healed2);

		}
	}


	{
		//cout << "lllllllllllllllllllllllll\n";


		while (!tempList1.isEmpty())
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
	}




	if (game->RemoveHU())
	{
		game->addToKilledList(picked);

	}

}


HealUnit::HealUnit(int heal, int pow, int cap, int t, Game* g) :  Unit(heal, pow, cap, t, g) 
{
	setEarthID();
}

void HealUnit::UpdateHU()
{
	//if (getTj() +10 < game->getTimestep())
	//	game->addToKilledList(this);
}

int HealUnit::getHealedCounter()
{
	return HealedCounter;
}

