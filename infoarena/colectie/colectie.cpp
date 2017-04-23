#include <bits/stdc++.h>

using namespace std;

ifstream fin("colectie.in");
ofstream fout("colectie.out");

const int NMAX = 32;
const int KMAX = 1e8 + 5;

int calup[10][10][2]; //calup[i][j] = nr de cifre de j continute in numerele de i cifre
//[0] = fara 0 ca prima cifre
//[1] = cu 0 ca prima cifra
int nri[10];//nri[i] = nr de numere invalide de i cifre
int nrv[10];//valide (nu incep cu 0)
int ans[10];
int n, k;

int cutie[32][10];
int sumc[1<<16][12];
int ind[1<<16];
int pos[10];
int m, mask1, mask2;
int b = 0x3f3f3f3f; 
int conf1, conf2;
int s[10];

void findDigits(int k) {

	for(int i = 0 ; i < 10; ++i)
		calup[1][i][0] = calup[1][i][1] = 1;

	nri[1] = nrv[1] = 10;

	for(int i = 2; i < 10; ++i) {

		for(int j = 0 ; j < 10; ++j) {
			if( j != 0 )
				calup[i][j][0] = calup[i - 1][j][1] * 9 + nri[i - 1];
			else 
				calup[i][j][0] = calup[i - 1][j][1] * 9;

			calup[i][j][1] = calup[i - 1][j][1] * 10 + nri[i - 1];
		}

		nrv[i] = nrv[i - 1] * 9;
		nri[i] = nri[i - 1] * 10;
	}


	int auxk = k;
	int nrc = 0;
	int pten = 1;

	while(auxk) {
		nrc++, auxk /= 10, pten *= 10;

		if(auxk)
			for(int i = 0 ; i < 10; ++i)
				ans[i] += calup[nrc][i][0];
	}

	auxk = k;
	pten /= 10;
	int fst = 0;

	while(pten) {

		int cn = (auxk % (pten * 10)) / pten;
		cn--; nrc--;

		if(fst == 1) {
			for(int i = 0 ; i < 10; ++i)
				ans[i] += (cn + 1) * calup[nrc][i][1];

			for(int i = 0 ; i <= cn; ++i) 
				ans[i] += pten;
			ans[cn + 1] += auxk % pten + 1;
		} else {

			for(int i = 0 ; i < 10; ++i)
				ans[i] += cn * calup[nrc][i][1];

			for(int i = 1; i <= cn; ++i)
				ans[i] += pten;
			ans[cn + 1] += auxk % pten + 1;
		}

		fst = 1;	
		pten /= 10;
	}

	ans[0]--;
}

struct cmp {

	bool operator()(int x, int y) {
		
		for(int i = 0 ; i < 10; ++i) {
			if(sumc[x][i] < sumc[y][i])
				return true;
			else if(sumc[x][i] > sumc[y][i])
				return false;
		}

		return sumc[x][10] > sumc[y][10];
	}

} cmpS;

void cauta(int v[12], int& cnt, int c2) {

	int step , p;

	step = 1 << m;

	for(p = 0 ; step ; step >>= 1)
		if(p + step <= mask1) {

			int ok = 1;
			
			for(int i = 0 ; i < 10; ++i) {
				if(sumc[ind[p + step]][i] + v[i] < ans[i]) { 
					ok = 0; 
					break;
				} else if(sumc[ind[p + step]][i] + v[i] == ans[i]) 
					ok = 0; 
				else  {
					ok = 1;
					break;
				}
			}

			if(ok == 0) p += step;
		}


	int ok = 1;
	for(int i = 0 ; i < 10 ; ++i) 
		if( (sumc[ind[p]][i] + v[i]) != ans[i])
			ok = 0;

	if(ok == 1 && cnt  + sumc[ind[p]][10] < b) {

		b = cnt + sumc[ind[p]][10];
		conf1 = sumc[ind[p]][11];
		conf2 = c2;
	}
}

int main() {

	fin >> n >> k;
	m = n / 2;
	//[0...m) [m .. n)
	findDigits(k);

	for(int i = 0; i < n ; ++i)
		for(int j = 0 ; j < 10; ++j)
			fin >> cutie[i][j], s[j] += cutie[i][j];

	mask1 = (1 << m) - 1;

	for(int i = 0 ; i <= mask1; ++i) {

		int cnt = 0;

		for(int j = 0 ; j < m; ++j)
			if(i & (1 << j)) {
				for(int l = 0 ; l < 10; ++l)
					sumc[i][l] += cutie[j][l];
				cnt++;
			}

		sumc[i][10] = cnt;
		sumc[i][11] = i;
	}

	for(int i = 0 ; i <= mask1; ++i)
		ind[i] = i;

	sort(ind , ind + mask1 + 1, cmpS);

	mask2 = (1 << (n - m)) - 1;

	for(int i = 0 ; i <= mask2; ++i) {

		for(int j = 0 ; j < 10; ++j)
			pos[j] = 0;
		
		int cnt = 0;

		for(int j = 0 ; j < n - m; ++j)
			if(i & (1 << j)) {
				for(int l = 0 ; l < 10; ++l)
					pos[l] += cutie[j + m][l];
				cnt++;
			}
		cauta(pos, cnt, i);
	}

	if(b == 0x3f3f3f3f) {
		fout << 0 << '\n';
	} else {

		fout << 1 << '\n';
		fout << b << '\n';

		for(int i = 0 ; i < m; ++i)
			if(conf1 & (1 << i))
				fout << i + 1 << ' ';

		for(int i = 0 ; i < (n - m); ++i)
			if(conf2 & (1 << i))
				fout << i + m + 1 << ' ';

		fout << '\n';
	}

	return 0;
}