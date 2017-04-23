#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5 + 5;

char s[NMAX];

int cnt[300];

int main() {

	cin >> s;

	int trident = 0;

	int n = strlen(s);

	if(n % 2 == 1) {

		cout << -1 << '\n';
		exit(0);
	}

	for(int i = 0 ; i < n; ++i)
		cnt[s[i]]++;

	int x1 = max(cnt['L'], cnt['R']) - min(cnt['L'], cnt['R']);
	int x2 = max(cnt['U'], cnt['D']) - min(cnt['U'], cnt['D']);

	trident += x1 / 2 + x2 / 2;

	if(x1 % 2 == 1)
		trident++;

	cout << trident << '\n';

	return 0;
}