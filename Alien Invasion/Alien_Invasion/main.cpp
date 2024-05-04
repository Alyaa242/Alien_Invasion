#include"Game.h"

int main() {

	Deque <int > d;
	d.addLast(6);

	d.print();
	int y;
	d.removeLast(y);
	d.print();
	d.enqueue(77);
	 d.print();
	d.addLast(0);
	d.print();
	d.dequeue(y);
	d.print();
	d.enqueue(9);
	d.print();
	return 0;
}
