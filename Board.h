#pragma once
#include "Square.h"
#include <vector>
#include <string>
using namespace std;

class Board {
public:
	Board();
    string at(int x, int y);
    void set(int x, int y, string newState);
private:
    vector<vector<Square>> squares;
};