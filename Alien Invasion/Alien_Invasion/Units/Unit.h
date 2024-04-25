#pragma once
#include <iostream>
#include "..//Game.h"
class Game;
class Unit
{
	Game* game; 
	int health, power, capacity;
	int Tj, Ta, Td;
	int ID;
	static int lastEarthID;
	static int lastAlienID;
public:

	//We need to add game ptr to constructor
	Unit(int heal, int pow, int cap, int t);	//Initializing basic members in constructor
	virtual void attack() = 0;

	//Getters to members:
	int getHealth() const;
	int getPower() const;
	int getCap() const;
	int getTj() const;
	int getTa() const;
	int getTd() const;
	int getID() const;

	void setEarthID();		//A function that sets units IDs automatically
	void setAlienID();
	int decHealth(int damage);		//Decrement health
};

std::ostream& operator << (std::ostream& out, const Unit& u);	//Overloading operator <<

