#pragma once
#include "Board.h"
#include "Square.h"
#include "Ai.h"

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
    void play(Ai ai);
    bool isValidPosition(int x, int y);
    pair<int, int> playerTurn(Board board);
    bool areInvalidCoordinates(int x, int y);
    // getters
    Board getBoard();
    //public int getPlayerMarker();
    //public int getAiMarker();
    
private:
    Board board;
    int nextPlayer;
    int playerChoice;
    int aiChoice;
    int turn;
};