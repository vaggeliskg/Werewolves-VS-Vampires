#include <iostream>
#include "state.h"

using namespace std;

// Print board of game
void board(int x, int y, State state) {
	bool printed;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x ; j++) {
			printed = false;
			if (i == 0 || i == y-1) {
				cout << "@";
				printed = true;
			}
			if (i != 0 && i != y - 1 && (j == x-1 || j == 0)) {
				cout << "#";
				printed = true;
			}
			for (int k = 0; k < state->Ww.size(); k++) {
				if (i == state->Ww.at(k)->get_position()->y && j == state->Ww.at(k)->get_position()->x) {
					cout << 'w';
					printed = true;
					break;
				}
			}
			for (int k = 0; k < state->Vp.size(); k++) {
				if (i == state->Vp.at(k)->get_position()->y && j == state->Vp.at(k)->get_position()->x) {
					cout << 'v';
					printed = true;
					break;
				}
			}
			if (i == state->At.at(0)->get_position()->y && j == state->At.at(0)->get_position()->x) {
				cout << "A";
				printed = true;
			}
			for (int k = 0; k < state->Tr.size(); k++) {
				if (i == state->Tr.at(k)->get_position()->y && j == state->Tr.at(k)->get_position()->x) {
					cout << "T";
					printed = true;
					break;
				}
			}
			for (int k = 0; k < state->Wt.size(); k++) {
				if (i == state->Wt.at(k)->get_position()->y && j == state->Wt.at(k)->get_position()->x) {
					cout << "W";
					printed = true;
					break;
				}
			}
			if (i == state->Pt.at(0)->get_position()->y && j == state->Pt.at(0)->get_position()->x) {
				cout << "P";
				printed = true;
			}
			if (printed == false)
				cout << " ";
			
		}
		cout << endl;
		
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
	ptr->set_length(y);
	ptr->set_width(x);
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

	// Printing results for test debugging
	cout << "Map is: " << ptr->get_length() << "x" << ptr->get_width() << endl;
	if (state->info.Team_W) {
		cout << "Team: Werewolves\n";
	}
	else {
		cout << "Team: Vampires\n";
	}


	system("cls");

	while (true) {
		board(x, y, state);
		/*for (int k = 0; k < state->Vp.size(); k++) {
			cout << "v:" << state->Vp.at(k)->get_position()->x << "," << state->Vp.at(k)->get_position()->y << endl;
		}
		for (int k = 0; k < state->Ww.size(); k++) {
			cout << "Ww:" << state->Ww.at(k)->get_position()->x << "," << state->Ww.at(k)->get_position()->y << endl;
		}
		for (int k = 0; k < state->Wt.size(); k++) {
			cout << "W:" << state->Wt.at(k)->get_position()->x << "," << state->Wt.at(k)->get_position()->y << endl;
		}
		for (int k = 0; k < state->Tr.size(); k++) {
			cout << "tr:" << state->Tr.at(k)->get_position()->x << "," << state->Tr.at(k)->get_position()->y << endl;
		}
		cout << "A:" << state->At.at(0)->get_position()->x << "," << state->At.at(0)->get_position()->y << endl;
		cout << "Pt:" << state->Pt.at(0)->get_position()->x << "," << state->Pt.at(0)->get_position()->y << endl;
		for (int k = 0; k < state->Locations.size(); k++) {
			cout << "Loc:" << state->Locations.at(k)->x << "," << state->Locations.at(k)->y << endl;
		}*/
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