#include <iostream>
#include "state.h"
#include <cstdlib>		// used for rand()

using namespace std;

// Map
void Map::set_length(int lngt) {
	length = lngt;
}

void Map::set_width(int wdt) {
	width = wdt;
}

void Map::set_time(bool a) {
	night = a;
}
int Map::get_length()const {
	return length;

}

int Map::get_width()const {
	return width;
}

bool Map::get_time()const {
	return night;
}

void Avatar::change(char b) {
	Point p = this->get_position();
	switch (b) {
	case 'w': p->y--;  this->set_position(p); break;
	case 's': p->y++;  this->set_position(p);  break;
	case 'd': p->x++;  this->set_position(p); break;
	case 'a': p->x--;  this->set_position(p); break;
	}
}

// Avatar
void Avatar::movement(State state, KeyState keys){
	Avatar* avatar = state->At.at(0);
	Point p = avatar->get_position();
	if (keys->up) {
		p->y--;													// might need some else if instead of if(to be fixed)
		avatar->set_position(p);
	}
	if (keys->down) {
		p->y++;
		avatar->set_position(p);
	}
	if (keys->left) {
		p->x--;
		avatar->set_position(p);
	}
	if (keys->right) {
		p->x++;
		avatar->set_position(p);
	}

}

// Creature
void Creature::movement(State state,int i, bool Wf) {
	//decide its movement + check that it does not go out of the map's border
	if (Wf == true) {
		Werewolf* w = state->Ww.at(i);
		Point place = w->get_position();
		int decide = rand() % 5;
		switch (decide) {
		case 0:
			if (place->x  < state->map->get_width() - 2) {
				place->x++;
				w->set_position(place);
			}
			break;
		case 1:
			if (place->x > 1) {
				place->x--;
				w->set_position(place);
			}	
			break;
		case 2:
			if (place->y < state->map->get_length() - 2) {
				place->y++;
				w->set_position(place);
			}
			break;
		case 3:
			if (place->y > 1) {
				place->y--;
				w->set_position(place);
			}
			break;
		case 4:
			//stand still
			break;
		}
		
	}
	else {
		Vampire* v = state->Vp.at(i);
		Point place = v->get_position();
		int decide = rand() % 9;
		switch (decide) {
		case 0:
			if (place->x < state->map->get_width() - 2) {
				place->x++;
				v->set_position(place);
			}
			break;
		case 1:
			if (place->x > 1) {
				place->x--;
				v->set_position(place);
			}
			break;
		case 2:
			if (place->y < state->map->get_length() - 2) {
				place->y++;
				v->set_position(place);
			}
			break;
		case 3:
			if (place->y > 1) {
				place->y--;
				v->set_position(place);
			}
			break;
		case 4:
			if (place->x < state->map->get_width() - 2 || place->y > 1) {
				place->x++;
				place->y--;
				v->set_position(place);
			}
			break;
		case 5:
			if (place->x < state->map->get_width() - 2 || place->y < state->map->get_length() - 2) {
				place->x++;
				place->y++;
				v->set_position(place);
			}
			break;
		case 6:
			if (place->x > 1 || place->y > 1) {
				place->x--;
				place->y--;
				v->set_position(place);
			}
			break;
		case 7:
			if (place->x > 1 || place->y < state->map->get_length() - 2) {
				place->x--;
				place->y++;
				v->set_position(place);
			}
			break;
		case 8:
			//do nothing
			break;
		}
	}
}

void Creature::set_position(Point pos) {
	position = pos;
}

Point Creature::get_position()const {
	return position;
}

// Object
void Object::set_position(Point pos) {
	position = pos;
}

Point Object::get_position()const {
	return position;
}

// Avatar
void Avatar::set_potions(int ptns) {
	potions = ptns;
}

int Avatar::get_potions()const {
	return potions;
}

void Avatar::help_W(Werewolf* werewolf) {						// Help creature werewolf by adding 1 more health value
	int prev_health = werewolf->get_health();
	if (prev_health < 2) {										// If health is not max
		werewolf->set_health(prev_health + 1);					// Then new health is previous value + 1
	}
}

void Avatar::help_V(Vampire* vampire) {							// Help creature vampire by adding 1 more health value
	int prev_health = vampire->get_health();
	if (prev_health < 2) {										// If health is not max
		vampire->set_health(prev_health + 1);					// Then new health is previous value + 1
	}
}

