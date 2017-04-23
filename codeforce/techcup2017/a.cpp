#include <bits/stdc++.h>

using namespace std;

typedef long long in64;

const int NMAX = 33;

in64 a, b;
in64 sol[NMAX];

void back(int k, in64 nr) {
	//k = cate operatii am facut pana acum obtinand nr
	if(nr > b) return ;
	
	if(nr == b) {

		cout << "YES\n";
		cout << k << '\n';

		for(int i = 1 ; i <= k ; ++i)
			cout << sol[i] << ' ';
		exit(0);

	} else {

		sol[k + 1] = nr * 2;
		back(k + 1, nr * 2);
		sol[k + 1] = nr * 10 + 1;
		back(k + 1, nr * 10 + 1);
	}
}	

int main() {

	cin >> a >> b;
	sol[1] = a;
	back(1, a);
	cout << "NO\n";

	return 0;
}