#include"Game.h"
 

int main() {

	Game* g=new Game;

	g->chooseMode();

	g->start();
	 
	delete g;
 
	return 0;
}
