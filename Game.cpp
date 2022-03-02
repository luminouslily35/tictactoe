#include "Game.h"
#include "Ai.h"
#include "GameHelper.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <format>
#include <string>
#include <stdexcept>
#include <sstream>
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
    string inputString;
    do {
        inputString = "";
        cout << "Please choose a marker:" << endl;
        cout << "1. X" << endl;
        cout << "2. O" << endl;
        cout << "3. Exit" << endl;
        try {
            getline(cin, inputString);
            if (inputString == "X" || inputString == "O") {
                throw invalid_argument("Please type 1 for X and 2 for O instead.");
            }
            // try to convert to int
            size_t pos;
            try {
                choice = stoi(inputString, &pos, 10);
                if (inputString.length() != 1) {
                    throw exception();
                }
            }
            catch (const exception& e) {
                throw invalid_argument("invalid argument received");
            }

            if (choice == PLAYER_X || choice == PLAYER_O || choice == EXIT_GAME) validChoice = true;
            else
                throw invalid_argument("number not 1, 2, or 3");
        }
        catch (const exception& e) {
            cout << "ERROR: " << e.what() << endl;
        }
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
            cout << "Note: Do not add commas or parentheses when making your decision!" << endl;
            GameHelper::printBoard(board);
            
            // choose a coordinate
            pair<int, int> choice = playerTurn(board);
            int x = choice.first;
            int y = choice.second;
            // place marker on coordinate
            board.setAdjusted(x, y, playerChoice);
            cout << "You have placed a marker on (" << x << ", " << y << ")\n---" << endl;
            winner = GameHelper::checkForWin(x, y, playerChoice, board);
        }
        else {
            // ai move            
            cout << "The AI moves." << endl;
            pair<int, int> choice = ai.aiMove(aiChoice, playerChoice, board);
            int x = choice.first;
            int y = choice.second;
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

pair<int, int> Game::playerTurn(Board board) {
    int x = 0;
    int y = 0;
    string playerInput;
    bool validMove = false;

    while (!validMove) {
        try {
            getline(cin, playerInput);
            istringstream is (playerInput);
            vector<string> v((istream_iterator<string>(is)), istream_iterator<string>());

            if (v.size() > 2) {
                throw exception("too many arguments");
            }
            else if (v.size() < 2) {
                throw exception("too few arguments");
            }
            
            vector<int> numbers;
            for (string str : v) {
                if (str.length() != 1) {
                    throw exception("invalid argument");
                }
                size_t pos;
                int result = 0;
                try {
                    result = stoi(str, &pos, 10);
                }
                catch (const exception& e) {
                    throw exception("invalid argument");
                }

                if (result > 3 || result < 1) {
                    throw exception("coordinate out of bounds");
                }
                numbers.push_back(result);
            }
            x = numbers[0];
            y = numbers[1];

            if (areInvalidCoordinates(x, y)) {
                throw exception("invalid coordinates");
            }
            else if (board.isTakenAdjusted(x, y)) {
                throw exception("this coordinate is occupied");
            }
            validMove = true;
        }
        catch (const exception& e) {
            cout << "ERROR: " << e.what() << endl;
        }


    }
    pair<int, int> choice = {x, y};
    return choice;
}






