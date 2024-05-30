#include "RandGen.h"
#include "Units/AlienDrone.h"
#include "Units/AlienMonster.h"
#include "Units/AlienSoldier.h"
#include "Units/EarthGunnery.h"
#include "Units/EarthSoldier.h"
#include "Units/EarthTank.h"
#include <cstdlib>

RandGen::RandGen(int* param, Game* g)
{
	parameters = param;
	game = g;
}

Unit* RandGen::CreateEarthUnit()
{
	int power = rand() % (parameters[upPowE] - parameters[lowPowE] + 1) + parameters[lowPowE];
	int health = rand() % (parameters[upHealE] - parameters[lowHealE] + 1) + parameters[lowHealE];
	int capacity = rand() % (parameters[upCapE] - parameters[lowCapE] + 1) + parameters[lowCapE];
	int B = rand() % 100 + 1;

	if (B <= parameters[ESPer]) {
			return new EarthSoldier( health, power, capacity, game->getTimestep());
	}
	else if (B <= parameters[ESPer] + parameters[ETPer]) {
		return new EarthTank( health, power, capacity, game->getTimestep());
	}
	else {
		return new EarthGunnery( health, power, capacity, game->getTimestep());
	}
}

Unit* RandGen::CreateAlienUnit()
{
	int power = rand() % (parameters[upPowA] - parameters[lowPowA] + 1) + parameters[lowPowA];
	int health = rand() % (parameters[upHealA] - parameters[lowHealA] + 1) + parameters[lowHealA];
	int capacity = rand() % (parameters[upCapA] - parameters[lowCapA] + 1) + parameters[lowCapA];
	int B = rand() % 100 + 1;

	if (B <= parameters[ASPer]) {
		return new AlienSoldier(health, power, capacity, game->getTimestep());
	}
	else if (B <= parameters[ASPer] + parameters[AMPer]) {
		return new AlienMonster(health, power, capacity, game->getTimestep());
	}
	else {
		return new AlienDrone(health, power, capacity, game->getTimestep());
	}
}

Unit** RandGen::GenerateEarthUnits()
{
	if (parameters) {
		Unit** arr = new Unit * [parameters[n]];
		for (int i = 0; i < parameters[n]; i++)
			arr[i] = nullptr;

		int A = rand() % 100 + 1;
		if (A <= parameters[prob]) {
			for (int i = 0; i < parameters[n]; i++) {
				arr[i] = CreateEarthUnit();
			}
		}
		return arr;
	}

	return nullptr;
}

Unit** RandGen::GenerateAlienUnits()
{
	if (parameters) {
		Unit** arr = new Unit * [parameters[n]];

		for (int i = 0; i < parameters[n]; i++)
			arr[i] = nullptr;

		int A = rand() % 100 + 1;
		if (A <= parameters[prob]) {
			for (int i = 0; i < parameters[n]; i++) {
				arr[i] = CreateAlienUnit();
			}
		}
		return arr;
	}

	return nullptr;
}

RandGen::~RandGen()
{
	delete parameters;
}
