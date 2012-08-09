#include "field.hh"
#include <cstdio>
#include <cstdlib>
using std::srand;
using std::rand;
#include "rnd.h"

int ki_color = 1;


int get_random_dir(){ 
	int ret =rndint(0,5);
return ret;
}

void print_move(move Move){
	print_position(Move.a);
	print_position(Move.b);
	print_position(Move.c);
	//print_position(unitvec[Move.dir]);
	std::cout << Move.dir<<std::endl;
}

pos find_neighbor(pos a,field &Field){
	int start_pos;
	int dir;
	if(rndint(1,2)==1) start_pos =0;
	else start_pos =3;

	if(rndint(1,2)==1) dir = 1;
	else dir = -1;

	pos tmp = add_pos(a,unitvec[start_pos]);

	if(Field.get_stone(tmp.a,tmp.b)==ki_color){
			return tmp;
		}
	
	for(int i=0;i<5;i++){	
		start_pos =(start_pos+dir)%6;
		tmp = add_pos(a,unitvec[start_pos]);
		if(Field.get_stone(tmp.a,tmp.b)==ki_color){
			return tmp;
		}
	}
	tmp = not_a_position;
	/*tmp.a =-1;
	tmp.b =-1;*/
}

move ki_do_move(field &Field) {
	int a=rndint(1,9);
	int b=rndint(1,9);
	while(!Field.get_stone(a,b)==ki_color) {
		a=rndint(1,9);
		b=rndint(1,9);		
	}
	//std::cout << "found stone at pos:"<< a<<"\t"<<b<<std::endl;
	pos tmp;
	tmp.a = a;
	tmp.b = b;
	pos tmp2 = find_neighbor(tmp,Field);
	if(!is_equal(tmp2,not_a_position)){
		//std::cout<< "found Neighbor"<<std::endl;
		pos tmp3 = sub_pos(tmp2,tmp);
		tmp3 = add_pos(tmp2,tmp3);		
		if(Field.get_stone(tmp3.a,tmp3.b)==ki_color) {
			//std::cout<<"trying to move 3 stones"<<std::endl;
			
			//Move three stones
			move Move;
			for(int i=0;i<6;i++) {
				int dir = get_random_dir();
					Move.a = tmp;
					Move.b =tmp2;
					Move.c = tmp3;
					Move.dir = dir;
					//print_move(Move);
				
				if(move_valid(tmp,tmp2,tmp3,unitvec[dir],Field)) {
					
					
					if(!is_over_bord(Move)) return Move;
					else{
						Move.a = not_a_position;
						Move.b = not_a_position;
						Move.c = not_a_position;
						return Move;
					}
				}
			}
			Move.a = not_a_position;
			Move.b = not_a_position;
			Move.c = not_a_position;
			return Move;
			

		}else{
			//Move two stones
			//std::cout<<"trying to move 2 stones"<<std::endl;
			move Move;
			for(int i=0;i<6;i++) {
				int dir = get_random_dir();
				if(move_valid(tmp,tmp2,unitvec[dir],Field)) {
					
					Move.a = tmp;
					Move.b =tmp2;
					Move.c = not_a_position;
					Move.dir = dir;
					if(!is_over_bord(Move)) return Move;
					else{
						Move.a = not_a_position;
						Move.b = not_a_position;
						Move.c = not_a_position;
						return Move;
					}
				}
			}
			Move.a = not_a_position;
			Move.b = not_a_position;
			Move.c = not_a_position;
			return Move;

		}
	}else{
		//Move one stone
		move Move;
		for(int i=0;i<6;i++) {
			int dir = get_random_dir();
			if(move_valid(tmp,unitvec[dir],Field)) {
				
				Move.a = tmp;
				Move.b =not_a_position;
				Move.c = not_a_position;
				Move.dir = dir;
				if(!is_over_bord(Move)) return Move;
				else{
					Move.a = not_a_position;
					Move.b = not_a_position;
					Move.c = not_a_position;
					return Move;
				}
			}
		}
		Move.a = not_a_position;
		Move.b = not_a_position;
		Move.c = not_a_position;
		return Move;
	}	
}	
/*
int main(){
	InitRandom();
}*/
