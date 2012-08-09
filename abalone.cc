#include <iostream>
#include "field.hh"
#include <sstream>
#include <cstdio>
#include "alpha-beta-ki.hh"
#include <time.h>
#include "nick_ki.hh"
#include "misc.hh"

using namespace std;

// protocol for AI:

class human_player {
	std::string player_name;
	stone player;
	// this function has to ensure that in "move", nothing like
	// {a = valid_move, b = invalid_move, c = valid_move} happens
public:
	human_player(std::string name) : player_name(name), player(WHITE) { }
	move operator()(field& f) {
		std::cout << player_name +
			std::string(": Please specify your move ('n' for no move)!");
		return read_move();
	}
};

int main() {
	std::srand(time(NULL));
	field f = start_field();
	
	nick_player player_one("Black", BLACK,1,2,1);
	nick_player player_two("White", WHITE);
	
	move player_move;
	for(;;) {
		player_move = player_one(f);
		do_move(f,player_move);
		//print_field(f);
		//std::getchar();
		if(check_victory(f)) break;
	
		player_move = player_two(f);
		do_move(f,player_move);
		//print_field(f);
		//std::getchar();
		if(check_victory(f)) break;
	}
}
