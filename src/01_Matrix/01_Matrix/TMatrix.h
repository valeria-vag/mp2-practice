#ifndef _TMatrix_h
#define _TMatrix_h

#include <iostream>
#include <cmath>
#include <string>
#include <exception>

using namespace std;

class Exception : exception
{
private:
	const string msg;
public:
	Exception(string exc) : msg(exc) {};

	const char* what() const
	{
		return msg.c_str();
	}
};

////////////////////////////////////////////////////////////////////
//VECTOR
////////////////////////////////////////////////////////////////////

template<class ValType>
class TVector
{
protected:
	ValType* elem;
	int size;
	int StartIdx;

public:
	TVector(int _size = 10, int _StartIdx = 0);
	TVector(const TVector&);
	virtual ~TVector();

	TVector operator+(const TVector&);
	TVector operator-(const TVector&);
	ValType operator*(const TVector&);
	TVector operator+(ValType);
	TVector operator-(ValType);
	TVector operator*(ValType);
	const TVector& operator=(const TVector&);

	ValType& operator[](int);
	const ValType& operator[](int) const;

	float Length() const;
	int GetSize() const;
	int GetStartIdx() const;

	bool operator==(const TVector&) const;
	bool operator!=(const TVector&) const;

	template<typename ValType> friend istream& operator>>(istream&, TVector<ValType>&);
	template<typename ValType> friend ostream& operator<<(ostream&, const TVector<ValType>&);
};

template<class ValType>
TVector<ValType>::TVector(int _size, int _StartIdx)
{
	if (_size < 0)
		throw Exception("Not correct size of vector!");

	if (_StartIdx < 0)
		throw Exception("Not correct index of vector!");

	size = _size;
	StartIdx = _StartIdx;

	if (size == 0)
		elem = NULL;
	else
	{
		elem = new ValType[size];
		for (int i = 0; i < size; i++)
			elem[i] = 0;
	}
};

template<class ValType>
TVector<ValType>::TVector(const TVector& _copy)
{
	size = _copy.size;
	StartIdx = _copy.StartIdx;

	if (size == 0)
		elem = NULL;
	else
	{
		elem = new ValType[size];
		for (int i = 0; i < size; i++)
			elem[i] = _copy.elem[i];
	}
};

template<class ValType>
TVector<ValType>::~TVector()
{
	size = 0;
	StartIdx = 0;

	delete[] elem;
	elem = NULL;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& _add)
{
	if (size != _add.size)
		throw Exception("Not correct size of vectors!");

	if (StartIdx != _add.StartIdx)
		throw Exception("Not correct index of vectors!");

	TVector<ValType> res(size, StartIdx);

	for (int i = 0; i < size; i++)
		res.elem[i] = elem[i] + _add.elem[i];

	return res;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& _sub)
{
	if (size != _sub.size)
		throw Exception("Not correct size of vectors!");

	if (StartIdx != _sub.StartIdx)
		throw Exception("Not correct index of vectors!");

	TVector<ValType> res(size, StartIdx);

	for (int i = 0; i < size; i++)
		res.elem[i] = elem[i] - _sub.elem[i];

	return res;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(ValType _add)
{
	TVector<ValType> res(*this);

	for (int i = 0; i < size; i++)
		res.elem[i] += _add;

	return res;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(ValType _sub)
{
	TVector<ValType> res(*this);

	for (int i = 0; i < size; i++)
		res.elem[i] -= _sub;

	return res;
};

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& _num)
{
	if (size != _num.size)
		throw Exception("Not correct size of vectors!");

	if (StartIdx != _num.StartIdx)
		throw Exception("Not correct index of vectors!");

	ValType res = 0;

	for (int i = 0; i < size; i++)
		res += (elem[i] * _num.elem[i]);

	return res;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(ValType _num)
{
	TVector<ValType> res(*this);

	for (int i = 0; i < size; i++)
		res.elem[i] *= _num;

	return res;
};

template<class ValType>
bool TVector<ValType>::operator==(const TVector& _vector) const
{
	if ((size != _vector.size) || (StartIdx != _vector.StartIdx))
		return false;

	for (int i = 0; i < size; i++)
		if (elem[i] != _vector.elem[i])
			return false;

	return true;
};

template<class ValType>
bool TVector<ValType>::operator!=(const TVector& _vector) const
{
	return !(*this == _vector);
};

template<class ValType>
const TVector<ValType>& TVector<ValType>::operator=(const TVector& _copy)
{
	if (this == &_copy)
		return *this;

	if (size != _copy.size)
	{
		size = _copy.size;
		delete[] elem;
		elem = new ValType[size];
	}

	StartIdx = _copy.StartIdx;

	for (int i = 0; i < size; i++)
		elem[i] = _copy.elem[i];

	return *this;
};

template<class ValType>
ValType& TVector<ValType>::operator[](int idx)
{
	if ((idx < 0) || (idx >= size))
		throw Exception("Not correct index of vector!");

	return elem[idx];
};

template<class ValType>
const ValType& TVector<ValType>::operator[](int idx)const
{
	if ((idx < 0) || (idx >= size))
		throw Exception("Not correct index of vector!");

	return elem[idx];
};

template<class ValType>
float TVector<ValType>::Length() const
{
	float length = 0;

	for (int i = 0; i < size; i++)
		length += (elem[i] * elem[i]);

	return sqrt(length);
};

template<class ValType>
int TVector<ValType>::GetSize() const
{
	return size;
};

template<class ValType>
int TVector<ValType>::GetStartIdx() const
{
	return StartIdx;
};


template<class ValType>
istream& operator>>(istream& _in, TVector<ValType>& _vector)
{
	for (int i = 0; i < _vector.size; i++)
		_in >> _vector.elem[i];

	return _in;
};

template<class ValType>
 ostream& operator<<(ostream& os, const TVector<ValType>& tmp)
    {
        cout << "\n  ";
        for (int i = 0; i < tmp.GetStartIdx(); i++)
            os << "\t";
        for (int i = 0; i < tmp.size; i++)
        {
            os << tmp.elem[i] << "\t";
        }
        return os;
    };


////////////////////////////////////////////////////////////////////
//MATRIX
////////////////////////////////////////////////////////////////////

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int size = 10);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValType> >&);
	~TMatrix();

	const TMatrix& operator=(const TMatrix&);

	TMatrix operator+(const TMatrix&);
	TMatrix operator-(const TMatrix&);
	TMatrix operator*(const TMatrix&);

	TMatrix operator+(ValType);
	TMatrix operator-(ValType);
	TMatrix operator*(ValType);

	TVector<ValType> operator*(const TVector<ValType>&);

	bool operator==(const TMatrix&) const;
	bool operator!=(const TMatrix&) const;

	template<typename ValType> friend istream& operator>>(istream&, TMatrix<ValType>&);

	template<typename ValType> friend ostream& operator<<(ostream&, const TMatrix<ValType>&);
};

