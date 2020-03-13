#include <iostream>
#include <string>

#include "Tstack.h"
#include "exceptions.h"

using namespace std;

class TPostfix {
private:
	static int Priority(const char);
	static bool IsItOperation(const char);
public:
	static string PostfixForm(string);//образование постф формы
	static double Calculate(double*, char*, string, int);
	static void GettingOperands(string, char*&, double*&, int&);
};

int TPostfix::Priority(const char sign) {
	switch (sign) {
	case '(': return 1;
	case ')': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
    default: 
		throw Exception("Entered symbol is uncorrect\n");
	}
}


bool TPostfix::IsItOperation(const char oper) {
	return ((oper == '+') || (oper == '-') || (oper == '*') || (oper == '/') || (oper == ')') || (oper == '('));
}

void TPostfix::GettingOperands(string p_f, char*& operands, double*& values, int& count) {
	int curr = 0;
	double value = 0;
	char* new_operands = new char[p_f.length()];
	double* new_values = new double[p_f.length()];
	for (int i = 0; i < p_f.length(); i++) {
		if (isalpha(p_f[i])) { //проверка на символьность
			count++;
			int flag = 0;
			for (int j = 0; j < curr; j++) {
				if (new_operands[j] == p_f[i]) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				new_operands[curr] = p_f[i];
				cout << "Enter value of operand " << p_f[i] << endl;
				cin >> value;
				new_values[curr] = value;
				curr++;
			}
		}
	}
	count = curr;

	memcpy(values, new_values, sizeof(double) * count); //скоп новое в старое
	memcpy(operands, new_operands, sizeof(char) * count);
}

string TPostfix::PostfixForm(string exp) {
	if (exp.length() == 0) 
		throw Exception("Input is uncorrect\n");

	int countLBrack = 0;
	int countRBrack = 0;

	TStack<char>Stack1(exp.length() + 1); //операции
	TStack<char>Stack2(exp.length() + 1); //операнды

	for (int i = 0; i < exp.length(); i++) {
		char sign = static_cast<char>(exp[i]); //приведение типов
		if (sign == ' ')
			continue;
		if (IsItOperation(sign)) { 
			if (sign == '(') {
				countLBrack++;
				Stack1.Push(sign);
				continue;
			}
			if (sign == ')') {
				countRBrack++;
				while (!Stack1.IsEmpty() ) { 
					if (Stack1.Top() != '(') {
						Stack2.Push(Stack1.Top());
						Stack1.Pop();
						continue;
					}
					Stack1.Pop();
					break;
				}
				continue;
			}
			if ((Stack1.IsEmpty()) || (Priority(sign) > Priority(Stack1.Top()))) {
				Stack1.Push(sign);
				continue;
			}
			while ((!Stack1.IsEmpty()) && (Priority(sign) <= Priority(Stack1.Top()))) {
				Stack2.Push(Stack1.Top());
				Stack1.Pop();
			}
			Stack1.Push(sign);
			continue;
		}
		if (isalpha(sign)) {
			Stack2.Push(sign);
			continue;
		}
		throw Exception("Symbols are uncorrect");
	}
	if (countLBrack != countRBrack) {
		if (countLBrack < countRBrack)
			throw Exception("Left bracket is lost");
		else
			throw Exception("Right bracket is lost");
	}

	while (!Stack1.IsEmpty()) {
		Stack2.Push(Stack1.Top());
		Stack1.Pop();
	}
	string p_f;

	while (!Stack2.IsEmpty()) {
		p_f += Stack2.Top();
		Stack2.Pop();
	}

	for (int i = 0; i < p_f.length() / 2; i++)
		swap(p_f[i], p_f[p_f.length() - 1 - i]);

	return p_f;
}

double TPostfix::Calculate(double* values, char* operands, string p_f, int count)
{
	TStack<double> res(p_f.length());
	for (int i = 0; i < p_f.length(); i++) {
		char sign = static_cast<char>(p_f[i]);
		if (isalpha(sign)) {
			for (int j = 0; j < count; j++) {
				if (operands[j] == sign) {
					res.Push(values[j]);
					break;
				}
			}
			continue;
		}

		double first = res.Top();
		res.Pop();
		double second = res.Top();
		res.Pop();
		double result;

		switch (sign) {
		case '+':
			result = second + first;
			break;
		case '-':
			result = second - first;
			break;
		case '*':
			result = second * first;
			break;
		case '/':
			if (first == 0)
				throw Exception("Cannot divide by zero (\n");
			result = second / first;
			break;
		}

		res.Push(result);
	}
	return res.Top();
};

