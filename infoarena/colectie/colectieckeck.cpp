#include <bits/stdc++.h>

using namespace std;

int ans[10];

int main() {

	int k;
	cin>> k;

	for(int i = 1; i <= k ;++i) {

		int aux = i;
		while(aux) 
			ans[aux % 10]++, aux /= 10;

	}

	for(int i = 0; i < 10 ; ++i)
		cout << ans[i] << '\n';
	return 0;
}