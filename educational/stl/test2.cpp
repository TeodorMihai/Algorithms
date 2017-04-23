#include <bits/stdc++.h>

using namespace std;

int main() {

	int y = 4;
	int z = 6;
	int& x = y;
	x = z;

	cout << x << '\n';
	cout << y << '\n';

	cout << ((1 << 2) + 10) << '\n';
	return 0;
}