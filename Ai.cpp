#include "Ai.h"
#include "GameHelper.h"

int Ai::findWinner(Board board) {
    return 0;
}

int Ai::scoreBoard(int aiChoice, Board board) {
    int winner = findWinner(board);



    // if ai is a winner
    // return 10 or whatever
    // else if player is a winner
    // return -10
    // else return 0
    return 0;
}

void Ai::minimax(int aiChoice, Board board) {
    // from the current state of board, look at all the different positions that the marker could go onto.
    // then recurse until you reach a terminal (where either ai wins, player wins, or draw)

    // make a list of moves (ranging from 1-9), excluding the occupied ones
    // and make a score-list for each move

    //List<int> moves = new List<int>();
    //return;
}
vector<int> Ai::aiMove(Board board) {
    return { 1, 1 };
}

vector<int> Ai::playRandom(Board board) {
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (!board.isTakenAdjusted(i, j)) {
                return { i, j };
            }
        }
    }
    return { 0, 0 };
}