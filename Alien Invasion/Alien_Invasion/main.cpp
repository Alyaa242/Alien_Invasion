#include"Game.h"

int main() {
	Game* game = new Game();
	//game->start();
	Deque <int > d;
	d.enqueue(5);
	d.enqueue(6);

	d.print();
	int y;
	d.dequeue(y);
	d.dequeue(y);
	d.print();
	d.enqueue(5);
	d.enqueue(6);

	d.print();
	delete game;

	return 0;
}
