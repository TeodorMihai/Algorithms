#include <bits/stdc++.h>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int NMAX = 2e6 + 6;

int n, m;
char a[NMAX], b[NMAX];
int pii[NMAX];
vector<int> ans;

int main() {

	fin >> a + 1; n = strlen(a + 1);
	fin >> b + 1; m = strlen(b + 1);

	pii[1] = 0; int p = 0;

	for(int i = 2; i <= n ; ++i) {

		while(p > 0 && a[p + 1] != a[i])
			p = pii[p];

		if(a[p + 1] == a[i])
			++p;

		pii[i] = p;
	}

	p = 0;

	int cnt = 0;

	for(int i = 1; i <= m ; ++i) {

		while(p > 0 && a[p + 1] != b[i])
			p = pii[p];

		if(a[p + 1] == b[i])
			++p;

		if(p == n) {
			cnt++;
			if(cnt <= 1000)
				ans.push_back(i - n);
		}
	}
	fout << cnt << '\n';
	for(int x : ans)
		fout << x << ' ';

	return 0;
}