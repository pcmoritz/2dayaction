#include "field.hh"
#include <algorithm>
#include <vector>
#include <limits>

stone other_player(stone player) {
	if (player == WHITE)
		return BLACK;
	else
		return WHITE;
}

const int MAX_LEVEL = 3;

double nega_max(field f, stone player, int level,
								double alpha, double beta, move& best_move);

class alpha_beta_player_extended {
	std::string player_name;
	stone player;
public:
	alpha_beta_player_extended(std::string name, stone p)
		: player_name(name), player(p) { }
	move operator()(field& f) {
		move best_move;
		double inf = std::numeric_limits<double>::max();
		nega_max(f, player, MAX_LEVEL, -inf, inf, best_move);
		return best_move;
	}
};

double nega_max(field f, stone player, int level,
								double alpha, double beta, move& best_move) {
	if (level == 0)
		return;
	
	std::list<move> list;
	possible_moves(f, player, &list);
	
	double local_alpha = -std::numeric_limits<double>::max();

	for (std::list<move>::const_iterator iterator = list.begin(),
				 end = list.end(); iterator != end; ++iterator) {
		field copy = copy_field(f);

    do_move(copy, *iterator);
		double s = -nega_max(copy, other_player(player), level-1, -beta, -alpha, best_move);
		
		if(s > local_alpha) {
			if(s > local_alpha)
				alpha = s;
			local_alpha = s;
			best_move = *iterator;
			if(alpha >= beta)
				break;
		}
	}
	return local_alpha;
}
