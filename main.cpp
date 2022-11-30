#include <iostream>
#include "state.h"

using namespace std;

void board(int x, int y) {

	Map map;
	
	//map.set_lenght(x);
	//map.set_width(y);


}






int main() {
	int x, y;
	cout << "Welcome to Werewolves vs Vampires\n";
	cout << "Please provide the length of the map: ";
	cin >> x;
	cout << "\n";
	cout << "Please provide the width of the map: ";
	cin >> y;
	cout << "\n";

	board(x, y);


}