#include <bits/stdc++.h>
using namespace std;


int v[100003];

const int MOD = 100000 ;

vector<int> sol;
	
int mark[100];
int s[100];

int cnt;

int c[100003];
int d[100003];

int n;

int ok(int x, int y, int z) {

	if(x < y && y < z)
		return 0;
	if(x > y && y > z)
		return 0;
	return 1;
}

void back(int x) {

	if(x == n + 1) {


		
		cnt++;

	} else {

		for(int i = 1; i <= n; ++i)
			if(mark[i] == 0 && (x == 1 || x == 2 ||  ok(i, s[x - 1], s[x - 2])  ) ) {

				mark[i] = 1;
				s[x] = i;

				back(x + 1);

				mark[i] = 0;
			}
	}
}

int main() {

	int T;

	cin >> T;

	v[1] = 1;
	v[2] = 2;
	c[2] = 0 ;
	d[3] = 0;



	while(T--) {

		cin >> n;

		for(int i = 3; i <= n ; ++i) {
			
			int x = i - 1;
			c[i] = 0;
			d[i] = 0;
			if(x % 2 == 0) {
				v[i] = (1ll * (v[i - 1] / 2 )* (x / 2 +1) + 1ll* (v[i - 1] / 2 ) * (x / 2 + 1) + 1ll * c[i - 2]   ) % MOD;
				c[i] = 1ll * (x + 1 - x/2 - 1) * v[i - 1] + d[i - 1];
				d[i] = v[i - 2] * x/2;


			} else {

				v[i] = (1ll * (v[i - 1] / 2) * (x / 2 + 2) + 1ll * (v[i - 1] / 2 ) * (x / 2 + 1) + c[i - 2] ) % MOD;
				c[i] += 1ll * (x + 1 - x/2 - 2) * v[i - 1] / 2 + 1ll * (x + 1 - x/2 - 1) * v[i - 1] / 2  + d[i - 1];
				d[i] = v[i - 2] * (x/2 + 1);
			}
			 
		}
		sol.push_back(v[n]);
	}

	for(unsigned i = 0 ; i < sol.size(); ++i)
		cout << sol[i] << '\n'; 


	back(1);

	cout << cnt << '\n'; 
	return 0;
}