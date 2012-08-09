#include <iostream>
#include "field.hh"
#include <sstream>
#include <cstdio>
#include "alpha-beta-ki.hh"
#include <time.h>

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
	
	alpha_beta_player player_one = alpha_beta_player("Black", BLACK);
	alpha_beta_player player_two = alpha_beta_player("White", WHITE);
	move player_move;
	for(;;) {
		//print_field(f);
		player_move = player_one(f);
		//print_field(f);
		//print_move(player_move);
		//do_move(f,player_move);
    //if(move_valid(player_move,f)){
			do_move(f,player_move);	
		//}else{
			//std::cout<<"Black cheated"<<std::endl;
			//print_field(f);
			//print_move(player_move);
			//std::getchar();
		//}
		if(check_victory(f)) break;
		//print_field(f);
		//std::getchar();
		//print_field(f);
		player_move = player_two(f);
		//if(move_valid(player_move,f)){
			do_move(f,player_move);
		//}else{
	//		std::cout<<"White cheated"<<std::endl;
	//		print_field(f);
	//		print_move(player_move);
	//		std::getchar();	
	//	}
		if(check_victory(f)) break;
		//std::getchar();
	}
}
