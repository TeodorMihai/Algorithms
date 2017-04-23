#include <bits/stdc++.h>

using namespace std;

const int NMAX = 106;

int n;

int v[NMAX];

int main() {

	int cnt = 0;
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
		if(v[i] == 0)
			cnt++;
	}

	int last = 0;
	int b = 0;

	for(int i = 1; i <= n; ++i) {

		if(v[i] == 0) {
			last = 0;
			b = 0;
		}

		if(v[i] == 1 || v[i] == 2) {
			if(last == 0) {
				last = v[i];
				b = 0;
			} else if(last != v[i] && b % 2 == 1) {
				cnt++;
				last = 0;
				b = 0;
			}
			else if(last == v[i] && b % 2 == 0) {
				last = 0;
				b = 0;
				cnt++;
			} 
			else b++;
		}

		if(v[i] == 3)
			b++;
	}

	cout << cnt << '\n';

	return 0;
}