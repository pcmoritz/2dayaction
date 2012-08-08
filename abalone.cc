#include <iostream>
#include "field.hh"

using namespace std;

struct pos {
	int a, b;
};

pos read_position() {
	int p;
	cin >> p;
	pos position;
	position.a = p/10;
	position.b = p%10;
	return position;
}

void print_position(pos p) {
	cout << p.a << " " << p.b << endl;
}

int main() {
	for (;;) {
		cout << "Please specify your move!" << endl;
		pos p = read_position();
		print_position(p);
	}
}
