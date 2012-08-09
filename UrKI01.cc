#include <iostream>
#include "field.hh"

// ein Kommentar

using namespace std;


void print_position(pos p) {
	cout << p.a << " " << p.b << endl;
}

// suche mögliche Züge für
// 1 Kugel
int main(){

	field f = start_field();
	move m;
	m.a.a = 5;
	m.a.b = 3;
	m.b.a = 6;
	m.b.b = 4;
	m.c.a = 7;
	m.c.b = 5;
	m.dir = 2;
	if (move_valid(m,f)) {
	  cout << "valid move" << endl;
	}
	print_field(f);
	cout << "vor move"<< endl;
	do_move(f,m);
	cout << "nach move"<< endl;
	print_field(f);
return 0;
}


