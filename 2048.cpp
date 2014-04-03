#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <string>
#include <sstream>
#include "Board.h"
#include "Board.cpp"
#include "Ai.cpp"
#include "Ai.h"
using namespace std;

const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int UP = 4;

void init();
void startgame(Board &b);
void initaimode(Board &b);
bool keepplaying(Board &b);
void getmove(Board &b);
void cls();

int main(int argc, char** argv) {
	init();
	bool isplaying = true;
	bool aimode = true;
	while (isplaying) {
		Board board;
		if (!aimode) {
			startgame(board);
			if (!keepplaying(board)) {
				isplaying = false;
			}
		} else {
			initaimode(board);
			break;
		}
	}
}

void init() {
	srand(time(NULL));
}

void startgame(Board &b) {
	string response = "";
	while (!b.isgameover()) {
		getmove(b);
	}
}

void initaimode(Board &b) {
	while (!b.isgameover()) {
		b.display();
		Ai ai(b);
		int aimove = ai.startaimode();
		b.makemove(aimove);
		cout << aimove << "\n";
		if (aimove == -1) {
			break;
		}
	}
	b.display();
	if (!b.isgameover()) {
		cout << "error" << "\n";
	}
}

void getmove(Board &b) {
	string response = "";
	bool error = false;
	b.display();
	cout << "Enter 'u', 'd', 'r', or 'l'" << "\n";
	cout << "Move: ";	
	cin >> response;
	string tmpret = "";
	for (int i = 0; i < response.size(); i++) {
		int tmpval = -1;
		if (response[i] == 'u') tmpval = UP;
		else if (response[i] == 'd') tmpval = DOWN;
		else if (response[i] == 'l') tmpval = LEFT;
		else if (response[i] == 'r') tmpval = RIGHT;
		if (tmpval >= RIGHT && tmpval <= UP)
			b.makemove(tmpval);
	}
}

bool keepplaying(Board &b) {
	string response = "";
	bool error = false;
	while (response.size() == 0) {
		cls();
		b.display();
		cout << "\n\nGAME OVER\n" << "\n";
		if (error) {
			cout << "Error: Invalid input." << "\n";
			cout << "Please enter 'y' or 'n'" << "\n";		
		}
		cout << "Keep playing? (y/n): ";
		cin >> response;
		if (response != "y" && response != "n") {
			response = "";
			error = true;
		}
	}
	return response == "y";
}

void cls() {
	for (int i = 0; i < 5; i++) {
		cout << "\n\n\n\n\n" << "\n";
	}
}