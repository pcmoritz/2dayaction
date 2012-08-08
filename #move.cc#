#include "field.hh"

void do_move(field& f, move m) {
	// first try if the move is valid... (to be implemented)
	
	pos a = m.a;
	pos b = m.b;
	pos c = m.c;
	int dir = m.dir;

	stone player = f.get_stone(a.a, a.b);

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
