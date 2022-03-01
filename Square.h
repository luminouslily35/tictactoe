#pragma once
#include <string>
using namespace std;

class Square {
public:
	Square() : state(" ") {};
    Square(string s);
	string getState();
	void setState(string newState);
private:
	string state; 
};