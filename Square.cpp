#include "Square.h"

Square::Square(string s) {
    state = s;
}

string Square::getState() {
    return state;
}

void Square::setState(string newState) {
    state = newState;
}