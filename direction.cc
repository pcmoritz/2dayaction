#include <iostream>
#include "field.hh"

using namespace std;

const pos unitvec[6] = {{1,1},{0,1},{-1,0},{-1,-1},{0,-1},{1,0}};

bool is_equal(pos a, pos b) {
	if(a.a==b.a&& a.b ==b.b) return true;
	else return false;
}

pos add_pos(pos a, pos b){
	pos c;
	c.a = a.a+b.a;
	c.b = a.b+b.b;
	return c;
}
pos sub_pos(pos a, pos b){
	pos c;
	c.a = a.a-b.a;
	c.b = a.b-b.b;
	return c;
}
pos inv_dir(pos a){
	pos c;
	c.a = -a.a;
	c.b = -a.b;
	return c;
}

// bool move_valid(move Move, field &f) {
//   if (!is_equal(Move.c,not_a_position) )  return move_valid(Move.a,Move.b,Move.c,
//     unitvec[Move.dir], f);
//   if (!is_equal(Move.b,not_a_position))  return move_valid(Move.a,Move.b,
//     unitvec[Move.dir], f);  
//   return move_valid(Move.a, unitvec[Move.dir], f);
// }


bool move_valid(pos a, pos dir,field &f) {
	if(f.get_stone(add_pos(a,dir).a,add_pos(a,dir).b)) return false;
	else return true;
}

bool move_valid(pos a, pos b,pos dir,field &f) {
	if(f.get_stone(a.a,a.b)==f.get_stone(b.a,b.b)){

		pos c = sub_pos(a,b);
		if(is_equal(c,dir) or is_equal(inv_dir(c),dir)) {
			//CASE: PARALLEL
		
			if(is_equal(add_pos(b,dir),a)) {
				//a is in front
				//cout<<"a is in front"<<endl;
				pos tmp = add_pos(a,dir);
				if(f.get_stone(tmp.a,tmp.b)) {
					//Case: 3 stones of same colour
					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
						return false;
					}else{

						tmp = add_pos(tmp,dir);
						if(f.get_stone(tmp.a,tmp.b)) {
						//double occupation
							return false;
						}
				
						//PUSH

						return true;
					}
				}
				//Next neighbor not occupied
				return true;
			}else{
				//b is in front
				//cout<<"b is in front"<<endl;
				pos tmp = add_pos(b,dir);
				if(f.get_stone(tmp.a,tmp.b)) {
					//Case: 3 stones of same colour
					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
						return false;
					}else{

						tmp = add_pos(tmp,dir);
						if(f.get_stone(tmp.a,tmp.b)) {
						//double occupation
							return false;
						}
				
						//PUSH

						return true;
					}
				}
				//Next neighbor not occupied
				return true;

			}

		}else{
			//cout<<"NPARALLEL"<<endl;
			pos dist = sub_pos(a,b);
			if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
			or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)) {
				pos tmp = add_pos(a,dir);
				pos tmp2 = add_pos(b,dir);
				if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b)) return false;
				else return true;
			}
			else return false;
			
		}
	}else return false;
}

bool check(pos a, pos b, pos tmp, pos dir, field &f);


// bool move_valid(pos a, pos b, pos c, pos dir, field &f) {
// 	if(f.get_stone(a.a,a.b)==f.get_stone(b.a,b.b) 
//       and f.get_stone(c.a,c.b)==f.get_stone(a.a,a.b)){ // Same colour
//   pos dist=sub_pos(a,b);
//   if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
//      is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
//   or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
//     if ( is_equal(c, add_pos(a,dist) ) or is_equal(c, sub_pos(b,dist) ) ) {
//         // 3 in a row
// 		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) { 
//         // parallel
//         if ( is_equal(sub_pos(c,dir),a) or is_equal(add_pos(c,dir),b) ) {
//         // cout<<"c is in front"<<endl;
// 				pos tmp = add_pos(c,dir);
//         return check(a,b,tmp,dir,f);
// 			  }
//         else{
//         // c not in front
// 				pos tmp = add_pos(c,dir);
//         tmp = add_pos(c,dir);
//         tmp = add_pos(c,dir);
//         return check(a,b,tmp,dir,f);
//         }
//       }
//       else {
//       // NonParallel
//    			//cout<<"NPARALLEL"<<endl;
// 				pos tmp = add_pos(a,dir);
// 				pos tmp2 = add_pos(b,dir);
// 				pos tmp3 = add_pos(c,dir);
// 				if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b) or 
//             f.get_stone(tmp3.a,tmp3.b) ) return false;
// 				else return true;
// 			}
// //			else return false;
    
