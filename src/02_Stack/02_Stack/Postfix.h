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
	static string PostfixForm(const string&); 
	static double Calculate(double* values, char* operands, string p_f, int count);//(const string& p_f, char* operands, double* values, int count) || (double* values, char* operands, string p_f, int count)
	static void GetOperands(double*& values, char*& operands, string p_f, int& count);//(const string& p_f, char*& operands, double*& values, int& count) || (string p_f, char*& operands, double*& values, int& count)
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

void TPostfix::GetOperands(double*& values, char*& operands, string p_f, int& count) {
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
	memcpy(values, new_values, sizeof(double) * count);
	memcpy(operands, new_operands, sizeof(char) * count);
}

string TPostfix::PostfixForm(const string& exp) {
	if (exp.length() == 0) {
		throw Exception("Input is uncorrect\n");
	}
	TStack<char> stack1(exp.length() + 1);
	TStack<char> stack2(exp.length() + 1);
	for (int i = 0; i < exp.length(); i++) {
		char sign = static_cast<char>(exp[i]);
		if (sign == ' ') {
			continue;
		}
		if (IsItOperation(sign)) {
			if (stack1.IsEmpty()) {
				stack1.Push(sign);
				continue;
			}
			if (Comparison(sign, stack1)) {
				while (!stack1.IsEmpty()) {
					stack2.Push(stack1.Top());
					stack1.Pop();
				}
				stack1.Push(sign);
			}
			else
				stack1.Push(sign);
		}

		if (sign == '(') {
			stack1.Push(sign);
		}
		if (isalpha(sign)) {
			stack2.Push(sign);
		}
		if (sign == ')') {
			int left_bracket_flag = 0;
			while (!stack1.IsEmpty()) {
				if (stack1.Top() != '(') {
					cout << stack1.Top() << endl;
					stack2.Push(stack1.Top());
					stack1.Pop();
					continue;
				}
				stack1.Pop();
				left_bracket_flag = 1;
				break;
			}
			if ((left_bracket_flag != 1) && (stack1.IsEmpty())) {
				throw Exception("Need bracket(\n");
			}
		}

	}
	while (!stack1.IsEmpty()) {
		stack2.Push(stack1.Top());
		stack1.Pop();
	}
	string postfix_form;

	while (!stack2.IsEmpty()) {
		postfix_form += stack2.Top();
		stack2.Pop();
	}

	for (int i = 0; i < postfix_form.length() / 2; i++)
		swap(postfix_form[i], postfix_form[postfix_form.length() - 1 - i]);

	return postfix_form;
}

double TPostfix::Calculate(double* values, char* operands, string p_f, int count)
{
	TStack<double> result_mas(p_f.length());
	for (int i = 0; i < p_f.length(); i++) {
		char sign = static_cast<char>(p_f[i]);
		if (isalpha(sign)) {
			for (int j = 0; j < count; j++) {
				if (operands[j] == sign) {
					result_mas.Push(values[j]);
					break;
				}
			}
			continue;
		}

		double first = result_mas.Top();
		result_mas.Pop();
		double second = result_mas.Top();
		result_mas.Pop();
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

		result_mas.Push(result);
	}
	return result_mas.Top();
};
