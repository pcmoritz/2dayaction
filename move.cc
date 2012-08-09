#include "field.hh"



void do_move(field& f, move m) {
	// first try if the move is valid... (to be implemented)
	
	pos a = m.a;
	pos b = m.b;
	pos c = m.c;
	int dir = m.dir;
	pos temp = a;
	pos backtemp = a;
	stone player = f.get_stone(a.a, a.b);
	
	// suche nach erster freien Position in dir
	
	do {
	  temp = add_pos(temp, unitvec[dir]);
	} while (f.get_stone(temp.a,temp.b) != 0);
	
	// verschiebe alle Steine bis Pos a
	while (not (is_equal(temp,a))) {
	  backtemp = sub_pos(temp, unitvec[dir]);
	  f.set_stone(temp.a, temp.b, f.get_stone(backtemp.a,backtemp.b));
	  temp = sub_pos(temp, unitvec[dir]);
	}; 
	
	// verschiebe die drei Steine
	pos next_a = add_pos(a, unitvec[dir]);
	pos next_b = add_pos(b, unitvec[dir]);
	pos next_c = add_pos(c, unitvec[dir]);
	
	// zero the old positions
	if(is_valid_pos(a))
		f.set_stone(a.a, a.b, EMPTY);
	if(is_valid_pos(b))
		f.set_stone(b.a, b.b, EMPTY);
	if(is_valid_pos(c))
		f.set_stone(c.a, c.b, EMPTY);
	
	// set new positions
	if(is_valid_pos(a))
		f.set_stone(next_a.a, next_a.b, player);
	if(is_valid_pos(b))
		f.set_stone(next_b.a, next_b.b, player);
	if(is_valid_pos(c))
		f.set_stone(next_c.a, next_c.b, player);
}
	
	