#include "..\std_lib_facilities.h"

class B1 {
public:
	virtual void vf() { cout << "B1:vf()\n"; }
	void f() { cout << "B1:f()\n"; }
};

class D1 : public B1 {
public:
	void vf() { cout << "D1:vf()\n"; }
	void f() { cout << "D1:f()\n"; }
};

int main()
{
	B1 ob;
	ob.vf();
	ob.f();

	D1 ob2;
	ob2.vf();
	ob2.f();

	B1& r = ob2;
	r.vf();
	r.f();
}