#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Condition of game (handle)
typedef struct state* State;

// Information about which keys are pressed
typedef struct key_state {
    bool up;						        // True if this key is pressed
    bool down;
    bool left;
    bool right;
    bool space;
    bool enter;
    bool p;
}* KeyState;

// General information about the game
typedef struct state_info {
    int number_W = 0;                       // Number of Werewolves that are still alive
    int number_V = 0;                       // Number of Vampires that are still alive
    bool Team_W;                            // True for team Werewolves, false for team Vampires
    bool playing = false;					// True if game has started (false after game over)
    bool paused = false;					// True if game is paused
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
    bool night;                             // Night or day
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
    Point position;                         // Position in map
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
    int potions = 1;                        // Number of potions [0,2]
public:
    void movement(State state, KeyState keys);
    void set_potions(int potions);
    int get_potions()const;
    void help_W(Werewolf*);                 // Helps creature Werewolf by adding 1 more health value
    void help_V(Vampire*);                  // Helps creature Vampire by adding 1 more health value
};

class Werewolf :public Creature {
private:
    int health;                             // Health value can be [0,2]
    int strength;                           // Strength value can be [,]
    int defence;                            // defence value can be [,]
public:
    void attack(Vampire*);                  // Attacks opponent that is near
    void help(Werewolf*);                   // Helps ally that is near
    void set_health(int health);
    void set_strength(int strength);
    void set_defence(int defence);
    int get_health()const;
    int get_strength()const;
    int get_defence()const;
};

class Vampire :public Creature {
private:
    int health;                             // Health value can be[0, 2]
    int strength;                           // Strength value can be [1,3]
    int defence;                            // defence value can be [1,2]
public:
    void attack(Werewolf*);                 // Attacks opponent that is near
    void help(Vampire*);                    // Helps ally that is near
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

