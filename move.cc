#include "field.hh"

void do_move(field& f, move m) {
	// first try if the move is valid...
	pos a = m.a;
	pos b = m.b;
	pos c = m.c;
	int dir = m.dir;

	stone player = f.get_stone(a.a, a.b);

	pos next_a = add_pos(a, unitvec[dir]);
	pos next_b = add_pos(b, unitvec[dir]);
	pos next_c = add_pos(c, unitvec[dir]);

	// zero the old positions
	f.set_stone(a.a, a.b, EMPTY);
	f.set_stone(b.a, b.b, EMPTY);
	f.set_stone(c.a, c.b, EMPTY);

	// set new positions
	f.set_stone(next_a.a, next_a.b, player);
	f.set_stone(next_b.a, next_b.b, player);
	f.set_stone(next_c.a, next_c.b, player);
}
