#include <iostream>
#include "field.hh"
using namespace std;

bool check(pos a, pos b, pos tmp, pos dir, field &f);


bool move_valid(pos a, pos b, pos c, pos dir, field &f) {
	if(f.get_stone(a.a,a.b)==f.get_stone(b.a,b.b) 
      and f.get_stone(c.a,c.b)==f.get_stone(a.a,a.b)){ // Same colour
  pos dist=sub_pos(a,b);
  if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
     is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
  or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
    if ( is_equal(c, add_pos(a,dist) ) or is_equal(c, sub_pos(b,dist) ) ) {
        // 3 in a row
		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) { 
        // c is in front
        if ( is_equal(sub_pos(c,dir),a) or is_equal(sub_pos(c,dir),b) ) {
				cout<<"c is in front"<<endl;
				pos tmp = add_pos(c,dir);
        return check(a,b,tmp,dir,f);
			  }
        else{
        // c not in front
				pos tmp = add_pos(c,dir);
        tmp = add_pos(c,dir);
        tmp = add_pos(c,dir);
        return check(a,b,tmp,dir,f);
        }
      }
      else {
      // NonParallel
   			cout<<"NPARALLEL"<<endl;
				pos tmp = add_pos(a,dir);
				pos tmp2 = add_pos(b,dir);
				pos tmp3 = add_pos(c,dir);
				if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b) or 
            f.get_stone(tmp3.a,tmp3.b) ) return false;
				else return true;
			}
//			else return false;
    
      }
    }
  dist=sub_pos(b,c);
  if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
     is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
  or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
    if ( is_equal(a, add_pos(b,dist) ) or is_equal(a, sub_pos(c,dist) )   ) {
		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) {
      // Parallel, a is in front
        if ( is_equal(sub_pos(a,dir),b) or is_equal(sub_pos(a,dir),a) ) {
				cout<<"a is in front"<<endl;
				pos tmp = add_pos(c,dir);
        return check(a,b,tmp,dir,f);
			  }
        else{
				pos tmp = add_pos(c,dir);
        tmp = add_pos(c,dir);
        tmp = add_pos(c,dir);
        return check(a,b,tmp,dir,f);
        }
      }
      else {
      // NonParallel
   			cout<<"NPARALLEL"<<endl;
				pos tmp = add_pos(a,dir);
				pos tmp2 = add_pos(b,dir);
				pos tmp3 = add_pos(c,dir);
				if(f.get_stone(tmp.a,tmp.b) or f.get_stone(tmp2.a,tmp2.b) or 
            f.get_stone(tmp3.a,tmp3.b) ) return false;
				else return true;
      }
    }
  }

  } 
  else return false;
}

int main(){
//unitvec[6] = {{1,1},{0,1},{-1,0},{-1,-1},{0,-1},{1,0}};
}

bool check(pos a, pos b, pos tmp, pos dir, field &f){
				if(f.get_stone(tmp.a,tmp.b)) {
					//Case: 4 stones of same colour
					if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b)){
						return false;
					}
          else{
						tmp = add_pos(tmp,dir);
					  if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b) ){ 
            // zebra occupation
              return false;
            } 
            else{ 
              // Either different colour or empty
              tmp = add_pos(tmp,dir);
              if(f.get_stone(tmp.a,tmp.b)==f.get_stone(a.a,a.b) ){ 
              // Blocked from behind
                return false;
              }
              if(f.get_stone(tmp.a,tmp.b)) {
						  // 3 Stones against me
							  return false;
						  } 
 	          }
          }
        }
			  return true;
}
