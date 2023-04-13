#include "..\std_lib_facilities.h"

class B2 {
public:
	virtual void pvf() = 0;
};

class D21 : public B2 {
public:
	void pvf() { cout << s << '\n'; }
private:
	string s{ "D21" };
};

class D22 : public B2 {
public:
	void pvf() { cout << i << '\n'; }
private:
	int i{ 22 };
};

void f(B2& ob)
{
	ob.pvf();
}

int main()
{
	D21 ob1;
	D22 ob2;
	f(ob1);
	f(ob2);
}