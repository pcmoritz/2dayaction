#include <iostream>
#include "field.hh"
#include <sstream>
#include <cstdio>
#include "alpha-beta-ki.hh"
#include <time.h>

using namespace std;

void print_move(move Move){
	print_position(Move.a);
	print_position(Move.b);
	print_position(Move.c);
	//print_position(unitvec[Move.dir]);
	std::cout << Move.dir<<std::endl;
}

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

int count_stones(int color,field &f) {
	int tmp = 0;
	for(int i=0;i<11;i++) {
		for(int j=0;j<11;j++) {
			if(f.is_pos_inside(i, j)) {
				if(f.get_stone(i,j)==color) tmp+=1;

			} else {
				f.set_stone(i,j,EMPTY);
			}	
		}
	}
	return tmp;
}

bool check_victory(field &f){
	if(count_stones(WHITE,f)<7){
		std::cout<<"BLACK won!"<<std::endl;
		return true;
	}
	if(count_stones(BLACK,f)<7){
		std::cout<<"White won!"<<std::endl;	
	}
}

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
		if(move_valid(player_move,f)){
			do_move(f,player_move);	
		}else{
			std::cout<<"Black cheated"<<std::endl;
			print_field(f);
			print_move(player_move);
			std::getchar();
		}
		if(check_victory(f)) break;
		//print_field(f);
		//std::getchar();
		//print_field(f);
		player_move = player_two(f);
		if(move_valid(player_move,f)){
			do_move(f,player_move);
		}else{
			std::cout<<"White cheated"<<std::endl;
			print_field(f);
			print_move(player_move);
			std::getchar();	
		}
		if(check_victory(f)) break;
		//std::getchar();
	}
}
