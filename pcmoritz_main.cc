#include "field.hh"
#include <iostream>

void print_position(pos p) {
	std::cout << p.a << " " << p.b << std::endl;
}

void print_move(move m) {
	std::cout << "move:" << std::endl;
	print_position(m.a);
	if(is_valid_pos(m.b))
		print_position(m.b);
	if(is_valid_pos(m.c))
		print_position(m.c);
	std::cout << m.dir << std::endl;
}

int main() {
	field f = start_field();
	std::list<move> list;
	possible_moves(f, BLACK, &list);

	for (std::list<move>::const_iterator iterator = list.begin(),
				 end = list.end(); iterator != end; ++iterator) {
    print_move(*iterator);
	}
}
