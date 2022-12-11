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

// Checks if there is any object or creature and updates struct with souroundings properly
static void check(State state, Creature* c) {
	Point p = c->get_position();
	S s = c->get_sour();
	for (int i = 0; i < state->Locations.size(); i++) {
		Point pp = state->Locations.at(i);
		if (p->x == (pp->x - 1) && p->y == pp->y)
			s->right = true;			// he's on the right

		if (p->x == (pp->x + 1) && p->y == pp->y)
			s->left = true;				//he's on the left

		if (p->x == pp->x && p->y == (pp->y - 1))
			s->down = true;				//he's below

		if (p->x == pp->x && p->y == (pp->y + 1))
			s->up = true;				//he's above

		if (p->x == (pp->x - 1) && p->y == (pp->y + 1))
			s->upper_r = true;			//he's upper right

		if (p->x == (pp->x + 1) && p->y == (pp->y + 1))
			s->upper_l = true;			//he's upper left

		if (p->x == (pp->x + 1) && p->y == (pp->y - 1))
			s->lower_l = true;			//he's lower left

		if (p->x == (pp->x - 1) && p->y == (pp->y - 1))
			s->lower_r = true;			//he's lower right

	}
	c->set_sour(s);
}

// Returns struct with sourounding to original form
static void reload(State state, Creature* cr) {
	S s = cr->get_sour();
	s->right = false;
	s->left = false;
	s->up = false;
	s->down = false;
	s->upper_r = false;
	s->upper_l = false;
	s->lower_l = false;
	s->lower_r = false;
	cr->set_sour(s);
}

// Moves creature
static void move(Creature* cr, State state,int i) {
	reload(state, cr);
	check(state, cr);
	cr->movement(state, i);
}



// Creature
void Creature::movement(State state,int i) {
	//decide its movement + check that it does not go out of the map's border
	Werewolf* w = state->Ww.at(i);
	Point place = w->get_position();
	S s = w->get_sour();
	int decide = rand() % 5;
	switch (decide) {
	case 0:
		if (place->x  < state->map->get_width() - 2 && s->right == false) {
			place->x++;
			w->set_position(place);
		}
		break;
	case 1:
		if (place->x > 1 && s->left == false) {
			place->x--;
			w->set_position(place);
		}	
		break;
	case 2:
		if (place->y < state->map->get_length() - 2 && s->down == false ) {
			place->y++;
			w->set_position(place);
		}
		break;
	case 3:
		if (place->y > 1 && s->up == false) {
			place->y--;
			w->set_position(place);
		}
		break;
	case 4:
		//stand still
		break;
	}
}

void Creature::set_sour(S surroundings) {
	sour = surroundings;
}

