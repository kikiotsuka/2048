#include "Board.h"
#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

extern const int RIGHT;
extern const int DOWN;
extern const int LEFT;
extern const int UP;

Board::Board() {
	dimension = 4;
	alive = true;
	digitsize = 1;
	score = 0;
	won = false;
	for (int i = 0; i < dimension; i++) {
		vector<int> tmp;
		for (int j = 0; j < dimension; j++) {
			tmp.push_back(-1);
		}
		board.push_back(tmp);
		mergetrack.push_back(tmp);
	}
	placeatrandcell();
	placeatrandcell();
}

void Board::makemove(int direction) {
	bool moved = false;
	if (direction == RIGHT || direction == DOWN)
		moved = moverightdown(direction);
	else if (direction == LEFT || direction == UP)
		moved = moveleftup(direction);
	if (moved)
		placeatrandcell();
	if (isgameover())
		alive = false;
	for (int i = 0; i < mergetrack.size(); i++) {
		for (int j = 0; j < mergetrack[0].size(); j++) {
			mergetrack[i][j] = -1;
		}
	}
}

bool Board::isgameover() {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (hasmoves(i, j))
				return false;
		}
	}
	return true;
}

bool Board::hasmoves(int x, int y) {
	int val = board[x][y];
	if (x < dimension - 1 && (board[x + 1][y] == -1 || board[x + 1][y] == val))
		return true;
	if (y < dimension - 1 && (board[x][y + 1] == -1 || board[x][y + 1] == val))
		return true;
	return false;
}

void Board::move(pair<int, int> loc, pair<int, int> original) {
	//merge tiles
	if (mergetrack[loc.first][loc.second] == -1 && 
			board[loc.first][loc.second] == board[original.first][original.second]) {
		board[loc.first][loc.second] = board[original.first][original.second] * 2;
		score += board[loc.first][loc.second];
		if (!won && board[loc.first][loc.second] == 2048)
			won = true;
		if (digitsize < 2 && board[loc.first][loc.second] > 9) digitsize++;
		if (digitsize < 3 && board[loc.first][loc.second] > 99) digitsize++;
		if (digitsize < 4 && board[loc.first][loc.second] > 999) digitsize++;
		mergetrack[loc.first][loc.second] = 1;
	} else {
		board[loc.first][loc.second] = board[original.first][original.second];
	}
	removecell(original);
}

bool Board::moverightdown(int direction) {
	bool moved = false;
	for (int i = dimension - 1; i >= 0; i--) {
		for (int j = dimension - 1; j >= 0; j--) {
			if (board[i][j] != -1) {
				pair<int, int> loc = movedirection(i, j, direction);
				if (loc.first != i || loc.second != j) {
					moved = true;
					move(loc, pair<int, int>(i, j));
				}
			}
		}
	}
	return moved;
}

bool Board::moveleftup(int direction) {
	bool moved = false;
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (board[i][j] != -1) {
				pair<int, int> loc = movedirection(i, j, direction);
				if (loc.first != i || loc.second != j) {
					moved = true;
					move(loc, pair<int, int>(i, j));
				}
			}
		}
	}
	return moved;
}

void Board::removecell(pair<int, int> location) {
	board[location.first][location.second] = -1;
}

pair<int, int> Board::movedirection(int x, int y, int direction) {
	int val = board[x][y];
	if (direction == RIGHT) {
		while (y < dimension - 1 && (board[x][y + 1] == -1 || board[x][y + 1] == val))
			y++;
	} else if (direction == DOWN) {
		while (x < dimension - 1 && (board[x + 1][y] == -1 || board[x + 1][y] == val))
			x++;
	} else if (direction == LEFT) {
		while (y > 0 && (board[x][y - 1] == -1 || board[x][y - 1] == val))
			y--;
	} else if (direction == UP) {
		while (x > 0 && (board[x - 1][y] == -1 || board[x - 1][y] == val))
			x--;
	}
	return pair<int, int>(x, y);
}

void Board::placeatrandcell() {
	pair<int, int> place(-1, -1);
	do {
		place.first = rand() % dimension;
		place.second = rand() % dimension;
	} while (iscelloccupied(place));
	int val = 2;
	if (rand() % 100 >= 90)
		val = 4;
	board[place.first][place.second] = val;
}

bool Board::iscelloccupied(pair<int, int> loc) {
	if (board[loc.first][loc.second] == -1)
		return false;
	return true;
}

bool Board::getisalive() {
	return alive;
}

void Board::display() {
	for (int i = 0; i < 5; i++) {
		cout << "\n\n\n\n\n" << "\n";
	}
	if (won) {
		cout << "2048 Reached! Keep going for an even better highscore" << "\n";
	}
	cout << "Score: " << score << "\n";
	for (int i = 0; i < dimension * (digitsize + 1) + 1; i++) {
		cout << "_";
	}
	cout << "\n";
	for (int i = 0; i < dimension; i++) {
		cout << "|";
		for (int j = 0; j < dimension; j++) {
			if (board[i][j] != -1) {
				if (board[i][j] > 999) {
					cout << board[i][j];
				} else if (board[i][j] > 99) {
					for (int k = 0; k < digitsize - 3; k++) {
						cout << "0";
					}
					cout << board[i][j];
				} else if (board[i][j] > 9) {
					for (int k = 0; k < digitsize - 2; k++) {
						cout << "0";
					}
					cout << board[i][j];
				} else {
					for (int k = 0; k < digitsize - 1; k++) {
						cout << "0";
					}
					cout << board[i][j];
				}
			} else {
				for (int k = 0; k < digitsize; k++) {
					cout << " ";
				}
			}
			if (j < dimension - 1) {
				cout << " ";
			}
		}
		cout << "|";
		cout << "\n";
	}
	for (int i = 0; i < dimension * (digitsize + 1) + 1; i++) {
		cout << "-";
	}
	cout << "\n";
}