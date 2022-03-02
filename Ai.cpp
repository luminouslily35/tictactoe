#include "Ai.h"
#include "GameHelper.h"
#include <algorithm>

int Ai::findWinner(int player, int opponent, Board board) {
    vector<int> agents = { player, opponent };

    for(int agent : agents) {
        if ((board.atAdjusted(1, 1) == agent && board.atAdjusted(2, 2) == agent && board.atAdjusted(3, 3) == agent) ||
            (board.atAdjusted(1, 3) == agent && board.atAdjusted(2, 2) == agent && board.atAdjusted(3, 1) == agent) ||
            (board.atAdjusted(1, 1) == agent && board.atAdjusted(1, 2) == agent && board.atAdjusted(1, 3) == agent) ||
            (board.atAdjusted(2, 1) == agent && board.atAdjusted(2, 2) == agent && board.atAdjusted(2, 3) == agent) ||
            (board.atAdjusted(3, 1) == agent && board.atAdjusted(3, 2) == agent && board.atAdjusted(3, 3) == agent) ||
            (board.atAdjusted(1, 1) == agent && board.atAdjusted(2, 1) == agent && board.atAdjusted(3, 1) == agent) ||
            (board.atAdjusted(1, 2) == agent && board.atAdjusted(2, 2) == agent && board.atAdjusted(3, 2) == agent) ||
            (board.atAdjusted(1, 3) == agent && board.atAdjusted(2, 3) == agent && board.atAdjusted(3, 3) == agent))
        {
            return agent;
        }
    }
    return 0;
}

int Ai::scoreBoard(int player, int opponent, vector<int> boardArray) {
    Board board = Board::asGrid(boardArray);
    int winner = findWinner(player, opponent, board);
    if (winner == player) return 10;
    else if (winner == opponent) return -10;
    else return 0;
}

int Ai::togglePlayer(int choice) {
    if (choice == 2) return 1;
    else return 2;
}

vector<vector<int>> Ai::findPossibleMoves(int currentPlayer, vector<int> boardArray, vector<pair<int, int>>* possibleActions) {
    vector<vector<int>> moves;
    for (int i = 0; i < 9; i++) {
        // space not taken
        if (boardArray[i] == 0) {
            vector<int> copy = boardArray;
            copy[i] = currentPlayer;
            moves.push_back(copy);
            int col = i % 3; int row = i / 3;
            possibleActions->push_back({ row+1, col+1 });
        }
    }
    return moves;
}

int Ai::minimax(int player, int opponent, int currentPlayer, vector<int> board, pair<int, int>* choice) {
    int gameScore = scoreBoard(player, opponent, board); // result in +10, -10, or 0
    if (gameScore != 0) { return gameScore; }

    // this is an array of pairs {x, y} that the player needs to take in order to achieve 
    // each board in possibleMoves
    vector<pair<int, int>> possibleActions;

    // possibleMoves are just an array of boards (represented as arrays of length 9)
    // they don't really tell you what the actual moves are
    vector<vector<int>> possibleMoves = findPossibleMoves(currentPlayer, board, &possibleActions);

    vector<int> scores;

    for (vector<int> move : possibleMoves) {
        int result = minimax(player, opponent, togglePlayer(currentPlayer), move, choice);
        scores.push_back(result);
    }

    if (scores.size() == 0) return 0;

    if (currentPlayer == player) {
        vector<int>::iterator result;
        result = max_element(scores.begin(), scores.end());
        int maxIndex = distance(scores.begin(), result);
        choice->first = possibleActions[maxIndex].first;
        choice->second = possibleActions[maxIndex].second;
        return scores[maxIndex];
    }
    else {
        vector<int>::iterator result;
        result = min_element(scores.begin(), scores.end());
        int minIndex = distance(scores.begin(), result);
        choice->first = possibleActions[minIndex].first;
        choice->second = possibleActions[minIndex].second;
        return scores[minIndex];
    }

    // some error must've occurred
    return -1;
}
pair<int, int> Ai::aiMove(int aiChoice, int playerChoice, Board board) {
    vector<int> boardArray = board.asArray();
    pair<int, int> choice = { 0, 0 };
    minimax(aiChoice, playerChoice, aiChoice, boardArray, &choice);
    return choice;
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