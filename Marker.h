#pragma once
#include <string>
using namespace std;

class Marker
{
public:
	string getState();
	string setState(string newState);
private:
	string state;
};

