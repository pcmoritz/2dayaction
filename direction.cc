#include <iostream>
#include "field.hh"
using namespace std;
pos unitvec[6] = {{1,1},{0,1},{-1,0},{-1,-1},{0,-1},{1,0}};

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
}

bool move_valid(pos a, pos dir,field &f) {
	if(f.get_stone(add_pos(a,dir).a,add_pos(a,dir).b)) return false;
	else return true;
}

bool move_valid(pos a, pos b,pos dir,field &f) {
	if(f.get_stone(a.a,a.b)==f.get_stone(b.a,b.b)){

		pos c = sub_pos(a,b);
		if(is_equal(c,dir) or is_equal(inv_dir(c),dir)) {
			//CASE: PARALLEL
		
			if(is_equal(add_pos(b,dir),a)) {
				//a is in front
				cout<<"a is in front"<<endl;
				pos tmp = add_pos(a,dir);
				if(f.get_stone(tmp.a,tmp.b)) {
					//Case: 3 stones of same colour
					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
						return false;
					}else{

						tmp = add_pos(tmp,dir);
						if(f.get_stone(tmp.a,tmp.b)) {
						//double occupation
							return false;
						}
				
						//PUSH

						return true;
					}
				}
				//Next neighbor not occupied
				return true;
			}else{
				//b is in front
				cout<<"b is in front"<<endl;
				pos tmp = add_pos(b,dir);
				if(f.get_stone(tmp.a,tmp.b)) {
					//Case: 3 stones of same colour
					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
						return false;
					}else{

						tmp = add_pos(tmp,dir);
						if(f.get_stone(tmp.a,tmp.b)) {
						//double occupation
							return false;
						}
				
						//PUSH

						return true;
					}
				}
				//Next neighbor not occupied
				return true;

			}

		}else{
			cout<<"NPARALLEL"<<endl;
			
			pos tmp = add_pos(a,dir);
			pos tmp2 = add_pos(b,dir);
			if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b)) return false;
			else return true;
		}
	}else return false;
}


int main(){
	field Feld;
	Feld.set_stone(5,4,EMPTY);
	Feld.set_stone(5,2,EMPTY);

	
	Feld.set_stone(4,2,BLACK);
	Feld.set_stone(4,1,BLACK);
	pos b = {4,3};
	pos a = {4,1};

	cout << move_valid(a,b,unitvec[0],Feld)<<endl;
}
