#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100009;

char s[NMAX];
int main()  {

	cin >> s;
	cout << s;

	for(int i = strlen(s) - 1; i >= 0 ; --i)
		cout << s[i];
	cout << '\n';
	return 0;
}

