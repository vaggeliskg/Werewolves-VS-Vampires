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
			place->x++;
			w->set_position(place);
			break;
		case 1:
			place->x--;
			w->set_position(place);
			break;
		case 2:
			place->y++;
			w->set_position(place);
			break;
		case 3:
			place->y--;
			w->set_position(place);
			break;
		case 4:
			//stand still
			break;
		}
		
	}
	else {
		Vampire* v = state->Vp.at(i);
		Point place = v->get_position();
		int decide = rand() % 5;
		switch (decide) {
		case 0:
			place->x++;
			v->set_position(place);
			break;
		case 1:
			place->x--;
			v->set_position(place);
			break;
		case 2:
			place->y++;
			v->set_position(place);
			break;
		case 3:
			place->y--;
			v->set_position(place);
			break;
		case 4:
			//stand still
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

// Werewolf
void Werewolf::attack(Vampire* vampire) {
	int attack_value = this->get_strength();					// Strength value
	if (attack_value >= vampire->get_strength()) {				// If strength value is bigger that it's opponent's, attack
		int damage = this->get_strength() - vampire->get_defence();	// Damage value
		if (damage > 0) {										// If strength value is bigger than opponent's defence value
			vampire->set_health(vampire->get_health() - damage);
		}
	}
	// Else go away
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
	// else go away
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
static Werewolf* create_w(int x, int y ) {
	Werewolf* w = new Werewolf;
	int health = (rand() % 2) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	w->set_health(health);
	w->set_strength(strength);
	w->set_defence(defense);
	w->set_position(position);

	return w;
}

// Creates a vampire
static Vampire* create_v(int x, int y) {
	Vampire* v = new Vampire;
	int health = (rand() % 2) + 1;
	int strength = (rand() % 3) + 1;
	int defense = (rand() % 2) + 1;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
 	position->y = (rand() % y) + (y / 4);
	v->set_health(health);
	v->set_strength(strength);
	v->set_defence(defense);
	v->set_position(position);
											//nomizw edw tha prepei na kanoyme deallocate to position
	return v;								// + kapoious elegxous gia na min exei themata sto interface
}

// Creates avatar
static Avatar* create_avatar(int x, int y) {
	Avatar* avatar = new Avatar;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	avatar->set_position(position);

	return avatar;
}

// Creates tree
static Tree* create_tree(int x, int y) {
	Tree* tree = new Tree;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	tree->set_position(position);

	return tree;
}

// Creates water
static Water* create_water(int x, int y) {
	Water* water = new Water;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	water->set_position(position);

	return water;
}

// Creates potion
static Potion* create_potion(int x, int y) {
	Potion* potion = new Potion;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	potion->set_position(position);

	return potion;
}

// Adds created objects in vectors
static void add(State state, int x, int y) {
	Avatar* avatar = create_avatar(x, y);			// Create Avatar
	state->At.push_back(avatar);
	for (int i = 0; i < x * y / 15; i++) {			// Create x*y/15 Werewolves and Vampires
		Werewolf* w = create_w(x,y);
		Vampire* v = create_v(x, y);
		state->Ww.push_back(w);
		state->Vp.push_back(v);

		state->info.number_V++;
		state->info.number_W++;


	}
	for (int i = 0; i < 5; i++) {					// Create i Trees and Water
		Tree* tree = create_tree(x, y);
		Water* water = create_water(x, y);

		state->Tr.push_back(tree);
		state->Wt.push_back(water);

	}
	Potion* potion = create_potion(x, y);			// Create potion

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



	add(s, s->map->get_length(), s->map->get_width());



	return s;
}

StateInfo state_info(State state) {
	return &state->info;
}

void state_update(State state, KeyState keys, Avatar* avatar) {
	if (state->info.playing) {
			avatar->movement(state, keys); //thelei virtual, override klp


			for (int i = 0; i < state->Ww.size(); i++) {
				Werewolf* w = state->Ww.at(i);
				w->movement(state, i, true); //0 for w , 1 for v thelei alli methodo tha to skefto meta
			}

			for (int i = 0; i < state->Vp.size(); i++) {
				Vampire* v = state->Vp.at(i);
				v->movement(state, i, false); //0 for w , 1 for v thelei alli methodo tha to skefto meta
			}

			 



	}
}

