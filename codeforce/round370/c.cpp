#include <bits/stdc++.h>

using namespace std;

int main() {

	int v[4];
	int x, y;
	cin >> x >> y;

	v[0] = v[1] = v[2] = y;
	int sec = 0;

	if(x == y) {
		cout  << 0 << '\n';
		exit(0);
	}

	while(1) {

		sec++;
		sort(v , v + 3);
		v[0] = v[1] + v[2] - 1;
		if(v[0] > x)
			v[0] = x;

		if(v[0] == x && v[1] == x && v[2] == x)
			break;
	}

	cout << sec << '\n';

	return 0;
}