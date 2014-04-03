#ifndef Board_H
#define Board_H

#include <vector>
#include <utility>
using namespace std;

class Board {
private:
	int dimension, digitsize, score;
	bool won;
	vector<vector<int> > board, mergetrack;

	void placeatrandcell();
	void move(pair<int, int> loc, pair<int, int> original);
	void removecell(pair<int, int> loc);
	pair<int, int> movedirection(int x, int y, int direction);
	bool moverightdown(int direction);
	bool moveleftup(int direction);
	bool hasmoves(int x, int y);
public:
	Board();
	Board(Board &copy);
	bool makemove(int direction);
	bool getwon();
	int getdimension();
	int getcellvalue(int x, int y);
	int getdigitsize();
	void display();
	bool iscelloccupied(pair<int, int> loc);
	bool isgameover();
	vector<vector<int> > getboard();
	int getscore();
};
#endif // Board_H