#include <iostream>
#include "state.h"

using namespace std;

// Map
void Map::set_length(int length) {
	length = length;
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

// More
State state_create() {
	return NULL;
}

StateInfo state_info(State state) {
	return NULL;
}

void state_update(State state, KeyState keys) {

}

