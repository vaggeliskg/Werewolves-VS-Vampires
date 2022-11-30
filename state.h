#pragma once

#include <vector>

// Information about which keys are pressed
typedef struct key_state {
    bool up;						// true if this key is pressed
    bool down;
    bool left;
    bool right;
    bool space;
    bool enter;
    bool p;
}*KeyState;

// General information about the game
typedef struct state_info {
    int number_W;                   // number of Werewolves that are still alive
    int number_V;                   // number of Vampires that are still alive
    bool Team_W;                    // true for team Werewolves, false for team Vampires
    bool playing;					// true if game has started (false after game over)
    bool paused;					// true if game is paused
}*StateInfo;

// Η κατάσταση του παιχνιδιού (handle)
typedef struct state* State;

// Coordinates
typedef struct point {
    int x;
    int y;
}*Point;

// Map of the game
class Map {
private:
    int length;
    int width;
    bool night;                     // night or day
public:
    void set_lenght(int);
    void set_width(int);
    void set_time(bool);

    int get_length()const;
    int get_width()const;
    bool get_time()const;

};

// Creatures can be Werewolves, Vampires or Avatar
class Creature {
protected:
    Point position;             // position in map
public:
    void movement(State state, KeyState keys);
    void set_position(Point position);
    Point get_position()const;
};

// Objects can be Water, Trees or Potion
class Object {
protected:
    Point position;
public:
    void set_position(Point position);
    Point get_position()const;
};

class Werewolf;
class Vampire;

class Avatar :public Creature {
private:
    int potions = 1;                // number of potions [0,2]
public:
    void set_potions(int potions);
    int get_potions()const;
    void help_W(Werewolf*);
    void help_V(Vampire*);
};

class Werewolf :public Creature {
private:
    int health;
    int strength;
    int defence;
public:
    void attack(Vampire*);
    void help(Werewolf*);
    void set_health(int health);
    void set_strength(int strength);
    void set_defence(int defence);
    int get_health()const;
    int get_strength()const;
    int get_defence()const;
};

class Vampire :public Creature {
private:
    int health;
    int strength;
    int defence;
public:
    void attack(Werewolf*);
    void help(Vampire*);
    void set_health(int health);
    void set_strength(int strength);
    void set_defence(int defence);
    int get_health()const;
    int get_strength()const;
    int get_defence()const;
};

class Tree :public Object {};

class Water :public Object {};

class Potion :public Object {};

State state_create();
StateInfo state_info(State state);
void state_update(State state, KeyState keys);