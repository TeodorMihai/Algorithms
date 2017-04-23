#include <fstream>
#include <queue>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

const int NMAX = 10000001;

int N; int A; int B; int C;

int v[NMAX];

const int mask = (1 << 8) - 1;

queue<int> Q[2][mask + 1];


void read() {

	fin >> N >> A >> B >> C;

	v[1] = B;
	//C < 2 ^ 31
	for(int i = 2 ; i <= N; ++i)
		v[i] = (1LL * A * v[i - 1] + B) % C;
}

void radix_sort() {



	int bits = 0;

	for(int i = 1; i <= N; ++i)
		Q[0][ v[i] & mask ].push(v[i]);

	for(int k = 0 ; k < 4; ++k)  {//first 32 bit digits

		int ind = k % 2;
		int other = (ind + 1) % 2;

		for(int i = 0 ; i <= mask ; ++i)
			while(Q[ind][i].empty() == false) {

				int x = Q[ind][i].front();

				Q[other][(x >> bits) & mask].push(x);
				Q[ind][i].pop();
			}
				
		bits += 8;
	}

	int last = 0; int cnt = 0;

	for(int i = 0 ; i <= mask ; ++i)
		while(Q[last][i].empty() == false) {

			v[++cnt] =  Q[last][i].front();

			Q[last][i].pop();
		}

	
}

int main() {


	read();

	radix_sort();

	for(int i = 1; i <= N; i += 10)
		fout << v[i] << '\n' ;

	return 0;
}