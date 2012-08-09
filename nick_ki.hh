#include <cmath>
#include <vector>
#include "field.hh"

double rate_move(field& f, int player,double *param) {
	double Bewertung=0;
	if(player==1)//std::cout<<param[3]<<"\t"<<count_stones(player+1,f)<<std::endl;
	if(player==1) {
		if(param[3]> count_stones(player+1,f)){
			Bewertung+=100*param[2];
			//std::cout<<"a"<<std::endl;
		}
	}else {
		if(param[3]> count_stones(player-1,f))Bewertung+=100*param[2];
	}
  	for(int i = 0; i <= N+1; ++i) {
		for(int j = 1; j <= N; ++j){
			int r;
			if (i>=5 && j>=5) {r= std::max(i-5,j-5);}
			if (i<=5 && j<=5) {r= std::max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			if (f.get_stone(i, j)==player) {Bewertung+=-pow((param[0]+r),param[1]);}
			if ((f.get_stone(i, j)!=player) &&(f.get_stone(i, j)!=EMPTY)) {Bewertung-=-pow((param[0]+r),param[1]);}
		}  
	}
return Bewertung;
}

class nick_player {
	std::string player_name;
	stone player;
	double *param;
public:
	
	nick_player(std::string name, stone p,double a=1,double b=2, double c=0) : player_name(name), player(p) {	
		param= new double[4];
		param[0] = a;
		param[1] = b;
		param[2] = c;
	}
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
			if(player==1) {
				param[3] = count_stones(player+1,f);
			}else {
				param[3] = count_stones(player-1,f);
			}
			do_move(f_hyp, v[n]);
		  
		  Bewertung = rate_move(f_hyp, player,param);
		  if (temp<Bewertung) {temp = Bewertung; aktuellbesterZug = n;}
		//cout << "Zug Nummer: " << n << " mit Bewertung: " << Bewertung << " temp:" << temp << endl;		  
		}
		return v[aktuellbesterZug];
// 		std::copy(list.begin(), list.end(), v.begin());
// 		std::random_shuffle(v.begin(), v.end());
// 		return v[0]; // assumes that there was at least one valid move
	}
};
