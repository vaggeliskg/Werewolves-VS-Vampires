#include <iostream>
#include "state.h"

using namespace std;

int main() {
	int x, y;					// x = width of map, y = length/height of map
	int timer = 0;
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
		if (state->info.paused == false) {						// If game is not paused
			board(x, y, state);									// Print board, creatures and objects
			Sleep(500);											// After delay of 500 milliseconds
			state_update(state);								// Update game state
			timer++;
			if (timer == 20) {
				if (state->map->get_time()) {
					state->map->set_time(false);
				}
				else {
					state->map->set_time(true);
				}
				timer = 0;
			}
		}
		if (!_kbhit() && state->info.paused == false) {			// If there is not any key pressed and game is not paused
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // Cursor goes at (0,0)
			continue;
		}
		else if (_kbhit()) {									// If any key is pressed
			switch (_getch()) {									// Get key pressed
				case 'w': state->At.at(0)->movement(state, 'w'); break;
				case 'd': state->At.at(0)->movement(state, 'd'); break;
				case 's': state->At.at(0)->movement(state, 's'); break;
				case 'a': state->At.at(0)->movement(state, 'a'); break;
				case 'q':										// If q is pressed
					state->info.playing = false;				// Game ends
					system("cls");								// Clear screen
					break;
				case 'p':										// If p is pressed, change the pause condition
					if (state->info.paused == false) {
						state->info.paused = true;
						system("cls");
						menu(state);							// Print menu
					}
					else {										// If p pressed and already in menu
						state->info.paused = false;
						system("cls");							// Clear screen
					}
					break;
				case 'h': state->At.at(0)->help_team(state); break;
			}
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // Cursor goes at (0,0)
	}
	system("cls");												// Clear screen
	if (state->info.number_W == 0) {							// If all werewolves died
		cout << "VAMPIRES WON!" << endl;
	}
	else if (state->info.number_V == 0) {						// If all vampires died
		cout << "WEREWOLVES WON!" << endl;
	}
	else {														// If game ended for any other reason, for example player quit
		cout << "YOU QUIT :(" << endl;
	}

	return 0;
}