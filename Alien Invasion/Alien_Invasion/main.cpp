#include"Game.h"
#include "DS/PriQueue.h"

int main() {

	Game* g=new Game;
	g->chooseMode();
	g->start();

	//g->Display();
	return 0;
}
