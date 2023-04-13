#include "..\std_lib_facilities.h"

class B1 {
public:
	virtual void vf() { cout << "B1:vf()\n"; }
	void f() { cout << "B1:f()\n"; }
};

int main()
{
	B1 ob;
	ob.vf();
	ob.f();
}