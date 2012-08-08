#include <cmath>
#include <iostream>
#include "field.hh"
using namespace std;

void print_field(field Field){
	for(int i=1;i<N+1;i++){
		for(int k=0;k<abs(i-(N-1)/2-1);k++){
			cout <<" ";
		}
		for(int j=1;j<N+1;j++){
			if(abs(j-i)<5){
				cout << Field.get_stone(i,j);
				cout <<" ";
			}
		}
		
		cout<<endl;
	}
}

int main(){
	field Field;
	Field.set_stone(2,2,EMPTY);
	print_field(Field);
}
