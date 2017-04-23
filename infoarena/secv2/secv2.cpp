#include <bits/stdc++.h>

using namespace std;

ifstream fin("secv2.in");
ofstream fout("secv2.out");

const int NMAX = 5e4 + 5;

int n; int k;
int sum[NMAX], v[NMAX], best[NMAX], ind[NMAX];

int st , dr, b = -0x3f3f3f3f;

int main()  {

	fin >> n >> k;
	for(int i = 1; i <= n ; ++i)
		fin >> v[i], sum[i] = sum[i - 1] + v[i];

	//maxi[i] = max(a[i] + a[i - 1] + ... a[i - K + 1], best[i - K] + a[i - k + 1] + .. a[i])
	//unde best[i] cel mai mare subsecventa acre se termina si il include pe i
	best[0] = -0x3f3f3f3f;
	for(int i = 1; i <= n ; ++i) {

		if(best[i - 1] + v[i] > v[i]) {
			best[i] = best[i - 1] + v[i];
			ind[i] = ind[i - 1];
		} else {
			best[i] = v[i];
			ind[i] = i;
		}
	}

	for(int i = k ; i <= n; ++i) {

		int s = sum[i] - sum[i - k];
		if(s >= best[i - k] + s) {
			if(s > b) {
				b = s;
				st = i - k + 1;
				dr = i;
			}
		} else {

			if(best[i - k] + s > b) {
				b = best[i - k] + s;
				st = ind[i - k];
				dr = i;
			}
		}

	}

	fout << st << ' ' << dr << ' ' << b << '\n';

	return 0;
}
