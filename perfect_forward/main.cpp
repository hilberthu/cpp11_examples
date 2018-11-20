#include <iostream>

using namespace std;

void fun(int &x) { cout << "lvalue ref" << endl; }
void fun(int &&x) { cout << "rvalue ref" << endl; }
void fun(const int &x) { cout << "const lvalue ref" << endl; }
void fun(const int &&x) { cout << "const rvalue ref" << endl; }

template<typename T>
void PerfectForward(T &&t) { fun(std::forward<T>(t)); }

int main(int argc, char* argv[])
{
	PerfectForward(10);           // rvalue ref

	int a;
	PerfectForward(a);            // lvalue ref
	PerfectForward(std::move(a)); // rvalue ref

	const int b = 8;
	PerfectForward(b);            // const lvalue ref
	PerfectForward(std::move(b)); // const rvalue ref
	return 0;
}
