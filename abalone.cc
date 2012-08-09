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
	
	field f = start_field();
	//possible_moves(f, BLACK);
	print_field(f);
	InitRandom();
	move Test;
	while(is_equal(Test.a,not_a_position)){	
		Test = ki_do_move(f);
	}
	do_move(f,Test);
	//print_move(Test);
	print_field(f);
	

	//is_over_bord test	
	/*pos a,b,c;
	a.a = 7;
	a.b = 5;
	cout<< move_valid(a,unitvec[4],f)<<endl;
	b.a = 1;
	b.b = 5;
	move Test;
	Test.a =a;
	Test.b = b;
	//Test.c = not_a_position;
	Test.dir = 4;*/
	//cout << is_over_bord(Test)<<endl;	
}
