#include "field.hh"
#include <cstdio>
#include <cstdlib>
using std::srand;
using std::rand;
#include "rnd.h"

int ki_color = 1;

/*pos unitvec[6] = {{1,1},{0,1},{-1,0},{-1,-1},{0,-1},{1,0}};

bool is_equal(pos a, pos b) {
	if(a.a==b.a&& a.b ==b.b) return true;
	else return false;
}

pos add_pos(pos a, pos b){
	pos c;
	c.a = a.a+b.a;
	c.b = a.b+b.b;
	return c;
}
pos sub_pos(pos a, pos b){
	pos c;
	c.a = a.a-b.a;
	c.b = a.b-b.b;
	return c;
}
pos inv_dir(pos a){
	pos c;
	c.a = -a.a;
	c.b = -a.b;
	return c;
}*/



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
	tmp.a =-1;
	tmp.b =-1;
}

move ki_do_move(field &Field) {
	int a=rndint(1,9);
	int b=rndint(1,9);
	while(Field.get_stone(a,b)) {
		a=rndint(1,9);
		b=rndint(1,9);		
	}
	pos tmp;
	tmp.a = a;
	tmp.b = b;
	pos tmp2 = find_neighbor(tmp,Field);
	if(tmp2.a!=-1){
		pos tmp3 = sub_pos(tmp2,tmp);
		tmp3 = add_pos(tmp,tmp3);		
		if(Field.get_stone(tmp3.a,tmp3.b)==ki_color){
			//Move three stones

		}else{
			//Move two stones

		}
	}else{
		//Move one stone

	}	
}	

int main(){
	InitRandom();
}
