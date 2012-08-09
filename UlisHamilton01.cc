#include <iostream>
#include "field.hh"

// ein Kommentar

using namespace std;

double UH1(field& f, int player) {
	double Bewertung=0;
  	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j){
			if (f.get_stone(i, j)==1) {Bewertung+=2;}
			if (f.get_stone(i, j)==2) {Bewertung+=-1;}
		}
		      
	}
return Bewertung;	
}



