#include <stdio.h>

struct pos {
	int a, b;
};

pos read_position() {
	int p;
	p = scanf("%d", &p);
	pos position;
	position.a = p/10;
	position.b = p%10;
	return position;
}

void print_position(pos p) {
	printf("(%d, %d)", p.a, p.b);
}

int main() {
	for (;;) {
		printf("Please specify your move!");
		pos p = read_position();
		print_position(p);
	}
}
