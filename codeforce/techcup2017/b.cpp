#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2005;

char s[NMAX];

long long sum;


void print(double sum) {


	int v[30];
	long long nr = 0;

	long long intreg = sum;
	long long aux = intreg;


	if(intreg == 0)
		cout << 0;		
	else {
		while(intreg > 0) {
			v[++nr] = intreg % 10;
			intreg /= 10;
		}

		for(int i = nr; i > 0 ; --i)
			if(i % 3 == 0 && i != nr)
				cout << '.' << v[i];
			else 
				cout << v[i];
	}



	long long res = sum * 100ll - aux * 100;

	if(res != 0) {

		cout << '.';
		if(res < 10)
			cout << '0';
		cout << res % 100;
	}

	cout << '\n';
}

int main() {


	cin >> s;

	int n = strlen(s);

	int p = 0;
	while(p < n) {
		while(p < n && s[p] >= 'a' && s[p] <= 'z') ++p;
		
		long long x = 0;
		int cnt = -100;
		
		while(p < n && !(s[p] >= 'a' && s[p] <= 'z')) {

			if(s[p] == '.') {
			 	cnt = 0; 
			 	++p;
			 } else {
				x = x * 10 + s[p] - '0';
				++cnt;
				++p;
			}
		}
		if(cnt == 2) 
			sum += x;
		else 
			sum += x * 100;
	}

	print(sum);
	//cout << fixed << setprecision(2) << sum << '\n';

	return 0;
}