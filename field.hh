#ifndef FIELD_H
#define FIELD_H

#include <cmath>
#include <iostream>

const int N = 9; // size of the field
const int K = std::ceil(N/2.0);

struct pos {
	int a, b;
};

extern pos not_a_position;

struct move {
	pos a, b, c;
	int dir;
};

enum stone {
	EMPTY = 0, BLACK = 1, WHITE = 2
};

int abs(int x);

class field {
	stone stones[N+2][N+2];
public:
	field() {
		for(int i = 0; i < N+2; ++i) {
			for(int j = 0; j < N+2; ++j)
				stones[i][j] = EMPTY;
		}
	}
	stone get_stone(int a, int b) {
		return stones[a][b];
	}
	void set_stone(int a, int b, stone s) {
		stones[a][b] = s;
	}
	bool is_pos_inside(int a, int b) {
		return (a > 0) && (b > 0) && (a < 10) && (b < 10) && (abs(a-b) < 5);
	}
};

field copy_field(field f);

// a field with normal start conditions (valid only for N=9)
field start_field();
field coordinate_field();

void print_field(field f);

extern const pos unitvec[6];
pos add_pos(pos a, pos b);

void do_move(field& f, move m);

#endif
