#include "field.hh"
#include <vector>

struct subfield {
  pos a,b,c,d,e,f;
  stone A,B,C,D,E,F;
	subfield(){
		a = not_a_position;
		b = not_a_position;
		c = not_a_position;
		d = not_a_position;
		e = not_a_position;
		f = not_a_position;
    A = EMPTY;
    B = EMPTY;
    C = EMPTY;
    D = EMPTY;
    E = EMPTY;
    F = EMPTY;
	}
};

struct listmove {
  std::vector<pos> list; 
	int dir;
};

listmove convert2list(move m) {
  listmove Listmove;
  if (!is_equal(m.c,not_a_position) ) Listmove.list.push_back(m.c);
  if (!is_equal(m.b,not_a_position) ) Listmove.list.push_back(m.b);
  Listmove.list.push_back(m.a);
  Listmove.dir=m.dir;
  return Listmove;
}

move convert2unsorted(listmove m) {
  move M;
  if (m.list.size()>2) {M.c=m.list[2];}
  if (m.list.size()>1) {M.b=m.list[1];}
  if (m.list.size()>0) {M.a=m.list[0];}
  return M;
}

bool in_front(int nr, listmove m){
}

void do_move(field& f, move m) {
	// first try if the move is valid... (to be implemented)
  subfield oldfield;
  oldfield.a=m.a;
  oldfield.b=m.b;
  oldfield.c=m.c;
	
	pos a = m.a;
	pos b = m.b;
	pos c = m.c;
	int dir = m.dir;
	pos temp = a;
	pos backtemp = a;
	stone player = f.get_stone(a.a, a.b);
	
	// suche nach erster freien Position in dir
	
	do {
	  temp = add_pos(temp, unitvec[dir]);
	} while (f.get_stone(temp.a,temp.b) != 0);
	
	// verschiebe alle Steine bis Pos a
	while (not (is_equal(temp,a))) {
	  backtemp = sub_pos(temp, unitvec[dir]);
	  f.set_stone(temp.a, temp.b, f.get_stone(backtemp.a,backtemp.b));
	  temp = sub_pos(temp, unitvec[dir]);
	}; 
	
	// verschiebe die drei Steine
	pos next_a = add_pos(a, unitvec[dir]);
	pos next_b = add_pos(b, unitvec[dir]);
	pos next_c = add_pos(c, unitvec[dir]);
	
	// zero the old positions
	if(is_valid_pos(a))
		f.set_stone(a.a, a.b, EMPTY);
	if(is_valid_pos(b))
		f.set_stone(b.a, b.b, EMPTY);
	if(is_valid_pos(c))
		f.set_stone(c.a, c.b, EMPTY);
	
	// set new positions
	if(is_valid_pos(a))
		f.set_stone(next_a.a, next_a.b, player);
	if(is_valid_pos(b))
		f.set_stone(next_b.a, next_b.b, player);
	if(is_valid_pos(c))
		f.set_stone(next_c.a, next_c.b, player);
}

int main() {
	move m;
	m.a.a = 5;
	m.a.b = 3;
	m.b.a = 6;
	m.b.b = 4;
	m.c.a = 7;
	m.c.b = 5;
	m.dir = 2;
  listmove M=convert2list(m);
  print_move(convert2unsorted(M));
}
