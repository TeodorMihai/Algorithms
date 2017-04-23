#include <bits/stdc++.h>

using namespace std;

#define pp pair<in64, int>

const int NMAX = 1e9;

typedef long long in64;

in64 n;

in64 np;

vector<pp> divizor;

int prod = 1;

void back(int k, in64 nr) {

	if(k == divizor.size()) {

		in64 s = nr;
		in64 d = np / nr;
		if(s < d)
			swap(s, d);

		if( (s + d) % 2 == 0) {
			in64 y = (s + d) / 2;
			in64 x = s - y;

			if(x > 0 && x <= 1e18 && y <= 1e18 && y > 0) {
				cout << x <<  ' ' << y  << '\n';
				exit(0);
			}
		}
	} else {

		back(k + 1, nr);
		in64 prod = 1;

		for(int i = 1 ; i < divizor[k].second; ++i) {
			prod = 1ll * divizor[k].first * prod;
			back(k + 1, nr  * prod);
		}
	}
}
int main() {

	cin >> n;
	np = 1ll * n * n;

	int aux = n;

	for(int i = 2; i * i <= n; ++i) {

		int cnt = 0;

		while(n % i == 0) n /= i, cnt++;

		if(cnt > 0)
			divizor.push_back({i, cnt * 2});
	}

	if(n > 1)  
		divizor.push_back({n, 2});

	back(0, 1);

	cout << -1 << '\n';

	return 0;
}