//       }
//     }
//   dist=sub_pos(b,c);
//   if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
//      is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
//   or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
//     if ( is_equal(a, add_pos(b,dist) ) or is_equal(a, sub_pos(c,dist) )   ) {
// 		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) {
//       // Parallel, a is in front
//         if ( is_equal(sub_pos(a,dir),b) or is_equal(sub_pos(a,dir),a) ) {
// 				cout<<"a is in front"<<endl;
// 				pos tmp = add_pos(c,dir);
//         return check(a,b,tmp,dir,f);
// 			  }
//         else{
// 				pos tmp = add_pos(c,dir);
//         tmp = add_pos(c,dir);
//         tmp = add_pos(c,dir);
//         return check(a,b,tmp,dir,f);
//         }
//       }
//       else {
//       // NonParallel
//    			cout<<"NPARALLEL"<<endl;
// 				pos tmp = add_pos(a,dir);
// 				pos tmp2 = add_pos(b,dir);
// 				pos tmp3 = add_pos(c,dir);
// 				if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b) or 
//             f.get_stone(tmp3.a,tmp3.b) ) return false;
// 				else return true;
//       }
//     }
//   }

//   } 
//   else return false;
// }

// bool check(pos a, pos b, pos tmp, pos dir, field &f){
// 				if(f.get_stone(tmp.a,tmp.b)) {
// 					//Case: 4 stones of same colour
// 					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
// 						return false;
// 					}
//           else{
// 						tmp = add_pos(tmp,dir);
// 					  if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b) ){ 
//             // zebra occupation
//               return false;
//             } 
//             else{ 
//               // Either different colour or empty
//               tmp = add_pos(tmp,dir);
//               if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b) ){ 
//               // Blocked from behind
//                 return false;
//               }
//               if(f.get_stone(tmp.a,tmp.b)) {
// 						  // 3 Stones against me
// 							  return false;
// 						  } 
//  	          }
//           }
//         }
//         else{ 
//           return true;
//         }
// }

bool is_pos_inside(pos a) {
		return (a.a > 0) && (a.b > 0) && (a.a < 10) && (a.b < 10) &&
			(std::abs((long)(a.a-a.b)) < 5);
	}


bool is_over_bord(move Move) {
	pos tmp = Move.a;
	pos dir = unitvec[Move.dir];
	tmp = add_pos(tmp,dir);
	//
	if(is_pos_inside(tmp)){
		pos tmp2 = Move.b;
      //cout << "1 is inside"<<endl;

		if(is_valid_pos(tmp2)) {
			tmp2 = add_pos(tmp2,dir);

			if(is_pos_inside(tmp2)) {
				pos tmp3 = Move.c;
				//cout << "2 is inside"<<endl;

				if(is_valid_pos(tmp3)) {
					tmp3 = add_pos(tmp3,dir);

					if(is_pos_inside(tmp3)) {
						return false;
					}else return true;

				}else return false;

			} else return true;
		}
		else return false;
	}
	else return true;
}
 /*int main(){
 	field Feld;
 	Feld.set_stone(5,4,EMPTY);
 	Feld.set_stone(5,2,EMPTY);

	// Feld.set_stone(4,3,BLACK);
	// Feld.set_stone(4,2,BLACK);
	// pos b = {4,3};
	// pos a = {4,2};

// 	cout << move_valid(a,b,unitvec[0],Feld)<<endl;
 }*/
