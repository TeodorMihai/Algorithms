#include <bits/stdc++.h>

using namespace std;

void fun(int&& x) {

	int y = x;
}

class Vect {
public:
	int* x;
	Vect() { }
	Vect(const Vect& v) = default;
};

int main() {

	int n;
	Vect v;
	Vect p(v);
	return 0;
}