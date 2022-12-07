#include <iostream>
#include "state.h"

using namespace std;

// Print board of game
void board(int x, int y) {

	for (int i = 0; i < y; i++) {
		cout << "\t\t#";
		for (int j = 0; j < x - 2; j++) {
			if (i == 0 || i == y - 1) cout << "#";
			else cout << ' ';
		}
		cout << "#\n";
	}
}

int main() {
	int x, y;					// x = width of map, y = length of map
	string team;

	// Select dimensions of map
	cout << "Welcome to Werewolves vs Vampires" << endl;
	cout << "Please type the width of the map: ";
	cin >> x;
	cout << "Please type the length of the map: ";
	cin >> y;
	cout << endl;

	Map* ptr = new Map;
	ptr->set_length(x);
	ptr->set_width(y);
	ptr->set_time(false);

	// Create state of the game
	State state = state_create(ptr);

	// Select team Werewolves or Vampires
	cout << "Please select team. Type 'W' or 'w' for Werewolves, 'V' or 'v' for Vampires: ";
	do {
		cin >> team;
		if (team != "W" && team != "w" && team != "V" && team != "v") {
			cout << "Wrong team input. Try again: ";
		}
		else if (team == "W" || team == "w") {
			state->info.Team_W = true;
		}
		else if (team == "V" || team == "v") {
			state->info.Team_W = false;
		}
	} while (team != "W" && team != "w" && team != "V" && team != "v");
	cout << endl;

	system("cls");

	board(x, y);

	// Printing results for test debugging
	cout << "Map is: " << ptr->get_length() << "x" << ptr->get_width() << endl;
	if (state->info.Team_W) {
		cout << "Team: Werewolves\n";
	}
	else {
		cout << "Team: Vampires\n";
	}


}