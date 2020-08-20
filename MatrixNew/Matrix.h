
#ifndef _Header_
#define _Header_

#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Matrix
{
	int rows, columns;
	int **p;


public:

	Matrix();
	Matrix(int rows, int columns);
	Matrix(const Matrix &other);
	Matrix & operator= (const Matrix &other);
	bool operator== (const Matrix &other) const;
	Matrix operator* (const int &value) const;
	Matrix operator+ (const Matrix &other) const;
	int GetValue(int row, int column) const;
	void Show() const;
	int GetSize() const;
	int * operator [] (int value) const;
	void operator () (int value);
	friend ostream& operator<<(ostream&out, const Matrix &m);
	friend istream& operator>>(istream& in, Matrix &m);
	void* operator new(std::size_t size);
	void operator delete(void* p);
	~Matrix();

};

#endif