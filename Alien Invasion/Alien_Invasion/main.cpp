#include"Game.h"

int main() {
	Game* g=new Game;
	Deque <int> *d= new Deque <int>;
	d->enqueue(1);
	d->enqueue(2);
	d->print();
	int u;
    d->dequeue(u);
	d->removeLast(u);
	d->print();
	d->enqueue(1);
	d->enqueue(2);
	d->print();
	
	cout << u;
	return 0;
}
