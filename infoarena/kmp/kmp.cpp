#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e6 + 5;

char a[NMAX]; int pi[NMAX];
char b[NMAX];

vector<int> sol;
int cnt;

int main() { 

	freopen("strmatch.in", "r", stdin);
	freopen("strmatch.out", "w", stdout);

	scanf("%s", a + 1);
	scanf("%s", b + 1);

	int n = strlen(a + 1); int m = strlen(b + 1);
	pi[1] = 0;
	int p = 0;//nu am matchuit nimic

	for(int i = 2; i <= n; ++i) {
		while(p > 0 && a[p + 1] != a[i])
			p = pi[p];

		if(a[i] == a[p + 1])
			++p;

		pi[i] = p;
	}

	p = 0;

	for(int i = 1; i <= m ; ++i) {
		
		while(p > 0 && a[p + 1] != b[i])
			p = pi[p];

		if(b[i] == a[p + 1])
			++p;

		if(p == n) {
			cnt++;

			if(cnt <= 1000)
				sol.push_back(i - n);
		}

	}


	printf("%d\n", cnt);
	for(int x : sol)
		printf("%d ", x);
	return 0;
}