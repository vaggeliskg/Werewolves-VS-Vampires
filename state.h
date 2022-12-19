#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;

// Condition of game (handle)
typedef struct state* State;

// Information about surrounding objects
typedef struct surroundings {
    bool up;						        // True if there is an object in this location
    bool down;
    bool left;
    bool right;
    bool upper_r;
    bool upper_l;
    bool lower_r;
    bool lower_l;
}*S ;

// General information about the game
typedef struct state_info {
    int number_W = 0;                       // Number of Werewolves that are still alive
    int number_V = 0;                       // Number of Vampires that are still alive
    bool Team_W = false;                    // True for team Werewolves, false for team Vampires. Initialize to false to avoid warnings
    bool playing = true;					// True if game has started (false after game over)
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
    Map(int, int, bool);                    // constructor for map
    ~Map();
    void set_time(bool);
    int get_length()const;
    int get_width()const;
    bool get_time()const;

};

// Creatures can be Werewolves, Vampires or Avatar
class Creature {
protected:
    Point position;                         // Position in map
    S surround;                             // Objects surrounding this creature
public:
    virtual void movement(State state, int first);
    void set_position(Point position);
    Point get_position()const;
    void set_surround(S sour);
    S get_surround()const;
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
    void movement(State state, char character);
    void set_potions(int potions);
    int get_potions()const;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    void help_team(State state);
};

class Werewolf :public Creature {
private:
    int health;                             // Health value can be [1,5]
    int strength;                           // Strength value can be [1,3]
    int defence;                            // Defence value can be [1,2]
    int medkit;                             // Medkit value can be [0,2]
public:
    void attack(Vampire*);                  // Attacks opponent that is near
    void help(Werewolf*);                   // Helps ally that is near
    void set_health(int health);
    void set_strength(int strength);
    void set_defence(int defence);
    void set_medkit(int medkit);
    int get_health()const;
    int get_strength()const;
    int get_defence()const;
    int get_medkit()const;
};

class Vampire :public Creature {
private:
    int health;                             // Health value can be[1, 5]
    int strength;                           // Strength value can be [1,3]
    int defence;                            // defence value can be [1,2]
    int medkit;                             // Medkit value can be [0,2]
public:
    void attack(Werewolf*);                 // Attacks opponent that is near
    void help(Vampire*);                    // Helps ally that is near
    void set_health(int health);
    void set_strength(int strength);
    void set_defence(int defence);
    void set_medkit(int medkit);
    int get_health()const;
    int get_strength()const;
    int get_defence()const;
    int get_medkit()const;
    void movement(State state, int first);
};

class Tree :public Object {};

class Water :public Object {};

class Potion :public Object {};

// Condition of game (handle)
struct state {
    struct state_info info;
    Map* map = NULL;
    vector <Werewolf*> Ww;                  // Vector that contains werewolves
    vector <Vampire*> Vp;                   // Vector that contains vampires
    vector <Avatar*> At;                    // Vector that contains avatar
    vector <Tree*> Tr;                      // Vector that contains trees
    vector <Water*> Wt;                     // Vector that contains water
    vector <Potion*> Pt;                    // Vector that contains potion
    vector <Point> Locations;               // Vector that contains each object location
};


// More
// Creates and returns the state of the game
State state_create(Map* map);

// Updates the state of the game depending the keys that are pressed
void state_update(State state);

// Prints board of game, creatures, objects
void board(int x, int y, State state);

// Prints menu of game and shows game information
void menu(State state);

// Deallocate memory
void deallocation(State state);

