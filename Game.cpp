#include "Game.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <format>
#include <string>
using namespace std;

Game::Game() {
    playerChoice = 0;
    aiChoice = 0;
    nextPlayer = 0;
    turn = 0;
    //playerWins = 0;
    //aiWins = 0;
    //draws = 0;
}

static map<int, string> numberToMarker = {
    { 1, "X" },
    { 2, "O" }
};

static map<string, int> markerToNumber = {
    { "X", 1 },
    { "O", 2 }
};

int Game::selectMarker() {
    int choice = 0;
    bool validChoice = false;
    do {
        cout << "Please choose a marker:" << endl;
        cout << "1. X" << endl;
        cout << "2. O" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3) validChoice = true;
        else cout << "You have made an incorrect choice." << endl;
    } while (!validChoice);
    return choice;
}

const int EXIT_GAME = 3;
const int MARKER_X = 1;
const int MARKER_O = 2;

const int NO_WINNER = 0;
const int X_WIN = 1;
const int O_WIN = 2;
const int DRAW = 3;


void Game::setup() {
    cout << "Welcome to Tic Tac Toe for C++" << endl;
    int choice = selectMarker();
    while (choice != EXIT_GAME) {
        setPlayers(choice);
        reset();
        play();
        choice = selectMarker();
    }
    cout << "Ending game" << endl;
}

void Game::setPlayers(int choice) {
    cout << "You have selected " << numberToMarker[choice] << endl;
    if (choice == MARKER_X) {
        cout << "You will go first" << endl;
    }
    else {
        cout << "You will go second" << endl;
    }
    playerChoice = choice;
    aiChoice = (choice == MARKER_X) ? MARKER_O : MARKER_X;
}

void Game::reset() {
    clearBoard();
    nextPlayer = 1;
    turn = 0;
}

void Game::switchPlayer(int current) {
    if (current == MARKER_X) nextPlayer = MARKER_O;
    else nextPlayer = MARKER_X;
}


void Game::play() {
    int winner = NO_WINNER;
    while (winner == NO_WINNER) {
        turn++;
        if (turn > 9) {
            winner = DRAW;
            break;
        }

        if (nextPlayer == playerChoice) {
            // player move
            cout << "It's your move." << endl;
            cout << "Place a coordinate (e.g. 1 2)" << endl;
            printBoard();
            
            // choose a coordinate
            vector<int> choice = playerTurn();
            int x = choice[0];
            int y = choice[1];
            // place marker on coordinate
            setAdjusted(x, y, numberToMarker[playerChoice]);
            cout << "You have placed a marker on (" << x << ", " << y << ")\n---" << endl;
            winner = checkForWin(x, y, numberToMarker[playerChoice]);
        }
        else {
            // ai move            
            cout << "It's the AI's move." << endl;
            vector<int> choice = aiTurn();
            int x = choice[0];
            int y = choice[1];
            setAdjusted(choice[0], choice[1], numberToMarker[aiChoice]);
            cout << "The AI has placed a marker on (" << x << ", " << y << ")\n---" << endl;
            winner = checkForWin(x, y, numberToMarker[aiChoice]);
        }

        //check for a win
        if (winner == NO_WINNER) {
            switchPlayer(nextPlayer);
        }
    }

    if (winner == playerChoice) {
        playerWins();
        printBoard();
    } else if (winner == aiChoice) {
        aiWins();
        printBoard();
    } else if (winner == DRAW) {
        draw();
        printBoard();
    }
    cout << "Starting a new game." << endl;
}

void Game::clearBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board.set(i, j, " ");
}

// need to subtract by 1 because tictactoe's first row/colum starts at 1, not 0
string Game::atAdjusted(int x, int y) {
    return board.at(x-1, y-1);
}

void Game::setAdjusted(int x, int y, string marker) {
    board.set(x-1, y-1, marker);
}

bool Game::winByRow(int x, string marker) {
    return (atAdjusted(x, 1) == marker &&
        atAdjusted(x, 2) == marker &&
        atAdjusted(x, 3) == marker);
}
bool Game::winByColumn(int y, string marker) {
    return (atAdjusted(1, y) == marker &&
        atAdjusted(2, y) == marker &&
        atAdjusted(3, y) == marker);
}

bool Game::winByDiagonal(string marker) {
    return (
        (atAdjusted(1, 1) == marker &&
            atAdjusted(2, 2) == marker &&
            atAdjusted(3, 3) == marker)
        ||
        (atAdjusted(1, 3) == marker &&
            atAdjusted(2, 2) == marker &&
            atAdjusted(3, 1) == marker)
        );
}

int Game::checkForWin(int x, int y, string marker) {
    if (winByRow(x, marker) || winByColumn(y, marker) || winByDiagonal(marker)) {
        return markerToNumber[marker];
    }
    return NO_WINNER;
}

void Game::playerWins() {
    cout << "You win!" << endl;
}

void Game::aiWins() {
    cout << "The AI wins." << endl;
}

void Game::draw() {
    cout << "It's a draw!" << endl;
}



void Game::printBoard() {
    string firstLine  = format("(1, )#  {}  #  {}  #  {}  #", atAdjusted(1, 1), atAdjusted(1, 2), atAdjusted(1, 3));
    string secondLine = format("(2, )#  {}  #  {}  #  {}  #", atAdjusted(2, 1), atAdjusted(2, 2), atAdjusted(2, 3));
    string thirdLine  = format("(3, )#  {}  #  {}  #  {}  #", atAdjusted(3, 1), atAdjusted(3, 2), atAdjusted(3, 3));
    cout << "      (, 1) (, 2) (, 3) " << endl;
    cout << "     ###################" << endl;
    cout << firstLine << endl;
    cout << "     ###################" << endl;
    cout << secondLine << endl;
    cout << "     ###################" << endl;
    cout << thirdLine << endl;
    cout << "     ###################" << endl;
}

