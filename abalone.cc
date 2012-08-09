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
	std::cout << std::endl;
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

// protocol for AI:

class human_player {
	std::string player_name;
	// this function has to ensure that in "move", nothing like
	// {a = valid_move, b = invalid_move, c = valid_move} happens
public:
	human_player(std::string name) : player_name(name) { }
	move operator()(field& f) {
		std::cout << player_name +
			std::string(": Please specify your move ('n' for no move)!");
		return read_move();
	}
};



int main() {
	field f = start_field();
	
	human_player player_one = human_player("Black");
	human_player player_two = human_player("White");

	for(;;) {
		print_field(f);
		do_move(f, player_one(f));
		print_field(f);
		do_move(f, player_two(f));
	}
	
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
	// field f = start_field();
	// possible_moves(f, BLACK);
}
