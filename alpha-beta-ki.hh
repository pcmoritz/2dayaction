#include "field.hh"
#include <algorithm>
#include <vector>
#include <limits>

int stonesa;
int stonesb;

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
		stonesa = count_stones(other_player(player),f);
		stonesb = count_stones(player,f);
		
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

double UH1(field& f, int player) {
	double Bewertung=0;
	if(stonesa> count_stones((int)other_player((stone)player),f)){
			Bewertung+=100;
		}
	if(stonesb < count_stones(player,f)){
			Bewertung-=1000;
		}
  	for(int i = 0; i <= N+1; ++i) {
		for(int j = 0; j <= N+1; ++j){
			int r;
			if (i>=5 && j>=5) {r= std::max(i-5,j-5);}
			if (i<=5 && j<=5) {r= std::max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			if (f.get_stone(i, j)==player) {Bewertung+=-pow((1+r),2);}
			if ((f.get_stone(i, j)!=player) &&(f.get_stone(i, j)!=EMPTY)) {Bewertung-=-pow((1+r),2);}
		}  
	}
return Bewertung;
}

// factor is 1 if we are maximizing and -1 if we are minimizing
// and we are "level" levels down the tree
double minmax(field f, stone player, int factor, int level) {
	if(level > 2)
		return UH1(f, (int)player);
	
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
