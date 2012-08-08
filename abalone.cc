#include <iostream>
#include "field.hh"

using namespace std;

pos read_position() {
	int p;
	cin >> p;
	pos position;
	position.a = p/10;
	position.b = p%10;
	return position;
}

move read_move() {
	cout << "first stone: ";
	pos a = read_position();
	cout << endl;
	cout << "second stone: ";
	pos b = read_position();
	cout << endl;
	cout << "third stone: ";
	pos c = read_position();
	cout << endl;
	cout << "direction (right 0, left 3, etc.): ";
	int dir = 0;
	cin >> dir;
	move m;
	m.a = a;
	m.b = b;
	m.c = c;
	m.dir = dir;
	return m;
}

void print_position(pos p) {
	cout << p.a << " " << p.b << endl;
}



int main() {
	field f = start_field();
	for(;;) {
		for(int i = 0; i < 2; ++i) {
			cout << (i ? "Black" : "White");
			cout << ": Please specify your move!" << endl;
			pos p = read_position();
			print_field(f);
		}
	}
}
