#include "field.hh"
#include <algorithm>
#include <vector>
#include <limits>
#include "Uli_ki.hh"

class random_player {
	std::string player_name;
	stone player;
public:
	random_player(std::string name, stone p) : player_name(name), player(p) { }
	move operator()(field& f) {
		std::list<move> list;
		possible_moves(f, player, &list);
		
		std::vector<move> v(list.size());
		std::copy(list.begin(), list.end(), v.begin());
		std::random_shuffle(v.begin(), v.end());
		return v[0]; // assumes that there was at least one valid move
	}
};

struct minmax_result {
	double best_score;
	move best_move;
};

double minmax(field f, stone player, int factor=1, int level=0);

stone other_player(stone player) {
	if (player == WHITE)
		return BLACK;
	else
		return WHITE;
}

class alpha_beta_player {
	std::string player_name;
	stone player;
public:
	alpha_beta_player(std::string name, stone p)
		: player_name(name), player(p) { }
	move operator()(field& f) {
		std::list<move> list;
		possible_moves(f, player, &list);

		double best_score = -std::numeric_limits<double>::max();
		move best_move;
		
		for (std::list<move>::const_iterator iterator = list.begin(),
				 end = list.end(); iterator != end; ++iterator) {
			field copy = copy_field(f);

			do_move(copy, *iterator);
			double s = minmax(copy, other_player(player), -1, 0);
		
			if(s > best_score) {
				best_score = s;
				best_move = *iterator;
			}
		}
		
		std::cout << "minmax result: " << best_score << std::endl;
		return best_move;
	}
};

double estimator(field& f, stone player) {
	return Uli01_rate_move(f, player) + 4 * Uli02_rate_move(f, player)
		+ Uli03_rate_move(f, player) + Uli04_rate_move(f, player);
}

// factor is 1 if we are maximizing and -1 if we are minimizing
// and we are "level" levels down the tree
double minmax(field f, stone player, int factor, int level) {
	if(level > 2)
		return estimator(f, player);
	
	std::list<move> list;
	possible_moves(f, player, &list);

	// the maximum score so far
	double best_score = -std::numeric_limits<double>::max();
	
	// iterate over all possible moves
	for (std::list<move>::const_iterator iterator = list.begin(),
				 end = list.end(); iterator != end; ++iterator) {
		// fix this and do not copy the field...
		field copy = copy_field(f);

    do_move(copy, *iterator);
		double s = factor*minmax(copy, other_player(player), -factor, level+1);
		
		if(s > best_score)
			best_score = s;
	}
}
