#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <string>
#include "Board.h"
#include "Board.cpp"
#include <stdexcept>
using namespace std;

const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int UP = 4;

void init();
void startgame(Board &b);
bool keepplaying();
int getmove(Board &b);
void cls();

int main(int argc, char** argv) {
	init();
	bool isplaying = true;
	while (isplaying) {
		Board board;
		startgame(board);
		if (!keepplaying()) {
			isplaying = false;
		}
	}
}

void init() {
	srand(time(NULL));
}

void startgame(Board &b) {
	string response = "";
	while (b.getisalive()) {
		int move = getmove(b);
		b.makemove(move);
	}
}

int getmove(Board &b) {
	string response = "";
	bool error = false;
	while (response.size() == 0) {
		b.display();
		if (error) {
			cout << "Error: Invalid input" << "\n";
		}
		cout << "Enter 'u', 'd', 'r', or 'l'" << "\n";
		cout << "Move: ";
		cin >> response;	
		if (response != "u" && response != "d" && response != "l" && response != "r") {
			response = "";
			error = true;
		}
	}
	if (response == "u") return UP;
	if (response == "d") return DOWN;
	if (response == "l") return LEFT;
	if (response == "r") return RIGHT;
	return -1;
}

bool keepplaying() {
	string response = "";
	bool error = false;
	while (response.size() == 0) {
		cls();
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