#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

const int NMAX = 10000001;
const int mask = (1 << 8) - 1;


int N; int A; int B; int C;

int v[NMAX]; int u[NMAX];

int freq[mask + 1]; 

void read() {

	fin >> N >> A >> B >> C;

	v[1] = B;
	//C < 2 ^ 31
	for(int i = 2 ; i <= N; ++i)
		v[i] = (1LL * A * v[i - 1] + B) % C;
		//fout << v[i] << " ";
}

void radix_sort() {

	for(int i = 0 ;i < 31; i += 8) {

		for(int j = 0 ; j <= mask ; ++j) freq[j] = 0;

		for(int j = 1 ; j <= N; ++j) freq[mask & (v[j] >> i)]++; // cate numere cu cheia x sunt

		for(int j = 1 ; j <= mask ; ++j) freq[j] += freq[j - 1]; //freq[j] = pe a cata pozitie se afla numarull cu cheia j(maxima)
		//nr cu cea mai mica cheia != pozitia 0 
		
		for(int j = N  ; j ; --j) u[ freq[ mask & (v[j] >> i)]-- ] = v[j]; 
		//il scadem pentru ca frq[i] reprezinta cea mai mare pozitie posibila pentru numarul cu key-ul = i
		//neaparat de parcurs invers!!

		for(int j = 1 ; j <= N; ++j) v[j] = u[j];
	}
}

int main() {


	read();

	radix_sort();

	for(int i = 1; i <= N; i+=10)
		fout << v[i] << " ";

	return 0;
}