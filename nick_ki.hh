#include <cmath>
#include <vector>
#include "field.hh"

double rate_move(field& f, int player) {
	double Bewertung=0;
  	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j){
			int r;
			if (i>=5 && j>=5) {r= std::max(i-5,j-5);}
			if (i<=5 && j<=5) {r= std::max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			if (f.get_stone(i, j)==player) {Bewertung+=-(1+r)*(1+r);}
			if ((f.get_stone(i, j)!=player) &&f.get_stone(i, j)!=EMPTY) {Bewertung-=-(1+r)*(1+r);}
		}  
	}
return Bewertung;
}

class nick_player {
	std::string player_name;
	stone player;
public:
	
	nick_player(std::string name, stone p) : player_name(name), player(p) { }
	move operator()(field& f) {
		std::list<move> list;
		possible_moves(f, player, &list); 
		std::vector<move> v(list.size());  //mit Anzahl der Elemente
		std::copy(list.begin(), list.end(), v.begin());
		
		int aktuellbesterZug = 0;
		double Bewertung = 0;
		double temp = -100000;
		for (int n=0;n<list.size();n++) {
		  field f_hyp=copy_field(f);
		  do_move(f_hyp, v[n]);
		  
		  Bewertung = rate_move(f_hyp, player);
		  if (temp<Bewertung) {temp = Bewertung; aktuellbesterZug = n;}
		//cout << "Zug Nummer: " << n << " mit Bewertung: " << Bewertung << " temp:" << temp << endl;		  
		}
		return v[aktuellbesterZug];
// 		std::copy(list.begin(), list.end(), v.begin());
// 		std::random_shuffle(v.begin(), v.end());
// 		return v[0]; // assumes that there was at least one valid move
	}
};