static void move_both(Werewolf* w, Vampire* v) {
	Point p1 = w->get_position();
	Point p2 = v->get_position();

	if (p1->x <= p2->x) {
		p1->x--;
		p2->x++;
	}
	if (p1->y <= p2->y) {
		p1->y--;
		p2->y++;
	}
	else if (p1->x >= p2->x) {
		p1->x++;
		p2->x--;
	}
	else if (p1->y >= p2->y) {
		p1->y++;
		p2->y--;
	}
}

static void move_both_2(Vampire* v, Werewolf* w) {
	Point p1 = w->get_position();
	Point p2 = v->get_position();

	if (p1->x <= p2->x) {
		p1->x--;
		p2->x++;
	}
	if (p1->y <= p2->y) {
		p1->y--;
		p2->y++;
	}
	else if (p1->x >= p2->x) {
		p1->x++;
		p2->x--;
	}
	else if (p1->y >= p2->y) {
		p1->y++;
		p2->y--;
	}
}

// Werewolf
void Werewolf::attack(Vampire* vampire) {
	int attack_value = this->get_strength();					// Strength value
	if (attack_value >= vampire->get_strength()) {				// If strength value is bigger that it's opponent's, attack
		int damage = this->get_strength() - vampire->get_defence();	// Damage value
		if (damage > 0) {										// If strength value is bigger than opponent's defence value
			vampire->set_health(vampire->get_health() - damage);
		}
	}
	//else {
		//move_both(this, vampire);
	//}
}

void Werewolf::help(Werewolf* werewolf) {
	int random = rand() % 2;									// Select randomly if a creature is going to help its ally
	switch (random) {
	case 0:
		if (this->get_health() > 1 && werewolf->get_health() < 2) {	// If health is >=2 and health of ally is not max=2
			werewolf->set_health(werewolf->get_health() + 1);	// Health of another creature +1
			this->set_health(this->get_health() - 1);			// Health of this creature -1
		}
		break;
	case 1:
		// do nothing
		break;
	}
}

void Werewolf::set_health(int h) {
	health = h;
}

void Werewolf::set_strength(int strng) {
	strength = strng;
}

void Werewolf::set_defence(int dfnc) {
	defence = dfnc;
}

int Werewolf::get_health()const {
	return health;
}

int Werewolf::get_strength()const {
	return strength;
}

int Werewolf::get_defence()const {
	return defence;
}

// Vampire
void Vampire::attack(Werewolf* werewolf) {
	int attack_value = this->get_strength();					// Strength value
	if (attack_value >= werewolf->get_strength()) {				// If strength value is bigger that it's opponent's, attack
		int damage = this->get_strength() - werewolf->get_defence();	// Damage value
		if (damage > 0) {										// If strength value is bigger than opponent's defence value
			werewolf->set_health(werewolf->get_health() - damage);
		}
	}
	//move_both_2(this, werewolf);
}

void Vampire::help(Vampire* vampire) {
	int random = rand() % 2;									// Select randomly if a creature is going to help its ally
	switch (random) {
	case 0:
		if (this->get_health() > 1 && vampire->get_health() < 2) {	// If health is >=2 and health of ally is not max=2
			vampire->set_health(vampire->get_health() + 1);		// Health of another creature +1
			this->set_health(this->get_health() - 1);			// Health of this creature -1
		}
		break;
	case 1:
		// do nothing
		break;
	}
}

void Vampire::set_health(int hlth) {
	health = hlth;
}

void Vampire::set_strength(int strng) {
	strength = strng;
}

void Vampire::set_defence(int dfnc) {
	defence = dfnc;
}

int Vampire::get_health()const {
	return health;
}

int Vampire::get_strength()const {
	return strength;
}

int Vampire::get_defence()const {
	return defence;
}

// Extra functions that create objects. They are used below in function: add()
// Creates a werewolf
static Werewolf* create_w(State state, int x, int y ) {
	Werewolf* w = new Werewolf;
	int health = (rand() % 2) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	w->set_health(health);
	w->set_strength(strength);
	w->set_defence(defense);
	w->set_position(position);

	return w;
}

// Creates a vampire
static Vampire* create_v(State state, int x, int y) {
	Vampire* v = new Vampire;
	int health = (rand() % 2) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	v->set_health(health);
	v->set_strength(strength);
	v->set_defence(defense);
	v->set_position(position);
											//nomizw edw tha prepei na kanoyme deallocate to position
	return v;								// + kapoious elegxous gia na min exei themata sto interface
}

