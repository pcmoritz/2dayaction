#ifndef ULI_KI_HH
#define ULI_KI_HH

#include <cmath>
#include <vector>
#include "field.hh"

// Uli01 bewertet, wie zentral die Steine stehen
// Uli02 bewertet, wie geklumpt die Steine stehen
// Uli03 bewertet, ob ein Stein hinausgeschoben werden kann
// Uli04 sucht günstige/ungünstige Muster


using namespace std;
double Uli01_rate_move(field& f, int player) {
	double Bewertung=0; double Wert=0;
  	for(int i = 0; i <= N+1; ++i) {
		for(int j = 0; j <= N+1; ++j){
			int r;
			if (i>=5 && j>=5) {r= std::max(i-5,j-5);}
			if (i<=5 && j<=5) {r= std::max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			
			if (r==0) {Wert=320;}
			if (r==1) {Wert=210;}
			if (r==2) {Wert=195;}
			if (r==3) {Wert=175;}
			if (r==4) {Wert=150;}
			if (r==5) {Wert=0;}
			
			if (f.get_stone(i, j)==player) {Bewertung+=Wert;}
			if ((f.get_stone(i, j)!=player) &&(f.get_stone(i, j)!=EMPTY)) {Bewertung-=Wert;}
		}  	
	}
return Bewertung;
}

double Uli02_rate_move(field& f, int player) {
	double Bewertung=0; double Wert=0; pos nachbar;
  	for(int i = 0; i <= N+1; ++i) {
		for(int j = 0; j <= N+1; ++j){
			if(f.get_stone(i,j)==player){
			  for(int dir = 0; dir <= 5; ++dir) {
			    pos temp;
			    temp.a = i;temp.b = j;
			    nachbar = add_pos(unitvec[dir],temp);
			    if (f.get_stone(nachbar.a,nachbar.b)==0){Wert-=1;}
			  }
			}
			if(f.get_stone(i,j)!=player && f.get_stone(i,j)!=EMPTY){
			  for(int dir = 0; dir <= 5; ++dir) {
			    pos temp;
			    temp.a = i;temp.b = j;
			    nachbar = add_pos(unitvec[dir],temp);
			    if (f.get_stone(nachbar.a,nachbar.b)==0){Wert+=1;}
			  }
			}
		}  
	}
	Bewertung = Wert;
return Bewertung;
}

double Uli03_rate_move(field& f, int player) {
	double Bewertung=0;
  	for(int i = 0; i <= N+1; ++i) {
		for(int j = 0; j <= N+1; ++j){
			int r;
			if (i>=5 && j>=5) {r= std::max(i-5,j-5);}
			if (i<=5 && j<=5) {r= std::max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			
			if ((f.get_stone(i, j)!=player) &&(f.get_stone(i, j)!=EMPTY&& r==5)) {Bewertung+=100;}
			
		}  	
	}
return Bewertung;
}

double Uli04_rate_move(field& f, int player) {
	double Bewertung=0;
	pos pos1,pos2,pos3,pos4,pos5;
	for(int dir = 0; dir <= 5; ++dir) { 
		for(int i = 1; i <= N; ++i) {
			for(int j = 1; j <= N; ++j){
				if (not((i > 1) && (j > 1) && (i < 9) && (j < 9) && (std::abs((long)(i-j))) < 4)){
				pos1.a = i;
				pos1.b = j;
				pos2.a = i+unitvec[dir].a;
				pos2.b = j+unitvec[dir].b;
				pos3.a = i+unitvec[dir].a+unitvec[dir].a;
				pos3.b = j+unitvec[dir].b+unitvec[dir].b;
				pos4.a = i+unitvec[dir].a+unitvec[dir].a+unitvec[dir].a;
				pos4.b = j+unitvec[dir].b+unitvec[dir].b+unitvec[dir].b;
				pos5.a = i+unitvec[dir].a+unitvec[dir].a+unitvec[dir].a+unitvec[dir].a;
				pos5.b = j+unitvec[dir].b+unitvec[dir].b+unitvec[dir].b+unitvec[dir].b;
			  
				if ((f.get_stone(pos1.a, pos1.b)==player)&& 
				    (f.get_stone(pos2.a, pos2.b)==player)&&
				    (f.get_stone(pos3.a, pos3.b)!=player)&&(f.get_stone(pos3.a, pos3.b)!=EMPTY)&&
				    (f.get_stone(pos4.a, pos4.b)!=player)&&(f.get_stone(pos4.a, pos4.b)!=EMPTY)&&
				    (f.get_stone(pos5.a, pos5.b)!=player)&&(f.get_stone(pos5.a, pos5.b)!=EMPTY))				    
				{Bewertung-=50;}
				
				if ((f.get_stone(pos1.a, pos1.b)==player)&& 
				    (f.get_stone(pos2.a, pos2.b)!=player)&&(f.get_stone(pos2.a, pos2.b)!=EMPTY)&&
				    (f.get_stone(pos3.a, pos3.b)!=player)&&(f.get_stone(pos3.a, pos3.b)!=EMPTY)&&
				    (f.get_stone(pos4.a, pos4.b)!=player)&&(f.get_stone(pos4.a, pos4.b)!=EMPTY))				    
				{Bewertung-=50;}
				
				if ((f.get_stone(pos1.a, pos1.b)==player)&& 
				    (f.get_stone(pos2.a, pos2.b)!=player)&&(f.get_stone(pos2.a, pos2.b)!=EMPTY)&&
				    (f.get_stone(pos3.a, pos3.b)!=player)&&(f.get_stone(pos3.a, pos3.b)!=EMPTY))				    
				{Bewertung-=50;}
				
				
				if ((f.get_stone(pos5.a, pos5.b)==player)&& 
				    (f.get_stone(pos4.a, pos4.b)==player)&&
				    (f.get_stone(pos3.a, pos3.b)==player)&&
				    (f.get_stone(pos2.a, pos2.b)!=player)&&(f.get_stone(pos2.a, pos2.b)!=EMPTY)&&
				    (f.get_stone(pos1.a, pos1.b)!=player)&&(f.get_stone(pos1.a, pos1.b)!=EMPTY))				    
				{Bewertung+=50;}
				
				if ((f.get_stone(pos4.a, pos4.b)==player)&& 
				    (f.get_stone(pos3.a, pos3.b)==player)&&
				    (f.get_stone(pos2.a, pos2.b)==player)&&
				    (f.get_stone(pos1.a, pos1.b)!=player)&&(f.get_stone(pos1.a, pos1.b)!=EMPTY))				    
				{Bewertung+=50;}
				
				if ((f.get_stone(pos3.a, pos3.b)==player)&& 
				    (f.get_stone(pos2.a, pos2.b)==player)&&
				    (f.get_stone(pos1.a, pos1.b)!=player)&&(f.get_stone(pos1.a, pos1.b)!=EMPTY))				    
				{Bewertung+=50;}
				  
				}
			}  	
		}	  
	}
return Bewertung;
}

class Uli_player {
	std::string player_name;
	stone player;
	double *param;
public:
	
	Uli_player(std::string name, stone p,double a=1,double b=2, double c=0) : player_name(name), player(p) {	
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
		for (size_t n=0;n<list.size();n++) {
		  field f_hyp=copy_field(f);
		  do_move(f_hyp, v[n]);
		  
		  Bewertung = Uli01_rate_move(f_hyp, player) + 4 * Uli02_rate_move(f_hyp, player) + Uli03_rate_move(f_hyp, player) + Uli04_rate_move(f_hyp, player);
		  // cout << Uli01_rate_move(f_hyp, player) << " " << Uli02_rate_move(f_hyp, player)<< endl;
		  if (temp<Bewertung) {temp = Bewertung; aktuellbesterZug = n;}
		//cout << "Zug Nummer: " << n << " mit Bewertung: " << Bewertung << " temp:" << temp << endl;		  
		}
		return v[aktuellbesterZug];
// 		std::copy(list.begin(), list.end(), v.begin());
// 		std::random_shuffle(v.begin(), v.end());
// 		return v[0]; // assumes that there was at least one valid move
	}
};

#endif
