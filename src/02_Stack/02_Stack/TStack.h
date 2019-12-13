#ifndef _TSTACK_H_ 
#define _TSTACK_H_
#include "exceptions.h"
using namespace std;

template<typename ValType>
class TStack {
private:
	int size;
	int top;
	ValType* elem;
public:
	TStack(int);
	TStack(const TStack&);
	~TStack();

	bool IsEmpty()const;
	bool IsFull()const;

	void Push(ValType); 
	void Pop(); 
	ValType Top();



};

template<typename ValType>
TStack<ValType>::TStack(int _size) {

	if (_size <= 0)
		throw Exception("Size is not correct\n");

	size = _size;
	elem = new ValType[size];
	top = 0;
	for (int i = 0; i < size; i++) {
		elem[i] = 0;
	}
}

template<typename ValType>
TStack<ValType>::TStack(const TStack& tmp) {
	size = tmp.size;
	top = tmp.top;
	for (int i; i < size; i++) {
		elem[i] = tmp.elem[i];
	}
}

template<typename ValType>
TStack<ValType>::~TStack() {
	top = 0;
	size = 0;
	delete[] elem;
}

template<typename ValType>
void TStack<ValType>::Push(ValType new_elem) {
	if (IsFull()) {
		throw Exception("Stack is full\n");
	}
	elem[top] = new_elem;
	top++;
}

template<typename ValType>
ValType TStack<ValType>::Top() {
	if (IsEmpty()) {
		throw Exception("Stack is empty\n");
	}
	return elem[top - 1];
}

template<typename ValType>
bool TStack<ValType>::IsEmpty()const {
	return (top == 0);
}

template<typename ValType>
bool TStack<ValType>::IsFull()const {
	return (size == top);
}

template<typename ValType>
void TStack<ValType>::Pop() {
	if (IsEmpty()) {
		throw Exception("Stack is empty\n");
	}
	top--;
}

#endif
