#pragma once
#include <string>
using namespace std;

class Square {
public:
	Square() : state(" ") {};
    Square(char s);
	string getState();
	void setState(string newState);
private:
	string state; 
};