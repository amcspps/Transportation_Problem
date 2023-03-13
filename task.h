#pragma once
#include "vector_t.h"
class Task {
public:
	Task(Matrix C, vector_t a, vector_t b) {
		_a = a;
		_b = b;
		_C = C;
	};
	void bpe();
	void print() { std::cout << _result; }
private:
	vector_t _a;
	vector_t _b;
	Matrix _C;
	vector_t _result;
};