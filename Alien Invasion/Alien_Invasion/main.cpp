#include"Game.h"
 

int main() {

	Game* g=new Game;

	g->chooseMode();

	g->start();
	g->Display();
	delete g;
 
	return 0;
}
