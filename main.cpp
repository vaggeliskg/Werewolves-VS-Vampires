#include <iostream>
#include "state.h"

using namespace std;

// Print board of game
void board(int x, int y, State state) {

	for (int i = 0; i < y; i++) {
		cout << "#";
		for (int j = 0; j < x - 2 ; j++) {
			for (int k = 0; k < state->Ww.size(); k++) {
				if (i == state->Ww.at(k)->get_position()->y && j == state->Ww.at(k)->get_position()->x) cout << 'W';
			}
			for (int k = 0; k < state->Vp.size(); k++) {
				if (i == state->Vp.at(k)->get_position()->y && j == state->Vp.at(k)->get_position()->x) cout << 'V';
			}
			if (i == 0 || i == y - 1) cout << "#";
			else if (i == state->At.at(0)->get_position()->y && j == state->At.at(0)->get_position()->x) cout << "A";
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

	//board(x, y);

	// Printing results for test debugging
	cout << "Map is: " << ptr->get_length() << "x" << ptr->get_width() << endl;
	if (state->info.Team_W) {
		cout << "Team: Werewolves\n";
	}
	else {
		cout << "Team: Vampires\n";
	}


	system("cls");

	//cout << state->At.at(0)->get_position()->y; "\n";
	//cout << state->At.at(0)->get_position()->x; "\n";

	while (true) {
		board(x, y, state);
		state_update(state, state->At.at(0));
		if (_kbhit) {

			switch (_getch()) {
			case 'w': state->At.at(0)->change('w'); break;
			case 'd': state->At.at(0)->change('d'); break;
			case 's': state->At.at(0)->change('s'); break;
			case 'a': state->At.at(0)->change('a'); break;
			}

			//cout << state->Vp.size(); "\n";
			//cout << state->Ww.size(); "\n";

		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

	}


}