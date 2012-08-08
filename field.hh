#include <cmath>

const int N = 9; // size of the field
const int K = std::ceil(N/2);

struct pos {
	int a, b;
};

enum stone {
	EMPTY = 0, BLACK = 1, WHITE = 2
};

int abs(int x) {
	if(x > 0)
		return x;
	else
		return -x;
}

class field {
	stone stones[N+2][N+2];
public:
	field() {
		for(int i = 0; i < N+2; ++i) {
			for(int j = 0; j < N+2; ++j)
				stones[i][j] = EMPTY;
		}
		for(int i = 1; i < K; ++i) {
			stones[K][i] = BLACK;
		}
		for(int i = 1; i < K+1; ++i) {
			stones[K-1][i] = BLACK;
		}
		for(int i = 3; i <= K; ++i) {
			stones[K-2][i] = BLACK;
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
