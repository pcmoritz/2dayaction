const int N = 9; // size of the field

enum stone {
	EMPTY = 0, BLACK = 1, WHITE = 2
};

class field {
	stone field[N+2][N+2];
public:
	stone get_stone(int a, int b) {
		return field[a][b];
	}
	void set_stone(int a, int b, stone s) {
		field[a][b] = s;
	}
};
