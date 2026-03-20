// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"
#include "SimpleUI.h"
// Main program

int main ()
{
    // TODO: Add your program code here
	cout << "Lab3_StudentDB started." << endl << endl;
	StudentDb db1;
	SimpleUI view(db1);
	view.run();
	return 0;
}
