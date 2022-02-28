#pragma once
#include "Board.h"
#include "Square.h"

//#include <vector>
//using namespace std;

class Game {
public:
    Game();
    int selectMarker();
    void setup();
    void setPlayers(int);
    void reset();
    void switchPlayer(int currentPlayer);
    void play();
    void clearBoard();
    string atAdjusted(int x, int y);
    int checkForWin(int, int, string);
    void playerWins();
    void aiWins();
    void draw();
    void setAdjusted(int x, int y, string marker);
    bool winByRow(int x, string marker);
    bool winByColumn(int y, string marker);
    bool winByDiagonal(string marker);
    void printBoard();
    bool isValidPosition(int x, int y);
    vector<int> playerTurn();
    vector<int> aiTurn() ;
    bool isTaken(int x, int y);

    bool areInvalidCoordinates(int x, int y);

    vector<int> findWinningPlay(const vector< vector<int> > & line);
    vector<int> preventLosingPlay(const vector< vector<int> > & line);
    vector<int> playRandom();
    vector<int> playCorner();
    
private:
    Board board;
    int nextPlayer;
    int playerChoice;
    int aiChoice;
    int turn;
    
    vector<vector<vector<int>>> lines;
};