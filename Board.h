#pragma once
#include "Square.h"
#include <vector>
#include <string>
using namespace std;

class Board {
public:
	Board();
    int atPosition(int x, int y);
    void setPosition(int x, int y, int value);
    int atAdjusted(int x, int y);
    void setAdjusted(int x, int y, int newState);
    void clear();
    bool isTakenAdjusted(int x, int y);
    vector<int> asArray();
    static Board asGrid(vector<int> arr);
private:
    vector<vector<int>> squares;
};