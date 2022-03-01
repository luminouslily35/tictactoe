#include "GameHelper.h"
#include <format>
#include <iostream>
using namespace std;

// this function is useful if a player just moved, and wants to see if they won
int GameHelper::checkForWin(int x, int y, int marker, Board board) {
        if (winByRow(x, marker, board) || winByColumn(y, marker, board) || winByDiagonal(marker, board)) {
            return marker;
        }
        return 0;
  }

bool GameHelper::winByRow(int x, int marker, Board board) {
    return (board.atAdjusted(x, 1) == marker &&
        board.atAdjusted(x, 2) == marker &&
        board.atAdjusted(x, 3) == marker);
}

bool GameHelper::winByColumn(int y, int marker, Board board) {
    return (board.atAdjusted(1, y) == marker &&
        board.atAdjusted(2, y) == marker &&
        board.atAdjusted(3, y) == marker);
}

bool GameHelper::winByDiagonal(int marker, Board board) {
    return (
        (board.atAdjusted(1, 1) == marker &&
            board.atAdjusted(2, 2) == marker &&
            board.atAdjusted(3, 3) == marker)
        ||
        (board.atAdjusted(1, 3) == marker &&
            board.atAdjusted(2, 2) == marker &&
            board.atAdjusted(3, 1) == marker)
        );
}

bool GameHelper::isValidPlayerMove(int x, int y, Board board) {
    return x >= 1 && x <= 3 && y >= 1 && y <= 3 && !board.isTakenAdjusted(x, y);
}

void GameHelper::printBoard(Board board) {
    string firstLine = format("(1, )#  {}  #  {}  #  {}  #", 
        GameHelper::repr(board.atAdjusted(1, 1)), 
        GameHelper::repr(board.atAdjusted(1, 2)),
        GameHelper::repr(board.atAdjusted(1, 3))
    );
    string secondLine = format("(2, )#  {}  #  {}  #  {}  #", 
        GameHelper::repr(board.atAdjusted(2, 1)),
        GameHelper::repr(board.atAdjusted(2, 2)),
        GameHelper::repr(board.atAdjusted(2, 3))
    );
    string thirdLine = format("(3, )#  {}  #  {}  #  {}  #", 
        GameHelper::repr(board.atAdjusted(3, 1)),
        GameHelper::repr(board.atAdjusted(3, 2)),
        GameHelper::repr(board.atAdjusted(3, 3))
    );
    cout << "      (, 1) (, 2) (, 3) " << endl;
    cout << "     ###################" << endl;
    cout << firstLine << endl;
    cout << "     ###################" << endl;
    cout << secondLine << endl;
    cout << "     ###################" << endl;
    cout << thirdLine << endl;
    cout << "     ###################" << endl;
}

string GameHelper::repr(int marker) {
    if (marker == 0) return " ";
    else if (marker == 1) return "X";
    else return "O";
}