// Creates avatar
static Avatar* create_avatar(State state, int x, int y) {
	Avatar* avatar = new Avatar;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	avatar->set_position(position);

	return avatar;
}

// Creates tree
static Tree* create_tree(State state, int x, int y) {
	Tree* tree = new Tree;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	tree->set_position(position);

	return tree;
}

// Creates water
static Water* create_water(State state, int x, int y) {
	Water* water = new Water;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	water->set_position(position);

	return water;
}

// Creates potion
static Potion* create_potion(State state, int x, int y) {
	Potion* potion = new Potion;
	Point position = new point;
	bool found = false;
	do {
		position->x = (rand() % (x - 2)) + 1;								// find one position
		position->y = (rand() % (y - 2)) + 1;
		for (int i = 0; i < state->Locations.size(); i++) {					// iterate vector with locations
			if (state->Locations.at(i)->x == position->x && state->Locations.at(i)->y == position->y) {					// if position already exists in vector
				found = true;												// make found true
				break;
			}
			else {
				found = false;												// if position does not already exists make found false
			}
		}
		if (found == false) {												// if found stayed false after the iteration
			state->Locations.push_back(position);							// then keep location in vector
		}

	} while (found);														// if a new location is found then stop searching where to place the object
	potion->set_position(position);

	return potion;
}

// Adds created objects in vectors
static void add(State state, int x, int y) {
	Avatar* avatar = create_avatar(state, x, y);	// Create Avatar
	state->At.push_back(avatar);
	for (int i = 0; i < x * y / 15; i++) {			// Create x*y/15 Werewolves and Vampires
		Werewolf* w = create_w(state, x,y);
		Vampire* v = create_v(state, x, y);
		state->Ww.push_back(w);
		state->Vp.push_back(v);

		state->info.number_V++;
		state->info.number_W++;


	}
	for (int i = 0; i < 5; i++) {					// Create i Trees and Water
		Tree* tree = create_tree(state, x, y);
		Water* water = create_water(state, x, y);

		state->Tr.push_back(tree);
		state->Wt.push_back(water);

	}
	Potion* potion = create_potion(state, x, y);	// Create potion

	state->Pt.push_back(potion);

}




// More
State state_create(Map* m) {
	state *s = new state;
	s->info.playing = true;
	s->info.paused = false;
	s->info.number_V = 0;
	s->info.number_W = 0;
	s->info.Team_W = false;
	s->map = m;
	s->map->set_length(m->get_length());
	s->map->set_width(m->get_width());
	s->map->set_time(m->get_time());



	add(s, s->map->get_width(), s->map->get_length());



	return s;
}

StateInfo state_info(State state) {
	return &state->info;
}


static void move_bothW(Werewolf* w1 , Werewolf* w2) {
	Point p1 = w1->get_position();
	Point p2 = w2->get_position();

	if(p1->x <= p2->x) {
		p1->x--;
		p2->x++;
	}
	if (p1->y <= p2->y) {
		p1->y--;
		p2->y++;
	}
	else if (p1->x >= p2->x) {
		p1->x++;
		p2->x--;
	}
	else if (p1->y >= p2->y) {
		p1->y++;
		p2->y--;
	}

}

static void move_bothV(Vampire* v1, Vampire* v2) {
	Point p1 = v1->get_position();
	Point p2 = v2->get_position();

	if (p1->x <= p2->x) {
		p1->x--;
		p2->x++;
	}
	if (p1->y <= p2->y) {
		p1->y--;
		p2->y++;
	}
	else if (p1->x >= p2->x) {
		p1->x++;
		p2->x--;
	}
	else if (p1->y >= p2->y) {
		p1->y++;
		p2->y--;
	}
}

static void move_away(Werewolf* w, Point point) {
	Point p1 = w->get_position();

	if (p1->x <= point->x) {
		p1->x--;
	}
	if (p1->y <= point->y) {
		p1->y--;
	}
	else if (p1->x >= point->x) {
		p1->x++;
	}
	else if (p1->y >= point->y) {
		p1->y++;
	}
}

