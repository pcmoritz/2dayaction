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
struct game_stats {
	stone winning_color;
	int moves;
};

template <class player_one,class player_two>
game_stats play_game(field Field,player_one p1,player_two p2) {
	move player_move;
	int moves=0;
	while(!check_victory(Field)) {
		player_move =p1(Field);
		do_move(Field,player_move);
		print_field(Field);
		moves+=1;
		if(check_victory(Field)) {
			game_stats ret;
			ret.moves = moves;
			ret.winning_color = check_victory(Field);		
		return ret;
		}
		player_move =p2(Field);
		do_move(Field,player_move);
		print_field(Field);
	}
	game_stats ret;
	ret.moves = moves;
	ret.winning_color = check_victory(Field);
	return ret;
}

template <class player_one,class player_two>
void func(field Field,player_one p1,player_two p2) {
	//player_move = Method(Field);
	game_stats tmp= play_game(Field,p1,p2);
	
	std::cout<<tmp.winning_color<<"\t"<<tmp.moves<<std::endl;
}
	

int main() {
	std::srand(time(NULL));
	field f;
	//f.set_stone(5,8,WHITE);
	f.set_stone(5,7,WHITE);
	f.set_stone(5,6,WHITE);
	f.set_stone(5,5,BLACK);
	f.set_stone(5,4,BLACK);
	f.set_stone(5,3,BLACK);

	
	//f.set_stone(3,6,WHITE);
	f.set_stone(3,5,WHITE);
	f.set_stone(3,4,BLACK);
	f.set_stone(3,3,BLACK);

	f.set_stone(7,8,WHITE);
	f.set_stone(7,7,BLACK);
	f.set_stone(7,6,BLACK);
	f.set_stone(7,5,BLACK);
	print_field(f);	

	/*nick_player player_one("Black", BLACK,1,2,1);
	alpha_beta_player player_two("White", WHITE);
	func(f,player_one,player_two);*/
	
	/*move player_move;
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
	}*/
}
