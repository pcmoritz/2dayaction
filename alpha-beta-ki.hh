#include "field.hh"
#include <algorithm>
#include <vector>

class alpha_beta_player {
	std::string player_name;
	stone player;
public:
	alpha_beta_player(std::string name, stone p) : player_name(name), player(p) { }
	move operator()(field& f) {
		std::list<move> list;
		possible_moves(f, player, &list);
		std::vector<move> v(list.size());
		std::copy(list.begin(), list.end(), v.begin());
		std::random_shuffle(v.begin(), v.end());
		return v[0]; // assumes that there was at least one valid move
	}
};
