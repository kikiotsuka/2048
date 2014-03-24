#ifndef Board_H
#define Board_H

#include <vector>
#include <utility>
using namespace std;

class Board {
private:
	int dimension;
	int digitsize;
	int score;
	bool alive;
	bool won;
	vector<vector<int> > board;

	void placeatrandcell();
	void makemove(pair<int, int> loc, pair<int, int> original);
	bool isgameover();
	bool iscelloccupied(pair<int, int> loc);
	void removecell(pair<int, int> loc);
	pair<int, int> movedirection(int x, int y, int direction);
	bool moverightdown(int direction);
	bool moveleftup(int direction);
	bool hasmoves(int x, int y);
public:
	Board();
	void makemove(int direction);
	bool getisalive();
	void display();
};
#endif // Board_H