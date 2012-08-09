#include <iostream>
#include "field.hh"
#include <algorithm>
#include <vector>

// ein Kommentar

using namespace std;

double UH1(field& f, int player) {
	double Bewertung=0;
  	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j){
			int r;
			if (i>=5 && j>=5) {r= max(i-5,j-5);}
			if (i<=5 && j<=5) {r= max(abs(i-5),abs(j-5));}
			if ((i>=5 && j<=5) || (i<=5 && j>=5)) {r = abs(i-j);}
			if (f.get_stone(i, j)==1) {Bewertung+=-(1+r)*(1+r);}
			if (f.get_stone(i, j)==2) {Bewertung-=-(1+r)*(1+r);}
		}  
	}
return Bewertung;
}

class Uli_player {
	std::string player_name;
	stone player;
public:
	
	Uli_player(std::string name, stone p) : player_name(name), player(p) { }
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
		  
		  Bewertung = UH1(f_hyp, player);
		  if (temp<Bewertung) {temp = Bewertung; aktuellbesterZug = n;}
		cout << "Zug Nummer: " << n << " mit Bewertung: " << Bewertung << " temp:" << temp << endl;		  
		}
		return v[aktuellbesterZug];
// 		std::copy(list.begin(), list.end(), v.begin());
// 		std::random_shuffle(v.begin(), v.end());
// 		return v[0]; // assumes that there was at least one valid move
	}
};

void print_position(pos p) {
	cout << p.a << " " << p.b << endl;
}

// suche mögliche Züge für
// 1 Kugel
int main(){

	field f = start_field();
	std::list<move> list;
	possible_moves(f, BLACK, &list);
	
	Uli_player Spieler1("Uli", BLACK);
	
	move m = Spieler1(f);
	
// 	move m;
// 	m.a.a = 5;
// 	m.a.b = 3;
// 	m.b.a = 6;
// 	m.b.b = 4;
// 	m.c.a = 7;
// 	m.c.b = 5;
// 	m.dir = 2;
	
	if (move_valid(m,f)) {
	cout << "valid move" << endl;
	}
	print_field(f);
	cout << "vor move"<< endl;
	do_move(f,m);
	cout << "nach move"<< endl;
	print_field(f);
return 0;
}