S Creature::get_sour()const {
	return sour;
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
void Avatar::movement(State state, char b) {
	reload(state, this);
	check(state, this);
	S s = this->get_sour();
	Point p = this->get_position();
	if (state->Pt.size() > 0) {
		Point potion_p = state->Pt.at(0)->get_position();
		switch (b) {
		case 'w':
			if (p->y > 1 && (s->up == false || p->y == potion_p->y + 1)) {
				p->y--;							// up
				this->set_position(p);
				break;
			}
		case 's':
			if (p->y < state->map->get_length() - 2 && (s->down == false || p->y == potion_p->y - 1)) {
				p->y++;							// down
				this->set_position(p);
				break;
			}
		case 'd':
			if (p->x < state->map->get_width() - 2 && (s->right == false || p->x == potion_p->x - 1)) {
				p->x++;							// right
				this->set_position(p);
				break;
			}
		case 'a':
			if (p->x > 1 && (s->left == false || p->x == potion_p->x + 1)) {
				p->x--;							// left
				this->set_position(p);
				break;
			}
		}
	}
	else {
		switch (b) {
		case 'w':
			if (p->y > 1 && s->up == false) {
				p->y--;							// up
				this->set_position(p);
				break;
			}
		case 's':
			if (p->y < state->map->get_length() - 2 && s->down == false) {
				p->y++;							// down
				this->set_position(p);
				break;
			}
		case 'd':
			if (p->x < state->map->get_width() - 2 && s->right == false) {
				p->x++;							// right
				this->set_position(p);
				break;
			}
		case 'a':
			if (p->x > 1 && s->left == false ) {
				p->x--;							// left
				this->set_position(p);
				break;
			}
		}
	}
	this->set_sour(s);
}

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

// Werewolf
void Werewolf::attack(Vampire* vampire) {
	int attack_value = this->get_strength();					// Strength value
	if (attack_value >= vampire->get_strength()) {				// If strength value is bigger that it's opponent's, attack
		int damage = this->get_strength() - vampire->get_defence();	// Damage value
		if (damage > 0) {										// If strength value is bigger than opponent's defence value
			vampire->set_health(vampire->get_health() - damage);
		}
	}
}

void Werewolf::help(Werewolf* werewolf) {
	int random = rand() % 2;									// Select randomly if a creature is going to help its ally
	switch (random) {
	case 0:
		if (this->get_medkit() > 0 && werewolf->get_health() < 5) {	// If number of medkit is >0 and health of ally is not max=5
			werewolf->set_health(werewolf->get_health() + 1);	// Health of another creature +1
			this->set_medkit(this->get_medkit() - 1);			// Medkit of this creature -1
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

void Werewolf::set_medkit(int mdkt) {
	medkit = mdkt;
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

int Werewolf::get_medkit()const {
	return medkit;
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
}

void Vampire::help(Vampire* vampire) {
	int random = rand() % 2;									// Select randomly if a creature is going to help its ally
	switch (random) {
	case 0:
		if (this->get_medkit() > 0 && vampire->get_health() < 5) {	// If number of medkit is >0 and health of ally is not max=5
			vampire->set_health(vampire->get_health() + 1);		// Health of another creature +1
			this->set_medkit(this->get_medkit() - 1);			// Medkit of this creature -1
		}
		break;
	case 1:
		// do nothing
		break;
	}
}

void Vampire::movement(State state, int i) {
	Vampire* v = state->Vp.at(i);
	Point place = v->get_position();
	S s = v->get_sour();
	int decide = rand() % 9;
	switch (decide) {
	case 0:
		if (place->x < state->map->get_width() - 2 && s->right == false) {
			place->x++;
			v->set_position(place);
		}
		break;
	case 1:
		if (place->x > 1 && s->left == false) {
			place->x--;
			v->set_position(place);
		}
		break;
	case 2:
		if (place->y < state->map->get_length() - 2 && s->down == false) {
			place->y++;
			v->set_position(place);
		}
		break;
	case 3:
		if (place->y > 1 && s->up == false) {
			place->y--;
			v->set_position(place);
		}
		break;

	case 4:
		if ((place->x < state->map->get_width() - 2 && place->y > 1) && s->upper_r == false) {
			place->x++;
			place->y--;
			v->set_position(place);
		}
		break;
	case 5:
		if ((place->x < state->map->get_width() - 2 && place->y < state->map->get_length() - 2) && s->lower_r == false) {
			place->x++;
			place->y++;
			v->set_position(place);
		}
		break;
	case 6:
		if ((place->x > 1 && place->y > 1) && s->upper_l == false) { 
			place->x--;
			place->y--;
			v->set_position(place);
		}
		break;
	case 7:
		if ((place->x > 1 && place->y < state->map->get_length() - 2) && s->lower_l == false) {
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

void Vampire::set_health(int hlth) {
	health = hlth;
}

void Vampire::set_strength(int strng) {
	strength = strng;
}

void Vampire::set_defence(int dfnc) {
	defence = dfnc;
}

void Vampire::set_medkit(int mdkt) {
	medkit = mdkt;
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

int Vampire::get_medkit()const {
	return medkit;
}

// Extra functions that create objects. They are used below in function: add()
// Creates a werewolf
static Werewolf* create_w(State state, int x, int y ) {
	Werewolf* w = new Werewolf;
	S sour = new surroundings;
	int health = (rand() % 5) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	int medkit = (rand() % 3);
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
	w->set_sour(sour);
	w->set_health(health);
	w->set_strength(strength);
	w->set_defence(defense);
	w->set_medkit(medkit);
	w->set_position(position);

	return w;
}

// Creates a vampire
static Vampire* create_v(State state, int x, int y) {
	Vampire* v = new Vampire;
	S sour = new surroundings;
	int health = (rand() % 5) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	int medkit = (rand() % 3);
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
	v->set_medkit(medkit);
	v->set_position(position);
	v->set_sour(sour);
											//nomizw edw tha prepei na kanoyme deallocate to position
	return v;								// + kapoious elegxous gia na min exei themata sto interface
}

// Creates avatar
static Avatar* create_avatar(State state, int x, int y) {
	Avatar* avatar = new Avatar;
	Point position = new point;
	S sour = new surroundings;
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
	avatar->set_sour(sour);
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

void state_update(State state) {
	if (state->info.playing) {
		Avatar* avatar = state->At.at(0);
		Point avatar_pos = avatar->get_position();
		if (state->Pt.size() > 0) {
			Potion* potion = state->Pt.at(0);
			Point potion_pos = potion->get_position();
			if (avatar_pos->x == potion_pos->x && avatar_pos->y == potion_pos->y) {
				avatar->set_potions(avatar->get_potions() + 1);
				for (int l = 0; l < state->Locations.size(); l++) {
					if (potion_pos == state->Locations.at(l)) {
						state->Locations.erase(state->Locations.begin() + l);
						break;
					}
				}
				state->Pt.erase(state->Pt.begin());
			}
		}

		for (int i = 0; i < state->Ww.size(); i++) {
			Werewolf* w = state->Ww.at(i);
			Point p1 = w->get_position();
			for (int k = 0; k < state->Ww.size(); k++) {
				Werewolf* w_2 = state->Ww.at(k);
				Point p2 = w_2->get_position();
				if (abs(p1->x - p2->x) <= 1 && abs(p1->y - p2->y) <= 1) {
					if (w == w_2) { continue; }			
					else {
						w->help(w_2);
						move(w_2, state, k);
					}
				}
				else {
					move(w, state, i);
				}
			}
			for (int j = 0; j < state->Vp.size(); j++) {
				Vampire* vp = state->Vp.at(j);
				Point p3 = vp->get_position();
				if (abs(p1->x - p3->x) <= 1 && abs(p1->y - p3->y) <= 1) {
					w->attack(vp);
					move(vp, state, j);
					if ((vp->get_health()) <= 0) {
						for (int l = 0; l < state->Locations.size(); l++) {
							if (p3 == state->Locations.at(l)) {
								state->Locations.erase(state->Locations.begin() + l);
								break;
							}
						}
						state->Vp.erase(state->Vp.begin() + j );
						state->info.number_V--;
						if (state->info.number_V == 0) {
							state->info.playing = false;
						}
						//deallocation of pointers , destructors, delete etc
					}
				}
				else {
					move(w, state, i);
				}
			}
		}

		for (int i = 0; i < state->Vp.size(); i++) {
			Vampire* v = state->Vp.at(i);
			Point p4 = v->get_position();
			for (int a = 0; a < state->Vp.size(); a++) {
				Vampire* vv = state->Vp.at(a);
				Point p5 = vv->get_position();
				if (abs(p4->x - p5->x) <= 1 && abs(p4->y - p5->y) <= 1) {
					if (v == vv) { continue; }			
					else {
						v->help(vv);
						move(vv, state, i);
					}
				}
				else {
					move(v, state, i);
				}
			}
			for (int b = 0; b < state->Ww.size(); b++) {
				Werewolf* wolf= state->Ww.at(b);
				Point p6 = wolf->get_position();
				if (abs(p4->x - p6->x) <= 1 && abs(p4->y - p6->y) <= 1) {
					v->attack(wolf);
					move(wolf, state, b);
					if ((wolf->get_health()) <= 0) {
						for (int l = 0; l < state->Locations.size(); l++) {
							if (p6 == state->Locations.at(l)) {
								state->Locations.erase(state->Locations.begin() + l);
								break;
							}
						}
						state->Ww.erase(state->Ww.begin() + b);
						state->info.number_W--;
						if (state->info.number_W == 0) {
							state->info.playing = false;
						}
					}
				}
				else {
					move(v, state, i);
				}
			}
		}
		
	}
}

// Functions that are used in main() in order to print the game and it's main menu
// Print board of game, creatures, objects
void board(int x, int y, State state) {
	bool printed;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			printed = false;
			if (i == 0 || i == y - 1) {
				cout << "#";
				printed = true;
			}
			if (i != 0 && i != y - 1 && (j == x - 1 || j == 0)) {
				cout << "#";
				printed = true;
			}
			for (int k = 0; k < state->Ww.size(); k++) {
				if (i == state->Ww.at(k)->get_position()->y && j == state->Ww.at(k)->get_position()->x) {
					cout << 'w';
					printed = true;
					break;
				}
			}
			for (int k = 0; k < state->Vp.size(); k++) {
				if (i == state->Vp.at(k)->get_position()->y && j == state->Vp.at(k)->get_position()->x) {
					cout << 'v';
					printed = true;
					break;
				}
			}
			if (i == state->At.at(0)->get_position()->y && j == state->At.at(0)->get_position()->x) {
				cout << "A";
				printed = true;
			}
			for (int k = 0; k < state->Tr.size(); k++) {
				if (i == state->Tr.at(k)->get_position()->y && j == state->Tr.at(k)->get_position()->x) {
					cout << "T";
					printed = true;
					break;
				}
			}
			for (int k = 0; k < state->Wt.size(); k++) {
				if (i == state->Wt.at(k)->get_position()->y && j == state->Wt.at(k)->get_position()->x) {
					cout << "W";
					printed = true;
					break;
				}
			}
			if (state->Pt.size() > 0) {
				if (i == state->Pt.at(0)->get_position()->y && j == state->Pt.at(0)->get_position()->x) {
					cout << "P";
					printed = true;
				}
			}
			if (printed == false)
				cout << " ";

		}
		cout << endl;

	}
}

// Prints menu of game and shows game information
void menu(State state) {
	int werewolves_left = state->info.number_W;
	int vampires_left = state->info.number_V;
	int potions_left = state->At.at(0)->get_potions();
	cout << "~MAIN MENU~" << endl << "Werewolves left: " << werewolves_left << endl << "Vampires left: " << vampires_left << endl;
	cout << "Potions left: " << potions_left << endl;
	cout << "*press 'p' to continue or press 'q' to exit game*" << endl;
}

