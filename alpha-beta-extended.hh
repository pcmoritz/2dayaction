#include "field.hh"
#include <algorithm>
#include <vector>
#include <limits>
#include "Uli_ki.hh"
#include <cstdlib>

int num_ops = 0; // debugging

stone other_player(stone player) {
	if (player == WHITE)
		return BLACK;
	else
		return WHITE;
}

const int MAX_LEVEL = 3;

double nega_max(field f, stone player, int level,
								double alpha, double beta, move* best_move);

class alpha_beta_player_extended {
	std::string player_name;
	stone player;
public:
	alpha_beta_player_extended(std::string name, stone p)
		: player_name(name), player(p) { }
	move operator()(field& f) {
		num_ops = 0;
		move best_move;
		field copy = copy_field(f);
		double inf = std::numeric_limits<double>::max();
		double result = nega_max(f, player, MAX_LEVEL, -inf, inf, &best_move);
		std::cout << "result: " << result << " ops: " << num_ops << std::endl;
		print_move(best_move);
		return best_move;
	}
};

double estimator(field& f, stone player) {
	return Uli01_rate_move(f, player) + 4 * Uli02_rate_move(f, player)
		+ Uli03_rate_move(f, player) + Uli04_rate_move(f, player);
}

double nega_max(field f, stone player, int level,
								double alpha, double beta, move* best_move) {
	if (level == 0)
		return estimator(f, player);
	
	std::vector<move> moves;
	vector_possible_moves(f, player, &moves);

	double best = -std::numeric_limits<double>::max();

	for(size_t i = 0; i < moves.size(); ++i) {
		//	for (std::list<move>::const_iterator iterator = list.begin(),
		//				 end = list.end(); iterator != end; ++iterator) {
		move m = moves[i];
		field copy = copy_field(f);
		num_ops++;

    do_move(copy, m);
		double s = -nega_max(copy, other_player(player), level-1, -beta, -alpha, best_move);
		//		std::cout << "level: " << level << " s: " << s << std::endl;

		if(s > best) {
			best = s;
			if(level == MAX_LEVEL)
				*best_move = m;
		}
		if(best > alpha)
			alpha = best;
		if(best >= beta)
			return best;
	}
	return best;
}
