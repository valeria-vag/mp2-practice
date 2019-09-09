
// ifndef не забыть!
template <class ValType>
class Vector
{
	protected
		int size;
	ValType* elems;
	int StartIndex;
public:
	TVector(int size = 10; int StartIndex = 0);
	TVector(const TVector&);
	~TVector();
	
	bool operator==(const TVector&)const;
	bool operator!=(const TVector&)const;

	TVector operator+(ValType);
	TVector operator-(ValType);
	TVector operator*(ValType);

	TVector operator+(const TVector&);
	TVector operator-(const TVector&);

	ValType operator*(const TVector&);
	ValType Length()const;
	int Size()const;
	int StartIndex()const;

	friend ostream &operator<<(ostream&, const vector&);
	friend istream &operator>>(istream&, TVector&);

	ValType &operator[](int index);

	//Исключения!
	/////////////////////////////////////////////////////


};