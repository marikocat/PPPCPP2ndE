#include "..\std_lib_facilities.h"

namespace MyNamespace {
	class Iterator {
	public:
		virtual double* next() = 0;
	};

	class Vector_iterator : public Iterator {
	public:
		Vector_iterator(const vector<double>& dv) : v{dv} {}
		double* next();
	private:
		vector<double> v;
		int n{ 0 };
	};

	double* Vector_iterator::next()
	{
		if (n == v.size()) return 0;
		return &v[n++];
	}

	class List_iterator : public Iterator {
	public:
		List_iterator(const list<double>& dl) : l{dl} {}
		double* next();
	private:
		list<double> l;
		int n{ 0 };
	};

	double* List_iterator::next()
	{
		if (n == l.size()) return 0;
		return &*std::next(l.begin(), n++);
	}

	void print(Iterator& it)
	{
		double* p;
		while (p = it.next())
		{
			cout << *p << '\n';
		}
	}
}

int main()
try
{
	using namespace MyNamespace;

	vector<double> vect{ 1.1,2.2, 3.3, 4.4, 5.5 };
	Vector_iterator vi{ vect };
	print(vi);

	list<double> ls{ 1.1,2.2, 3.3, 4.4, 5.5 };
	List_iterator li{ ls };
	print(li);

	return 0;
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}