#include <iostream>
#include "state.h"

using namespace std;

// Map
void Map::set_length(int a) {
	length = a;
}

void Map::set_width(int width) {
	width = width;
}

void Map::set_time(bool night) {
	night = night;
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

void Creature::set_position(Point position) {
	position = position;
}

Point Creature::get_position()const {
	return position;
}

// Object
void Object::set_position(Point position) {
	position = position;
}

Point Object::get_position()const {
	return position;
}

// Avatar
void Avatar::set_potions(int potions) {
	potions = potions;
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

void Werewolf::set_health(int health) {
	health = health;
}

void Werewolf::set_strength(int strength) {
	strength = strength;
}

void Werewolf::set_defence(int defence) {
	defence = defence;
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

void Vampire::set_health(int health) {
	health = health;
}

void Vampire::set_strength(int strength) {
	strength = strength;
}

void Vampire::set_defence(int defence) {
	defence = defence;
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

