#pragma once
#include "Board.h"

class Ai
{
public:
	void minimax(int aiChosen, Board board);
	int findWinner(Board board);
	int scoreBoard(int aiChosen, Board board);
	vector<int> aiMove(Board board);
	vector<int> playRandom(Board board);
};