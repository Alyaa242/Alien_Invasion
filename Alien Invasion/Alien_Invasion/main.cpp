#include"Game.h"
#include "DS/PriQueue.h"

int main() {

	Game* g=new Game;
	//Deque <int> *d= new Deque <int>;
	//g->chooseMode();

	g->start();

	g->Display();
	return 0;
}
