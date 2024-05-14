#pragma once
#include <iostream>
#include "..//Game.h"
class Game;
class Unit
{
	float health, power, capacity;
	int ID;
	
	int wait;

	int Tj, Ta, Td , Dd , Db , Df;

	static int lastEarthID;
	static int lastAlienID;
	static int lastAllyID;
	bool attacked;

protected:
	Game* game;

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
	int getDd() const;
	int getDb() const;
	int getDf() const;

	bool isAttacked() const;
	void setAttacked(bool x);
	void setTa(int t);
	void setTd(int t);
	void setDd(int t);
	void setDb(int t);
	void setDf(int t);

	void setEarthID();		//A function that sets units IDs automatically
	void setAlienID();
	void setAllyID();
	void decHealth(float damage);		//Decrement health
	void incHealth(float increment);		//increment health
	int getWait();
	void setWait(int w);

	static int getLastEarthID();
	static int getLastAlienID();

};

std::ostream& operator << (std::ostream& out, Unit* u);	//Overloading operator <<

