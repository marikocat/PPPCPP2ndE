#include <iostream>
using namespace std;

class Tracer {
	string s;
public:
	Tracer(const string& ss);
	Tracer(const Tracer& t);
	~Tracer();

	Tracer& operator=(const Tracer& t);

	string get_s() const { return s; }
};

ostream& operator<<(ostream& os, const Tracer& t)
{
	cout << t.get_s();
	return os;
}

Tracer::Tracer(const string& ss)
	: s{ ss }
{
	cout << "constructor: " << s << '\n';
}

Tracer::Tracer(const Tracer& t)
	: s{ t.s }
{
	cout << "copy constructor: " << s << '\n';
}

Tracer::~Tracer()
{
	cout << "destructor: " << s << '\n';
}

Tracer& Tracer::operator=(const Tracer& t)
{
	s = t.s;
	cout << "copy assignment: " << s << '\n';
	return *this;
}

struct A {
	Tracer t;
	A(const Tracer& tt) : t{ tt } {}
};

Tracer t3{ "global" };

int main()
{
	Tracer t1{ "hi" };
	cout << t1 << '\n';

	Tracer t2{ "hello" };
	cout << t2 << '\n';
	A ob1{ t2 };

	Tracer* pt = new Tracer{ "new" };
	cout << *pt << '\n';
	delete pt;

	Tracer t3{ "temp" };
	t3 = t1;
}