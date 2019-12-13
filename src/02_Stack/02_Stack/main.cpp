#include <iostream>
#include <string>

#include "Postfix.h"
#include "TStack.h"
#include "exceptions.h"

using namespace std;

void main() {
	string str;
	int count = 0;
	try {
		cout << "Enter expression " << endl;
		getline(cin, str);
		string p_f = TPostfix::PostfixForm(str);
		cout << "Postfix form: " << endl;
		cout << p_f << endl;
		char* operands = new char[p_f.length()];
		double* values = new double[p_f.length()];
		TPostfix::GetOperands(values, operands, p_f,  count);
		double result = TPostfix::Calculate(values, operands, p_f, count);
		cout << "Result: " << result << endl;
	}
	catch (const Exception& ex) {
		cout << ex.what() << endl << endl;
	}
	system("pause");
}