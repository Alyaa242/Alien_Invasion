#include "HealUnit.h"

void HealUnit::attack()
{
	/*int =h;
	h += (getHealth() * getCap() / 100) / sqrt(h);*/

}


HealUnit::HealUnit(int heal, int pow, int cap, int t) :  Unit(heal, pow, cap, t) 
{
	setEarthID();
}
