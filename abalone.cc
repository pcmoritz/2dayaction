#include <iostream>
#include "field.hh"
#include <sstream>

using namespace std;

int string_to_number(std::string str) {
	int num;
	istringstream convert(str);
	convert >> num;
	return num;
}

pos read_position() {
	std::string str;
	cin >> str;
	if(str == std::string("n"))
		return not_a_position;
	int p = string_to_number(str);
	pos position;
	position.a = p/10;
	position.b = p%10;
	return position;
}

move read_move() {
	cout << "first stone: ";
	pos a = read_position();
	cout << "second stone: ";
	pos b = read_position();
	cout << "third stone: ";
	pos c = read_position();
	cout << "direction (right 1, left 4, etc.): ";
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
	// field f = start_field();
	// for(;;) {
	// 	for(int i = 0; i < 2; ++i) {
	// 		print_field(f);
	// 		cout << (i ? "White" : "Black");
	// 		cout << ": Please specify your move ('n' for no move)!" << endl;
	// 		move m = read_move();
	// 		do_move(f, m);
	// 	}
	// }
	field f = test_field();
	possible_moves(f, BLACK);
}
