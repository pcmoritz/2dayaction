#include "field.hh"
#include <list>
#include <iostream>

pos add_pos_dir(int a, int b, int dir) {
	pos p = {a, b};
	return add_pos(p, unitvec[dir]);
}

void add_move_one(std::list<move>& list, pos p, pos dir) {
	std::cout << "Possible move:";
	print_position(p);
	std::cout << " ";
	print_position(dir);
}

// position not occupied and inside bounds
bool position_free(field& f, pos other) {
	return (f.get_stone(other.a, other.b) == 0) &&
		f.is_pos_inside(other.a, other.b);
}

// add all possible moves with one stone
void search_one(field& f, stone player, std::list<move>& list) {
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(f.get_stone(i, j) == player) {
				// iterate over directions
				for(int dir = 0; dir <= 5; ++dir) {
					pos p = {i, j};
					pos q = add_pos(p, unitvec[dir]);
					if(position_free(f, q)) {
						add_move_one(list, p, unitvec[dir]);
					}
				}
			}
		}
	}
}

void add_move_two(std::list<move>& list, pos p, pos q, int dir) {
	std::cout << "Possible move:";
	print_position(p);
	std::cout << " ";
	print_position(q);
	std::cout << " ";
	std::cout << dir;
	std::cout << std::endl;
}

bool different_players(int a, int b) {
	return (b != a) && (b != 0);
}

void search_two(field& f, stone player, std::list<move>& list) {
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(f.get_stone(i, j) == player) {
				for(int delta = 0; delta <= 2; ++delta) {					
					if(f.get_stone(add_pos_dir(i, j, delta)) == player) {
						for(int dir = 0; dir <= 5; ++dir) {
							pos p = {i, j};
							pos other = add_pos_dir(i, j, delta);
							// if parallel:
							// same direction
							if(dir == delta) {
								if(position_free(f, add_pos_dir(other.a, other.b, dir)))
									add_move_two(list, p, other, dir);

								// Wegschiebfall p other p1 p2
								pos p1 = add_pos_dir(other.a, other.b, dir);
								pos p2 = add_pos_dir(p1.a, p1.b, dir);
								if(different_players(player, f.get_stone(p1)) &&
									 f.get_stone(p2) == 0) {
									// adden
									add_move_two(list, p, other, dir);
								}
							}
							// opposite direction
							if((delta + 3 - dir) % 6 == 0) {
								if(position_free(f, add_pos_dir(p.a, p.b, dir)))
									add_move_two(list, p, other, dir);

								// Wegschiebfall p2 p1 p other
								pos p1 = add_pos_dir(p.a, p.b, dir);
								pos p2 = add_pos_dir(p1.a, p1.b, dir);
								if(different_players(player, f.get_stone(p1)) &&
									 f.get_stone(p2) == 0) {
										 // adden
										 add_move_two(list, p, other, dir);
									 }
							}

							// if non-parallel:
							else {
								pos a = add_pos_dir(i, j, dir);
								pos b = add_pos_dir(a.a, a.b, delta);
								if(position_free(f, a) && position_free(f, b))
									add_move_two(list, p, other, dir);
							}
						}
					}
				}
			}
		}
	}
}


void add_move_three(std::list<move>& list, pos p, pos q, pos r, int dir) {
	std::cout << "Possible move:";
	print_position(p);
	std::cout << " ";
	print_position(q);
	std::cout << " ";
	print_position(r);
	std::cout << " ";
	std::cout << dir;
	std::cout << std::endl;
}

void search_three(field& f, stone player, std::list<move>& list) {
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(f.get_stone(i, j) == player) {
				pos a = {i, j};
				for(int delta = 0; delta <= 2; ++delta) {
					pos b = add_pos_dir(i, j, delta);
					if(f.get_stone(b) == player)  {
						pos c = add_pos_dir(b.a, b.b, delta);
						if(f.get_stone(c) == player) {
							// finally free
							for(int dir = 0; dir <= 5; ++dir) {
								// first the parallel case
								if(dir == delta) {
									pos d = add_pos_dir(c.a, c.b, delta);
									if(position_free(f, d))
										add_move_three(list, a, b, c, dir);
									// Wegschiebfall
								}
							}
						}						
					}
				}
			}
		}
	}
}



std::list<move> possible_moves(field& f, stone player) {
	std::list<move> list;

	search_one(f, player, list);
	std::cout << std::endl;
	search_two(f, player, list);
	
	return list;
}
