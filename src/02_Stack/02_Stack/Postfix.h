#include <iostream>
#include <string>

#include "Tstack.h"
#include "exceptions.h"

using namespace std;

class TPostfix {
private:
	static int Priority(const char);
	static bool Comparison(char, TStack<char>&);
	static bool IsItOperation(const char);
public:
	static string PostfixForm(string);
	static double Calculate(double*, char*, string, int);
	static void GettingOperands(string, char*&, double*&, int&);
};

int TPostfix::Priority(const char sign) {
	switch (sign) {
	case '+': return 2;
	case '-': return 2;
	case '*': return 1;
	case '/': return 1;
	default: return 3;
	}
}
bool TPostfix::Comparison(char exp, TStack<char>& pop_elem) {
	return (Priority(pop_elem.Top()) < Priority(exp));
};

bool TPostfix::IsItOperation(const char oper) {
	return ((oper == '*') || (oper == '/') || (oper == '+') || (oper == '-'));
}

void TPostfix::GettingOperands(string p_f, char*& operands, double*& values, int& count) {
	int curr = 0;
	double value = 0;
	char* new_operands = new char[count];
	double* new_values = new double[count];
	for (int i = 0; i < p_f.length(); i++) {
		if (isalpha(p_f[i])) {
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
	memcpy(values, new_values, sizeof(double) * count);//скопировали 2ое в 1ое
	memcpy(operands, new_operands, sizeof(char) * count);//скопировали 2ое в 1ое
}


string TPostfix::PostfixForm(string exp) {
	if (exp.length() == 0) 
		throw Exception("Input is uncorrect\n");

	TStack<char>Stack1(exp.length() + 1);
	TStack<char>Stack2(exp.length() + 1);

	for (int i = 0; i < exp.length(); i++) {
		char sign = static_cast<char>(exp[i]);
		if (sign == ' ')
			continue;
		if (IsItOperation(sign)) {
			if (Stack1.IsEmpty()) {
				Stack1.Push(sign);
				continue;
			}
			if (Comparison(sign, Stack1)) {
				while (!Stack1.IsEmpty()) {
					Stack2.Push(Stack1.Top());//верхн эл-т из 1го стека перекладываем во 2й
					Stack1.Pop();//уменьшаем 1й стек
				}
				Stack1.Push(sign);
			}
			else
				Stack1.Push(sign);
		}

		if (sign == '(') {
			Stack1.Push(sign);
		}
		if (isalpha(sign)) {
			Stack2.Push(sign);
		}
		if (sign == ')') {
			int left_bracket_flag = 0;
			while (!Stack1.IsEmpty()) {
				if (Stack1.Top() != '(') {
					cout << Stack1.Top() << endl;
					Stack2.Push(Stack1.Top());
					Stack1.Pop();
					continue;
				}
				Stack1.Pop();
				left_bracket_flag = 1;
				break;
			}
			if ((left_bracket_flag != 1) && (Stack1.IsEmpty())) {
				throw Exception("Need bracket '(' \n");
			}
		}

	}
	while (!Stack1.IsEmpty()) {
		Stack2.Push(Stack1.Top());
		Stack1.Pop();
	}
	string postfix_form;

	while (!Stack2.IsEmpty()) {
		postfix_form += Stack2.Top();
		Stack2.Pop();
	}

	for (int i = 0; i < postfix_form.length() / 2; i++)
		swap(postfix_form[i], postfix_form[postfix_form.length() - 1 - i]);

	return postfix_form;
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
