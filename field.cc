#include "field.hh"

int abs(int x) {
	if(x > 0)
		return x;
	else
		return -x;
}

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
