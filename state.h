#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Condition of game (handle)
typedef struct state* State;

// Information about which keys are pressed
typedef struct key_state {
    bool up;						        // true if this key is pressed
    bool down;
    bool left;
    bool right;
    bool space;
    bool enter;
    bool p;
}* KeyState;

// General information about the game
typedef struct state_info {
    int number_W = 0;                       // number of Werewolves that are still alive
    int number_V = 0;                       // number of Vampires that are still alive
    bool Team_W = false;                    // true for team Werewolves, false for team Vampires
    bool playing = false;					// true if game has started (false after game over)
    bool paused = false;					// true if game is paused
}* StateInfo;

// Coordinates
typedef struct point {
    int x;
    int y;
}* Point;

// Map of the game
class Map {
private:
    int length;
    int width;
    bool night;                             // night or day
public:
    void set_length(int);
    void set_width(int);
    void set_time(bool);

    int get_length()const;
    int get_width()const;
    bool get_time()const;

};

// Creatures can be Werewolves, Vampires or Avatar
class Creature {
protected:
    Point position;                         // position in map
public:
    void movement(State state, int first, bool ct);
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
    int potions = 1;                        // number of potions [0,2]
public:
    void movement(State state, KeyState keys);
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

// Condition of game (handle)
struct state {
    struct state_info info;
    Map* map;
    vector <Werewolf*> Ww;
    vector <Vampire*> Vp;
    vector <Avatar*> At;
    vector <Tree*> Tr;
    vector <Water*> Wt;
    vector <Potion*> Pt;
};


// More
// Creates and returns the state of the game
State state_create(Map* map);

// Returns game information to state
StateInfo state_info(State state);

// Updates the state of the game depending the keys that are pressed
void state_update(State state, KeyState keys, Avatar* avatar);