template<typename ValType>
TMatrix<ValType>::TMatrix(int _size) : TVector<TVector<ValType> >(_size)
{
	for (int i = 0; i < _size; i++)
		this->elem[i] = TVector<ValType>(_size - i, i);
};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& _copy) : TVector<TVector<ValType> >(_copy)
{};

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& _vector) : TVector<TVector<ValType> >(_vector)
{};

template<typename ValType>
TMatrix<ValType>::~TMatrix()
{};

template<typename ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& _copy)
{
	if (this == &_copy)
		return *this;

	if (this->size != _copy.size)
	{
		this->size = _copy.size;

		delete[] this->elem;
		this->elem = new TVector<ValType>[_copy.size];
	}

	for (int i = 0; i < this->size; i++)
		this->elem[i] = _copy.elem[i];

	return *this;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& _add)
{
	if (this->size != _add.size)
		throw Exception("Not correct size of adding matrix!");

	TMatrix<ValType> result(this->size);

	for (int i = 0; i < this->size; i++)
		result.elem[i] = this->elem[i] + _add.elem[i];

	return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& _sub)
{
	if (this->size != _sub.size)
		throw Exception("Not correct size of adding matrix!");

	TMatrix<ValType> result(this->size);

	for (int i = 0; i < this->size; i++)
		result.elem[i] = this->elem[i] - _sub.elem[i];

	return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& _factor)
{
	if (this->size != _factor.size)
		throw Exception("Not correct size of adding matrix!");

	TMatrix<ValType> result(this->size);

	for (int i = 0; i < this->size; i++)
		for (int j = this->elem[i].GetStartIdx(); j < this->size; j++)
			for (int k = i; k <= j; k++)
				result.elem[i][j - i] += this->elem[i][k - i] * _factor.elem[k][j - k];

	return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType _add)
{
	TMatrix<ValType> result(*this);

	for (int i = 0; i < this->size; i++)
		result[i] = result.elem[i] + _add;

	return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType _sub)
{
	TMatrix<ValType> result(*this);

	for (int i = 0; i < this->size; i++)
		result[i] = result.elem[i] - _sub;

	return result;
};

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType _factor)
{
	TMatrix<ValType> result(*this);

	for (int i = 0; i < this->size; i++)
		result[i] = result.elem[i] * _factor;

	return result;
};

template<typename ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& _factor)
{
	if (this->size != _factor.GetSize())
		throw Exception("Not correct size of adding vector!");

	TVector<ValType> result(this->size);

	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->elem[i].GetSize(); j++)
			result[i] += this->elem[i][j] * _factor[i + j];

	return result;
};

template<typename ValType>
bool TMatrix<ValType>::operator==(const TMatrix& _matrix) const
{
	if (this->size != _matrix.size)
		return false;

	for (int i = 0; i < this->size; i++)
		if (this->elem[i] != _matrix.elem[i])
			return false;

	return true;
};

template<typename ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& _matrix) const
{
	return !(*this == _matrix);
};

template<typename ValType>
istream& operator>>(istream& _in, TMatrix<ValType>& _matrix)
{
	for (int i = 0; i < _matrix.size; i++)
		_in >> _matrix.elem[i];

	return _in;
};


template<typename ValType>
ostream& operator<<(ostream& os, const TMatrix<ValType>& tmp)
    {
        for (int i = 0; i < tmp.GetSize(); i++)
        {
            os << tmp.elem[i];
        }
        return os;
    };


#endif
