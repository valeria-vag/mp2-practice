#include <iostream>
#include <string>

#include "Postfix.h"
#include "TStack.h"
#include "exceptions.h"

using namespace std;

void main() {
	string str;
	string operands;
	try {
		cout << "Enter expression " << endl;
		getline(cin, str);
		string p_f = TPostfix::PostfixForm(str);
		cout << "Postfix form: " << endl;
		cout << p_f << endl;
		int count = TPostfix::GettingCount(p_f);
		double* values = new double[count];
		TPostfix::GettingValues(values, operands, p_f, count);
		double result = TPostfix::Calculate(values, operands, p_f);
		cout << "Result: " << result << endl;
	}
	catch (const Exception& ex) {
		cout << ex.what() << endl << endl;
	}
	system("pause");
}