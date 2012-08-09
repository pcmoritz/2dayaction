#include <iostream>
#include "field.hh"

// ein Kommentar

using namespace std;

double UH1_field(field& f, int player) {
	double Bewertung=0;
  	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j){
			if (f.get_stone(i, j)==1) {Bewertung+=1;}
			if (f.get_stone(i, j)==2) {Bewertung+=2;}
		}
		      
	}
return Bewertung;	
}



