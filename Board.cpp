#include "Board.h"
#include "Square.h"

Board::Board() {
    for (int i = 0; i < 3; i++) {
    	// default constructor called for each of the 3 Squares
        vector<Square> v(3);
        squares.push_back(v);
    }
}

string Board::at(int x, int y) {
    return squares[x][y].getState();
}

void Board::set(int x, int y, string newState) {
    squares[x][y].setState(newState);
}
