#include <bits/stdc++.h>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int NMAX = 100009;

int n;

int v[NMAX];
int ind[NMAX];
int aib[NMAX];
int best[NMAX];
int ret[NMAX];
int in[NMAX]; //in[i] = unde s-ar afla elelemntul i, daca vectorul ar fi sortat

//aib[i] = infoamtia de pe intervalul [i - 2^zerouri(i) + 1, i], 
//retin retin indexul in vectorul initial

int bite(int x) {
	return x & (-x);
}//numarul reprezentat doar de cel mai nenemnificativ bit de i al lui x


struct comparisonObj {

	//must be unstable sort, reverse the order oth the element that are equal
	//v[x] == v[y], swap only if y < x, this means to reverse
	bool operator() (const int& x,const int& y) const { 

		if(v[x] == v[y])
			return x > y;

		return v[x] < v[y];
	}

} cmp1;


void update(int pos, int value) {

	while(pos <= n) {
		//parcurg toate intervalele care il contin  pe pos initial
		if(best[value] > best[aib[pos]])
			aib[pos] = value;
		//pe intervalul pos, cel mai bun numar e numarul cu indexul value

		pos += bite(pos);
	}
}

int query(int pos) {

	int posMax = 0;

	while(pos > 0) {

		if(best[posMax] < best[aib[pos]])
			posMax = aib[pos];

		pos -= bite(pos);
	}

	return posMax;
}

void printSol(int last) {

	if(last == 0) return ;

	printSol(ret[last]);

	fout << v[last] << ' ';
}

int main() {

	fin >> n;

	for(int i = 1; i <= n ; ++i) {
		fin >> v[i]; ind[i] = i;

	}

	sort(ind + 1, ind + 1 + n, [] (int x,int y) { 

		if(v[x] == v[y])
			return x > y;

		return v[x] < v[y];
	});
	//in[i] = unde s-ar afla eelementul i, daca vectorul ar fi sortat
	//ind[1] - indicele celui mai mic element

	for(int i = 1; i <= n; ++i)
		in[ind[i]] = i;//ind[i], indicele celui de-al i-lea element in vectorul sortat, 
						//in este functia inversa lui ind

	int maxi = -1;
	int last ;

	for(int i = 1; i <= n ; ++i) {
		//ind[i] = indicele celu de al i-lea element
		int q = query(in[i]);//intoarce maximul (dpdv best) de pe intervalul [1...in[i]]
		best[i] = best[q] + 1;
		ret[i] = q;

		update(in[i], i);

		if(maxi < best[i]) {
			last = i;
			maxi = best[i];
		}
	}

	fout << maxi << '\n'; 

	printSol(last);


	return 0;
}