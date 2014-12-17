#include "Tools.h"

#include <random>
#include <ctime>
#include <iostream>

using namespace std;

int Tools::randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}

void Tools::pause(bool have_newline){
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(200, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(200, '\n');
}

