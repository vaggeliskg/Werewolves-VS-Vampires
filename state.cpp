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

// Creature
void Creature::movement(State state, KeyState keys){


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

void Avatar::help_W(Werewolf*) {

}

void Avatar::help_V(Vampire*) {

}

// Werewolf
void Werewolf::attack(Vampire*) {

}

void Werewolf::help(Werewolf*) {

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
void Vampire::attack(Werewolf*) {

}

void Vampire::help(Vampire*) {

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

// Creates a werewolf
Werewolf* create_w(int x, int y ) {
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
Vampire* create_v(int x, int y) {
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

	return v;
}

// Creates avatar
Avatar* create_avatar(int x, int y) {
	Avatar* avatar = new Avatar;
	Point position = new point;
	position->x = (rand() % x) + (x / 4);
	position->y = (rand() % y) + (y / 4);
	avatar->set_position(position);
}


// Adds created objects in vectors
static void add(State state, int x, int y) {
	Avatar* avatar = create_avatar(x, y);
	for (int i = 0; i < x * y / 15; i++) {
		Werewolf* w = create_w(x,y);
		Vampire* v = create_v(x, y);
	}




}




// More
State state_create(int x , int y) {
	state *s = new state;
	s->info.playing = true;
	s->info.paused = false;
	s->info.number_V = 0;
	s->info.number_W = 0;
	//s->info.Team_W = false;


	add(s, x, y);



	return s;
}

StateInfo state_info(State state) {
	return &state->info;
}

void state_update(State state, KeyState keys) {

}

