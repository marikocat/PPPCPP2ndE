#include "..\std_lib_facilities.h"

class B1 {
public:
	virtual void vf() { cout << "B1:vf()\n"; }
	void f() { cout << "B1:f()\n"; }
	virtual void pvf() = 0;
};

class D1 : public B1 {
public:
	void vf() { cout << "D1:vf()\n"; }
	void f() { cout << "D1:f()\n"; }
	void pvf() { cout << "D1:pvf()\n"; }
};

class D2 : public D1 {
public:
	void pvf() { cout << "D2:pvf()\n"; }
};

int main()
{
	// B1 ob; abstract class
	// ob.vf();
	// ob.f();

	D1 ob2;
	ob2.vf();
	ob2.f();
	ob2.pvf();

	B1& r = ob2;
	r.vf();
	r.f();
	r.pvf();

	D2 ob;
	ob.vf();
	ob.f();
	ob.pvf();
}