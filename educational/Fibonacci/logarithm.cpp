#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("lgput.in");
ofstream fout("lgput.out");

const int MOD = 1999999973;

int N; int P;

unsigned put[32]; // put[i] = N ^ (2 ^ i)

unsigned sol = 1;


int main() {

	fin >> N >> P;

	put[0] = N;

	for(int i = 1; i < 32; ++i) 
		put[i] = 1LL * put[i - 1] * put[i - 1] % MOD;
	
	for(unsigned i = 0 ; i < 32; ++i)
		if((1 << i) & P)
			sol = 1LL * sol * put[i] % MOD;

	fout << sol ;
	return 0;
}