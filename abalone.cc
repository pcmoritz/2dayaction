#include <iostream>
#include "field.hh"
#include <sstream>
#include "random_ki.hh"

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

class nick_ai_player {
	std::string player_name;
	// this function has to ensure that in "move", nothing like
	// {a = valid_move, b = invalid_move, c = valid_move} happens
public:
	nick_ai_player(std::string name) : player_name(name) { }
	move operator()(field& f) {
		
		move Test;
		while(is_equal(Test.a,not_a_position)){	
			Test = ki_do_move(f);
		}
		//print_move(Test);
		
		return Test;
	}
};



int main() {
	field f = start_field();
	//possible_moves(f, BLACK);
	/*print_field(f);
	InitRandom();
	move Test;
	while(is_equal(Test.a,not_a_position)){	
		Test = ki_do_move(f);
	}
	do_move(f,Test);
	//print_move(Test);
	print_field(f);*/
	InitRandom();
	
	//human_player player_one = human_player("Black");
	nick_ai_player player_one = nick_ai_player("BLACK");
	nick_ai_player player_two = nick_ai_player("White");

	int tmp;
	for(;;) {
		print_field(f);
		ki_color = BLACK;
		do_move(f, player_two(f));
		print_field(f);
		ki_color = WHITE;
		do_move(f, player_one(f));
		std::cin>>tmp;
	}
}