bool Game::isValidPosition(int x, int y ) {
    // 1 <= x <= 3
    // 1 <= y <= 3
    return (!( x < 1 || x > 3 ||y < 1 || y > 3 ||isTaken(x, y)));
}

bool Game::isTaken(int x, int y) {
    string pos = atAdjusted(x, y);
    return (pos == "X" || pos == "O");
}

bool Game::areInvalidCoordinates(int x, int y) {
    return x < 1 || x > 3 || y < 1 || y > 3;
}

vector<int> Game::playerTurn() {
    int x = 0;
    int y = 0;
    while (!isValidPosition(x, y)) {
        cin >> x >> y;
        if (areInvalidCoordinates(x, y)) {
            cout << "These coordinates are not valid." << endl;
            cout << "Please input another x, y value." << endl;
        }
        else if (isTaken(x, y)) {
            cout << "This square is currently occupied." << endl;
            cout << "Please input another x, y value." << endl;
        }
    }
    vector<int> choice = {x, y};
    return choice;
}

vector<int> Game::aiTurn() {
    //bool found = false;

    //vector<int> c00 = {0, 0};
    //vector<int> c01 = {0, 1};
    //vector<int> c02 = {0, 2};
    //vector<int> c10 = {1, 0};
    //vector<int> c11 = {1, 1};
    //vector<int> c12 = {1, 2};
    //vector<int> c20 = {2, 0};
    //vector<int> c21 = {2, 1};
    //vector<int> c22 = {2, 2};

    //vector< vector<int> > line1 = {c00, c01, c02 };
    //vector< vector<int> > line2 = {c10, c11, c12 };
    //vector< vector<int> > line3 = {c20, c21, c22 };
    //vector< vector<int> > line4 = {c00, c10, c20 };
    //vector< vector<int> > line5 = {c01, c11, c21 };
    //vector< vector<int> > line6 = {c02, c12, c22 };
    //vector< vector<int> > line7 = {c00, c11, c22 };
    //vector< vector<int> > line8 = {c02, c11, c20 };

    //vector < vector< vector<int> > > allLines =
    //{line1, line2, line3, line4, line5, line6, line7, line8};

    //vector<int> coord;

    //for (int i = 0; i < 8; i++) {
    //    coord = findWinningPlay(allLines[i]);

    //    cout << "i: " << i << endl;
    //    //cout << coord[0] << ", " << coord[1] << endl;
    //    cout << "size: " << coord.size() << endl;

    //    if (coord.size() > 0) {
    //        set(coord[0], coord[1], aiMarker);
    //        return coord;
    //    }
    //}

    //for (int i = 0; i < 8; i++) {
    //    coord = preventLosingPlay(allLines[i]);

    //    cout << "i: " << i << endl;
    //    //cout << coord[0] << ", " << coord[1] << endl;
    //    cout << "size: " << coord.size() << endl;
    //    if (coord.size() > 0) {
    //        set(coord[0], coord[1], aiMarker);
    //        return coord;
    //    }
    //}

    //// Here, the AI might choose to do a couple of things
    //// If the AI is going second, and say the player has placed an X
    //// in the middle. Then the AI would definitely place at a corner.
    //if (turn == 2 && at(1, 1) == 'X') {
    //    coord = playCorner();
    //    set(coord[0], coord[1], aiMarker);
    //    return coord;
    //}

    // play like an idiot
    vector<int> coord = playRandom();
    return coord;

}


//vector<int> Game::findWinningPlay(const vector< vector<int> > & line) {
//    // the line consists of three coordinates, and inspect 
//    int aiMarkerCount = 0;
//    int emptyCount = 0;
//    vector<int> toSet;
//
//    for (int i = 0; i < 3; i++) {
//        // inspect the marker placed at this coordinate
//        vector<int> coord = line[i];
//        if (at(coord[0], coord[1]) == aiMarker)
//            aiMarkerCount++;
//        else if (at(coord[0], coord[1]) == ' ') {
//            emptyCount++;
//            toSet = coord;
//        }
//    }
//
//    if (!(aiMarkerCount == 2 && emptyCount == 1)) {
//        // clear contents of toSet
//        toSet.clear();
//    }
//
//    return toSet; 
//}
//
//vector<int> Game::preventLosingPlay(const vector< vector<int> > & line) {
//    int playerMarkerCount = 0;
//    int emptyCount = 0;
//    vector<int> toSet;
//
//    for (int i = 0; i < 3; i++) {
//        // inspect the marker placed at this coordinate
//        vector<int> coord = line[i];
//
//        cout << "coord: " << coord[0] << ", " << coord[1] << endl;
//
//        if (at(coord[0], coord[1]) == playerMarker)
//            playerMarkerCount++;
//        else if (at(coord[0], coord[1]) == ' ') {
//            emptyCount++;
//            toSet = coord;
//        }
//    }
//
//    if (!(playerMarkerCount == 2 && emptyCount == 1)) {
//        // clear contents of toSet
//        toSet.clear();
//    }
//    
//    return toSet; 
//}


vector<int> Game::playRandom() {
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (!isTaken(i, j)) {
                vector<int> toSet = {i, j};
                return toSet;
            }
        }
    }
}


// Plays one of the four corners at random
vector<int> Game::playCorner() {
    int choice = rand() % 4;
    vector<int> toSet;
    if (choice == 0) {
        toSet = {0, 0};
    } else if (choice == 1) {
        toSet = {0, 2};
    } else if (choice == 2) {
        toSet = {2, 0};
    } else if (choice == 3) {
        toSet = {2, 2};
    }
    return toSet;
}