static void move_awayV(Vampire* v, Point point) {
	Point p1 = v->get_position();

	if (p1->x <= point->x) {
		p1->x--;
	}
	if (p1->y <= point->y) {
		p1->y--;
	}
	else if (p1->x >= point->x) {
		p1->x++;
	}
	else if (p1->y >= point->y) {
		p1->y++;
	}
}




void state_update(State state, Avatar* avatar) {
	if (state->info.playing) {
			//avatar->movement(state, keys);		//thelei virtual,simadiko isws xreiastei allagi(idea: tou creature
												//h movement na einai virtual kai na exei thn kinhsh toy werewolf

			for (int i = 0; i < state->Ww.size(); i++) {
				Werewolf* w = state->Ww.at(i);
				Point p1 = w->get_position();
				w->movement(state, i, true);					//true for w , false for v thelei alli methodo tha to skefto meta
				for (int k = 0; k < state->Ww.size(); k++) {
					Werewolf* w_2 = state->Ww.at(k);
					Point p2 = w_2->get_position();
					if (abs(p1->x - p2->x) <= 1 && abs(p1->y - p2->y) <= 1) {
						if (w == w_2) { continue; }			//it may be wrong , we'll see
						else {
							w->help(w_2);
							w_2->movement(state, k, true);
							//move_bothW(w, w_2);
						}
					}
				}
				for (int c = 0; c < state->Tr.size(); c++) {
					Tree* tree = state->Tr.at(c);
					Point p = tree->get_position();
					//if (abs(p1->x - p->x) <= 1 && abs(p1->y - p->y) <= 1) {
						//move_away(w, p);
					//}
				}
				for (int c = 0; c < state->Wt.size(); c++) {
					Water* water = state->Wt.at(c);
					Point pp = water->get_position();
					//if (abs(p1->x - pp->x) <= 1 && abs(p1->y - pp->y) <= 1) {
						//move_away(w, pp);
					//}
				}
				for (int j = 0; j < state->Vp.size(); j++) {
					Vampire* vp = state->Vp.at(j);
					Point p3 = vp->get_position();
					if (abs(p1->x - p3->x) <= 1 && abs(p1->y - p3->y) <= 1) {
						w->attack(vp);
						if ((vp->get_health()) == 0) {
							if (j == 0) {
								state->Vp.erase(state->Vp.begin() + j );
							}
							else state->Vp.erase(state->Vp.begin() + j - 1);
							//deallocation of pointers , destructors, delete etc
						}
						//vp->movement(state, j, false); //isws na mh xreiazetai
					}
				}
			}

			for (int i = 0; i < state->Vp.size(); i++) {
				Vampire* v = state->Vp.at(i);
				Point p4 = v->get_position();
				v->movement(state, i, false); //0 for w , 1 for v thelei alli methodo tha to skefto meta

				for (int a = 0; a < state->Vp.size(); a++) {
					Vampire* vv = state->Vp.at(a);
					Point p5 = vv->get_position();
					if (abs(p4->x - p5->x) <= 1 && abs(p4->y - p5->y) <= 1) {
						if (v == vv) { continue; }			//it may be wrong , we'll see
						else {
							v->help(vv);
							//move_bothV(v, vv);
							//vv->movement(state, a, false);
						}
					}
				}
				for (int c = 0; c < state->Tr.size(); c++) {
					Tree* tree = state->Tr.at(c);
					Point p = tree->get_position();
					//if (abs(p4->x - p->x) <= 1 && abs(p4->y - p->y) <= 1) {
						//move_awayV(v, p);
					//}
				}
				for (int c = 0; c < state->Wt.size(); c++) {
					Water* water = state->Wt.at(c);
					Point pp = water->get_position();
					//if (abs(p4->x - pp->x) <= 1 && abs(p4->y - pp->y) <= 1) {
					//	move_awayV(v, pp);
					//}
				}
				for (int b = 0; b < state->Ww.size(); b++) {
					Werewolf* wolf= state->Ww.at(b);
					Point p6 = wolf->get_position();
					if (abs(p4->x - p6->x) <= 1 && abs(p4->y - p6->y) <= 1) {
						v->attack(wolf);
						if ((wolf->get_health()) == 0) {
							if (b == 0) {
								state->Ww.erase(state->Ww.begin() + b);
							}
							else state->Ww.erase(state->Ww.begin() + b - 1);
							//same as Vp
						}
						//wolf->movement(state, b, false); //isws na mh xreiazetai
					}
				}
			}

			 



	}
}

