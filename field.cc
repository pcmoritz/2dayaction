#include "field.hh"

field start_field() {
	field f;
	for(int i = 1; i <= 5; ++i) {
		f.set_stone(i, i+4, BLACK);
	}

	for(int i = 1; i <= 6; ++i) {
		f.set_stone(i, i+3, BLACK);
	}

	for(int i = 3; i <= 5; ++i) {
		f.set_stone(i, i+2, BLACK);
	}

	for(int i = 1; i <= 5; ++i) {
		f.set_stone(i+4, i, WHITE);
	}

	for(int i = 1; i <= 6; ++i) {
		f.set_stone(i+3, i, WHITE);
	}

	for(int i = 3; i <= 5; ++i) {
		f.set_stone(i+2, i, WHITE);
	}
	
	return f;
}

field coordinate_field() {
	field f;
	for(int i = 0; i < N+2; ++i) {
		for(int j = 0; j < N+2; ++j)
			f.set_stone(i, j, (stone)(i*10 + j));
	}
	return f;
}

field test_field() {
	field f;
	//f.set_stone(2,2,WHITE);
	f.set_stone(1,1,BLACK);
	f.set_stone(2,1,BLACK);
	f.set_stone(3,1,BLACK);
	f.set_stone(4,1,WHITE);
	f.set_stone(5,1,BLACK);
	return f;
}

field copy_field(field f) {
	field new_field;
	for(int i = 0; i < N+2; ++i) {
		for(int j = 0; j < N+2; ++j) {
			new_field.set_stone(i, j, f.get_stone(i, j));
		}
	}
	return new_field;
}

pos not_a_position = {-42, -42};

bool is_valid_pos(pos p) {
	return (p.a != not_a_position.a || p.b != not_a_position.b);
}
