#include <bits/stdc++.h>

using namespace std;


const int NMAX  = 102;

char s[NMAX][NMAX];

int red[NMAX];
int main() {

	int n; int d;
	cin >> n >> d;

	for(int i = 1; i <= d ; ++i) {
		cin >> s[i];

		bool ok = true;
		for(int j = 0 ; j < strlen(s[i]) ; ++j)
			if(s[i][j] == '0')
				ok = false;
		red[i] = ok;
		
	}


	int maxi = 0;
	int cnt = 0;

	for(int i = 1; i <= d; i++) {

		if(red[i] == 0)
			cnt++;
		else cnt = 0;

		if(cnt > maxi)
			maxi = cnt;
	}
	cout << maxi << '\n'; 


	return 0;
}