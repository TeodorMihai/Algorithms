#include <bits/stdc++.h>

using namespace std;

ifstream fin("pinex.in");
ofstream fout("pinex.out");

typedef long long in64;

const in64 AMAX = 1e18;
const in64 BMAX = 1e12;
const in64 RBMAX = 1e6;
//78,498 nr primes intre 0 si 1e6

int m; in64 a; in64 b;
vector<int> primes;
vector<int> diviz;
bool checked[RBMAX + 2];

void eratostene() {

	for(int i = 2;  i <= RBMAX; ++i) {

		if(checked[i] == false) {
		
			primes.push_back(i);

			for(int j = i + i; j <= RBMAX; j += i)
				checked[j] = true;
		}
	}
}


void getPrimeDivisors(in64 b) {

	diviz.clear();

	for(int x : primes) {

		if(x > b) break;

		bool divisible = false;

		while(b % x == 0) {

			b /= x;
			divisible = true;
		}

		if(divisible)
			diviz.push_back(x);
	}

	if(b > 1)
		diviz.push_back(b);
}

//nr de numere mai mici sau egale decat a si prime cu b
in64 solve(in64 a, in64 b) {

	getPrimeDivisors(b);
	//aflam nr de numere <= a, neprime cu b
	//=> nr de numere care sunt divizibile cu macar unul dintre divizori

	int n = diviz.size();
	in64 cnt = 0;

	for(int mask = 1 ; mask < (1 << n); mask++) {

		in64 d = 1;
		int bites = 0;

		for(int i = 0 ; i < n ; ++i)
			if(mask & (1 << i)) 
				d *= diviz[i], bites++;

		int parity = bites % 2 == 0 ? -1 : 1;

		cnt += parity * a / d;
	}

	return a - cnt;
}

int main() {

	fin >> m;

	eratostene();

	while(m--) {

		fin >> a >> b;

		fout << solve(a, b) << '\n';
	}

	return 0;
}