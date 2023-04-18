#include "..\std_lib_facilities.h"

class A {
public:
	virtual void f() = 0;
};

class C : public A {
	void f() { cout << "C::f()"; }
};

class B {
protected:
	B() {}
};

class D : public B {

};

int main()
{
	//A a;
	//B b;
	C c;
	D d;
}