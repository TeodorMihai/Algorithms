#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200009;

int n; char s[NMAX];

int d[NMAX];

int main() {


	cin >> n;
	cin >> s + 1;

	for(int i = 1; i <= n ; ++i)
		cin >> d[i];

	int minD = 0x3f3f3f3f;

	for(int i = 1; i <= n ; ++i)
		if(i != 1 && i != n)
			if(s[i] == 'R' && s[i + 1] == 'L')
				minD = min(minD, (d[i + 1] - d[i]) / 2);

	if(s[1] == 'R' && s[2] == 'L')
		minD = min(minD, (d[2] - d[1]) / 2);
	if(minD == 0x3f3f3f3f)
		cout << -1 << '\n';
	else 
		cout << minD << '\n';


	return 0;
}