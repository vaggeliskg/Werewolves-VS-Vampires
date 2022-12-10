#include <iostream>
#include "state.h"

using namespace std;

int main() {
	int x, y;					// x = width of map, y = length/height of map
	string team;

	// Select dimensions of map
	cout << "Welcome to Werewolves vs Vampires!" << endl;
	cout << "Suggested width [20,140] and length [15,35]" << endl;
	cout << "Please type the width of the map: ";
	do{
		cin >> x;
	} while (x < 20 || x > 140);
	cout << "Please type the height of the map: ";
	do {
		cin >> y;
	} while (y < 15 || y > 35);
	cout << endl;

	// Create map of the game
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

	// Game proceeds
	while (state->info.playing) {								// If game has started
		if (state->info.paused) {								// If game is paused
			system("cls");										// Clear screen
			menu(state);										// Print main menu
		}
		else {													// If game is not paused
			board(x, y, state);									// Print board, creatures and objects
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
		}
			if (_kbhit) {										// If any key is pressed
				switch (_getch()) {								// Get key pressed
				case 'w': state->At.at(0)->change('w'); break;
				case 'd': state->At.at(0)->change('d'); break;
				case 's': state->At.at(0)->change('s'); break;
				case 'a': state->At.at(0)->change('a'); break;
				case 'q':										// If q is pressed then
					state->info.playing = false;				// Game ends
					system("cls");								// Clear screen
					break;
				case 'p':										// If p is pressed, change the pause condition
					if (state->info.paused == false) {
						state->info.paused = true;
					}
					else {										// If p pressed and already in menu
						state->info.paused = false;
						system("cls");							// Clear screen
					}
					break;
				}

			}

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // Cursor goes at (0,0)
	}

	return 0;
}