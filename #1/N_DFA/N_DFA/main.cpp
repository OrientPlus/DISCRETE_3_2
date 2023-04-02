#include "Header.h"

using namespace std;

int main()
{
	DFA dfa;

	dfa.init("DFA.txt");

	if (!dfa.go("01111011"))
		cout << endl << "Invalid chain!" << endl;
	else
		cout << endl << "Valid chain!" << endl;

	system("pause");
	return 0;
}