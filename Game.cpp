#include "Game.h"
#include "Ai.h"
#include "GameHelper.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <format>
#include <string>
using namespace std;


// constant declaration
const int PLAYER_X = 1;
const int PLAYER_O = 2;
const int EXIT_GAME = 3;

const int NO_WINNER = 0;
const int X_WIN = 1;
const int O_WIN = 2;
const int DRAW = 3;

const int X = 1;
const int O = 2;
const int BLANK_MARKER = 0;

static map<int, int> numberToMarker = {
    { 1, X },
    { 2, O },
    { 0, BLANK_MARKER}
};

static map<int, int> markerToNumber = {
    { X, 1 },
    { O, 2 }
};

Game::Game() {
    playerChoice = 0;
    aiChoice = 0;
    nextPlayer = 0;
    turn = 0;
}

void Game::setup() {
    cout << "Welcome to Tic Tac Toe for C++" << endl;
    int choice = selectMarker();
    Ai ai;

    while (choice != EXIT_GAME) {
        setPlayers(choice);
        reset();
        play(ai);
        choice = selectMarker();
    }
    cout << "Ending game" << endl;
}

int Game::selectMarker() {
    int choice = 0;
    bool validChoice = false;
    do {
        cout << "Please choose a marker:" << endl;
        cout << "1. X" << endl;
        cout << "2. O" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        if (choice == PLAYER_X || choice == PLAYER_O || choice == EXIT_GAME) validChoice = true;
        else cout << "You have made an incorrect choice." << endl;
    } while (!validChoice);
    return choice;
}

void Game::setPlayers(int choice) {
    cout << "You have selected " << numberToMarker[choice] << endl;
    if (choice == PLAYER_X) {
        cout << "You will go first" << endl;
    }
    else {
        cout << "You will go second" << endl;
    }
    playerChoice = choice;
    aiChoice = (choice == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

void Game::reset() {
    board.clear();
    nextPlayer = PLAYER_X;
    turn = 0;
}

void Game::switchPlayer(int current) {
    if (current == PLAYER_X) nextPlayer = PLAYER_O;
    else nextPlayer = PLAYER_X;
}

Board Game::getBoard() {
    return board;
}

void Game::play(Ai ai) {
    int winner = NO_WINNER;
    while (winner == NO_WINNER) {
        turn++;
        if (turn > 9) {
            winner = DRAW;
            break;
        }

        if (nextPlayer == playerChoice) {
            // player move
            cout << "Type a pair of numbers to make your move. (e.g. 1 2)" << endl;
            GameHelper::printBoard(board);
            
            // choose a coordinate
            vector<int> choice = playerTurn(board);
            int x = choice[0];
            int y = choice[1];
            // place marker on coordinate
            board.setAdjusted(x, y, playerChoice);
            cout << "You have placed a marker on (" << x << ", " << y << ")\n---" << endl;
            winner = GameHelper::checkForWin(x, y, playerChoice, board);
        }
        else {
            // ai move            
            cout << "The AI moves." << endl;
            vector<int> choice = ai.playRandom(board);
            int x = choice[0];
            int y = choice[1];
            board.setAdjusted(x, y, aiChoice);
            cout << "The AI has placed a marker on (" << x << ", " << y << ")\n---" << endl;
            winner = GameHelper::checkForWin(x, y, aiChoice, board);
        }

        //check for a win
        if (winner == NO_WINNER) {
            switchPlayer(nextPlayer);
        }
    }

    if (winner == playerChoice) {
        cout << "You win!" << endl;
        GameHelper::printBoard(board);
    } else if (winner == aiChoice) {
        cout << "The AI wins." << endl;
        GameHelper::printBoard(board);
    } else if (winner == DRAW) {
        cout << "It's a draw!" << endl;
        GameHelper::printBoard(board);
    }
    cout << "Starting a new game." << endl;
}


bool Game::areInvalidCoordinates(int x, int y) {
    return x < 1 || x > 3 || y < 1 || y > 3;
}

vector<int> Game::playerTurn(Board board) {
    int x = 0;
    int y = 0;
    while (!GameHelper::isValidPlayerMove(x, y, board)) {
        cin >> x >> y;
        if (areInvalidCoordinates(x, y)) {
            cout << "These coordinates are not valid." << endl;
            cout << "Please input another x, y value." << endl;
        }
        else if (board.isTakenAdjusted(x, y)) {
            cout << "This square is currently occupied." << endl;
            cout << "Please input another x, y value." << endl;
        }
    }
    vector<int> choice = {x, y};
    return choice;
}






