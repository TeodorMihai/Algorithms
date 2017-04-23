#include <fstream>
#include <queue>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

const int NMAX = 10000001;

int N; int A; int B; int C;

int v[NMAX];

const int byte = (1 << 8) - 1;

queue<int> Q[byte + 1];


void read() {

	fin >> N >> A >> B >> C;

	v[1] = B;
	//C < 2 ^ 31
	for(int i = 2 ; i <= N; ++i)
		v[i] = (1LL * A * v[i - 1] + B) % C;
}

void radix_sort() {



	int mask = 0;

	for(int k = 0 ; k < 4; ++k)  {

		for(int i = 1; i <= N; ++i)
			Q[ (v[i] >> mask) & byte].push(v[i]);
		
		int cnt = 0;

		for(int i = 0 ; i < byte + 1; ++i)
			while(Q[i].empty() == false) {

				v[++cnt] = Q[i].front();

				Q[i].pop();
			}
			
		mask += 8;
	}
	
}

int main() {


	read();

	radix_sort();

	for(int i = 1; i <= N; i += 10)
		fout << v[i] << " " ;

	return 0;
}