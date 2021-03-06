#include "Board.h"
#include "Square.h"

Board::Board() {
    for (int i = 0; i < 3; i++) {
        vector<int> v(3);
        squares.push_back(v);
    }
}
int Board::atPosition(int x, int y) {
    return squares[x][y];
}

void Board::setPosition(int x, int y, int newState) {
    squares[x][y] = newState;
}

int Board::atAdjusted(int x, int y) {
    return atPosition(x - 1, y - 1);
}

void Board::setAdjusted(int x, int y, int newState) {
    setPosition(x - 1, y - 1, newState);
}

void Board::clear() {
    for (int x = 1; x < 4; x++)
        for (int y = 1; y < 4; y++)
            setAdjusted(x, y, 0);
}

bool Board::isTakenAdjusted(int x, int y) {
    int pos = atAdjusted(x, y);
    return (pos == 1 || pos == 2);
}

vector<int> Board::asArray() {
    vector<int> array;
    for (int x = 1; x < 4; x++)
        for (int y = 1; y < 4; y++)
            array.push_back(atAdjusted(x, y));
    return array;
}

Board Board::asGrid(vector<int> arr) {
    Board newBoard;
    for (int i = 0; i < 9; i++) {
        int j = i / 3;
        int k = i % 3;
        newBoard.setAdjusted(j + 1, k + 1, arr[i]);
    }
    return newBoard;
}