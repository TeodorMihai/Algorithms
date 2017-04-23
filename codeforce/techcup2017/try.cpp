#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2005;

char s[NMAX];

long long sum;


void print(long long sum) {


	int v[30];
	long long nr = 0;

	long long intreg = sum;


	while(intreg > 0) {
		v[++nr] = intreg % 10;
		intreg /= 10;
	}

	long long rest = sum % 100;


	if(sum < 100)
		cout << 0;
	
	for(int i = nr; i > 2 ; --i) {

		if( (i - 2) % 3 == 0 && i != nr)
			cout << '.' << v[i];
		else 
			cout << v[i];
	}

	if(rest != 0) {
		cout << '.';

		if(rest < 10)
			cout << 0;
		cout << rest ;

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