#pragma once
#include "Board.h"

class Ai
{
public:
	int minimax(int player, int opponent, int currentPlayer, vector<int> board, pair<int, int>* choice);
	int scoreBoard(int player, int opponent, vector<int> boardArray);
	int findWinner(int player, int opponent, Board board);
	int togglePlayer(int choice);
	pair<int, int>  aiMove(int aiChoice, int playerChoice, Board board);
	vector<int> playRandom(Board board);
	vector<vector<int>> findPossibleMoves(int currentPlayer, vector<int> boardArray, vector<pair<int, int>>* possibleActions);
};

