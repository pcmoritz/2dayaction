#include <iostream>
#include "field.hh"
using namespace std;
pos unitvec[6] = {{1,1},{0,1},{-1,0},{-1,-1},{0,-1},{1,0}};

bool check(pos a, pos b, pos tmp, pos dir, field &f);

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

bool move_valid(pos a, pos dir,field &f) {
	if(f.get_stone(add_pos(a,dir).a,add_pos(a,dir).b)) return false;
	else return true;
}

bool move_valid(pos a, pos b, pos c, pos dir, field &f) {
	if(f.get_stone(a.a,a.b)==f.get_stone(b.a,b.b) 
      and f.get_stone(c.a,c.b)==f.get_stone(a.a,a.b)){
  dist=sub_pos(a,b);
  if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
     is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
  or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
    if ( is_equal(c, add_pos(a,dist) ) or is_equal(c, sub_pos(b,dist) ) ) {
		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) {
      // Parallel, c is in front
        if ( is_equal(sub_pos(c,dir),a) or is_equal(sub_pos(c,dir),b) ) {
				cout<<"c is in front"<<endl;
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
      }
    }
  } 
  dist=sub_pos(b,c);
  if(is_equal(unitvec[0],dist) or is_equal(unitvec[1],dist) or 
     is_equal(unitvec[2],dist) or is_equal(unitvec[3],dist)
  or is_equal(unitvec[4],dist) or is_equal(unitvec[5],dist)){
    if ( is_equal(a, sub_pos(b,dist) ) or is_equal(a, add_pos(a,dist) )   ) {
		  if(is_equal(dist,dir) or is_equal(dist,inv_dir(dir)) ) {
      // Parallel, c is in front
        if ( is_equal(sub_pos(c,dir),a) or is_equal(sub_pos(c,dir),b) ) {
				cout<<"c is in front"<<endl;
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
      }
    }
  }

  }
  else return false;
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
