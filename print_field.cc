#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include "field.hh"
using namespace std;

const int RED = 0;
const int BLUE = 1;

std::string number_to_string(int num) {
	ostringstream convert;
	convert << num;
	return std::string(convert.str());
}

void print_color(std::string t, int color) {
	cout << std::string("\033[1;3") + number_to_string(color) + "m"
		+ t + std::string("\033[0m");
}

void print_field(field Field){
	for(int i=1;i<N+1;i++){
		for(int k=0;k<abs(i-(N-1)/2-1);k++){
			cout <<"  ";
		}
		for(int j=1;j<N+1;j++){
			if(abs(j-i)<5){
				print_color(number_to_string(i) + number_to_string(j),
										Field.get_stone(i,j));
				cout << " ";
			}
		}
		
		cout<<endl;
	}
}
