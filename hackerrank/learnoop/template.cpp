#include <bits/stdc++.h>

using namespace std;

template<class T>
int maxi(T a) {
	cout << 3 << '\n';
}
template<>
int maxi(double a) {
	cout << 4 << '\n';
}

int main() {

	double a = 5.0;
	maxi(a);
	maxi(3);

	return 0;
}