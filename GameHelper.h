#pragma once
#include "Board.h"

class GameHelper
{
public:
	//static int findWinner(Board board);
	static int checkForWin(int x, int y, int marker, Board board);
	static bool winByRow(int x, int marker, Board board);
	static bool winByColumn(int y, int marker, Board board);
	static bool winByDiagonal(int marker, Board board);
	static bool isValidPlayerMove(int x, int y, Board board);
	static void printBoard(Board board);
private:
	static string repr(int marker);
};

