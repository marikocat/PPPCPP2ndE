#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

template<typename T, int N>
class Pool
{
	T p[N];
	bool used[N];
	int num_unused;
public:
	Pool() : p(), used(), num_unused(N) {}
	T* get();
	void free(T* obj);
	int available() const;
};

template<typename T, int N>
T* Pool<T, N>::get()
{
	for (int i = 0; i < N; ++i)
		if (!used[i])
		{
			used[i] = true;
			--num_unused;
			return &p[i];
		}
	return nullptr;
}

template<typename T, int N>
void Pool<T, N>::free(T* obj)
{
	*obj = T();
	++num_unused;
	used[obj - p] = false;
}

template<typename T, int N>
int Pool<T, N>::available() const
{
	return num_unused;
}

struct Test_obj
{
	char a[80];
};

template<int N>
class Stack
{
public:
	Stack(); //make an N-byte stack
	void* get(int n); // allocate n bytes from the stack; return 0 if no free space
	void free(); // return the last value returned by get() to the stack
	int available() const; // number of available bytes
private:
	char data[N];
	char* top;
	short obj_sizes[N/100];
	int object_num;
};

template<int N>
Stack<N>::Stack() : data(), top(&data[0]), obj_sizes(), object_num(0) {}

template<int N>
void* Stack<N>::get(int n)
{
	if (n > available()) return nullptr;
	void* p = top;
	top += n;
	obj_sizes[object_num] = n;
	++object_num;
	return p;
}

template<int N>
void Stack<N>::free()
{
	--object_num;
	top -= obj_sizes[object_num];
	obj_sizes[object_num] = 0;
}

template<int N>
int Stack<N>::available() const
{
	return &data[N] - top;
}

void test_allocating_on_heap()
{
	const int objects_num = 10000;

	for (int n = 0; n < 3; ++n)
	{
		vector<char*> vc;
		auto start = chrono::system_clock::now();
		for (int i = 0; i < objects_num; ++i)
		{
			vc.push_back(new char[rand() % 1000]);
		}
		for (int i = 0; i < objects_num; ++i)
		{
			delete vc[i];
		}
		auto end = chrono::system_clock::now();
		auto res = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << res.count() << " milliseconds\n";
	}
	cout << '\n';

	for (int n = 0; n < 3; ++n)
	{
		vector<char*> vc;
		auto start = chrono::system_clock::now();
		for (int i = 0; i < objects_num; ++i)
		{
			vc.push_back(new char[rand() % 1000]);
		}
		for (int i = objects_num - 1; i >= 0; --i)
		{
			delete vc[i];
		}
		auto end = chrono::system_clock::now();
		auto res = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << res.count() << " milliseconds\n";
	}
	cout << '\n';

	for (int n = 0; n < 3; ++n)
	{
		vector<char*> vc;
		vector<int> vn(objects_num);
		iota(vn.begin(), vn.end(), 0);
		random_shuffle(vn.begin(), vn.end());
		auto start = chrono::system_clock::now();
		for (int i = 0; i < objects_num; ++i)
		{
			vc.push_back(new char[rand() % 1000]);
		}
		for (int i = 0; i < objects_num; ++i)
		{
			delete vc[vn[i]];
		}
		auto end = chrono::system_clock::now();
		auto res = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << res.count() << " milliseconds\n";
	}
	cout << '\n';
}

void test_pool()
{
	const int objects_num = 10000;
	cout << "size of test object: " << sizeof(Test_obj) << '\n';
	for (int n = 0; n < 3; ++n)
	{
		Pool<Test_obj, objects_num> pool;
		Test_obj* data[objects_num];
		auto start = chrono::system_clock::now();
		for (int i = 0; i < objects_num; ++i)
		{
			data[i] = pool.get();
		}
		for (int i = 0; i < objects_num; ++i)
		{
			pool.free(data[i]);
		}
		auto end = chrono::system_clock::now();
		auto res = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << res.count() << " milliseconds for a pool\n";
	}
	cout << '\n';
}

void test_stack()
{
	const int objects_num = 10000;
	for (int n = 0; n < 3; ++n)
	{
		Stack<80 * objects_num> stack;
		void* data[objects_num];
		auto start = chrono::system_clock::now();
		for (int i = 0; i < objects_num; ++i)
		{
			data[i] = stack.get(rand() % 1000);
		}
		for (int i = 0; i < objects_num; ++i)
		{
			stack.free();
		}
		auto end = chrono::system_clock::now();
		auto res = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << res.count() << " milliseconds for a stack\n";
	}
	cout << '\n';
}

int main()
{
	test_allocating_on_heap();
	for (int i = 0; i < 3; ++i)
		test_pool();
	for (int i = 0; i < 3; ++i)
		test_stack();
}