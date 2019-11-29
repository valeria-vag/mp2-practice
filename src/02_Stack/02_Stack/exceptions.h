#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Exception : public exception {
private:
	string msg;
public:
	Exception(string _msg) : msg(_msg) {};
	const char* what() const noexcept {
		return msg.c_str();
	}
};
#endif
