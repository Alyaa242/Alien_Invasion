#include"Game.h"
#include "DS/PriQueue.h"

int main() {
	Game* game = new Game();
	game->start();
	
	delete game;

	return 0;
}
