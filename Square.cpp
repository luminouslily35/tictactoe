#include "Square.h"

Square::Square(char s) {
    state = s;
}

string Square::getState() {
    return state;
}

void Square::setState(string newState) {
    state = newState;
}