#pragma once
#include <iostream>
#include "..//Game.h"
class Game;
class Unit
{
	int health, power, capacity;
	int ID;
	int Tj, Ta, Td;
	static int lastEarthID;
	static int lastAlienID;
	bool attacked;

protected:
	Game* game;
	int blah;

public:

	//We need to add game ptr to constructor
	Unit(int heal, int pow, int cap, int t, Game* g);	//Initializing basic members in constructor
	virtual void attack() = 0;

	//Getters to members:
	int getHealth() const;
	int getPower() const;
	int getCap() const;
	int getTj() const;
	int getTa() const;
	int getTd() const;
	int getID() const;
	bool isAttacked() const;
	
	void setAttacked(bool x);
	void setTa(int t);
	void setTd(int t);

	void setEarthID();		//A function that sets units IDs automatically
	void setAlienID();
	void decHealth(int damage);		//Decrement health
};

std::ostream& operator << (std::ostream& out, const Unit& u);	//Overloading operator <<

