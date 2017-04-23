#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int NMAX = 2000001;
const int MOD1 = 100004;
const int MOD2 = 100003;

int N; int M;

char A[NMAX]; char B[NMAX];


vector<int> RabinKarp(char* A, char* B) {

	vector<int> sol;

	int p1 = 1; int p2 = 1;

	int interval = 'z' - '0';


	int hashA1 = 0; int hashB1 = 0;
	int hashA2 = 0; int hashB2 = 0;

	for(int i = 0 ; i < N; ++i) {

		hashA1 = ( hashA1 * interval +  (A[i] - '0') ) % MOD1;
		hashA2 = ( hashA2 * interval +  (A[i] - '0') ) % MOD2;
		
		if(i) {
			p1 =  p1 * interval % MOD1;
			p2 =  p2 * interval % MOD2;
		}
	}

	if(N > M) 
		return sol;

	for(int i = 0; i < N; ++i) {

		hashB1 = ( hashB1 * interval +  (B[i] - '0') )% MOD1;
		hashB2 = ( hashB2 * interval +  (B[i] - '0') )% MOD2;
		
	}

	for(int i = N; i < M; ++i) {

		if(hashB1 == hashA1 && hashA2 == hashB2 )
			sol.push_back(i - N);

		hashB1 = (hashB1 - p1 * (B[i - N] - '0' ) ) % MOD1;
		hashB2 = (hashB2 - p2 * (B[i - N] - '0' ) ) % MOD2;

		if(hashB1 < 0)
			hashB1 += MOD1;

		if(hashB2 < 0) 
			hashB2 += MOD2;

		hashB1 = ( hashB1 * interval +  (B[i] - '0') )% MOD1;
		hashB2 = ( hashB2 * interval +  (B[i] - '0') )% MOD2;
	}

	if(hashB1 == hashA1 && hashA2 == hashB2 )
			sol.push_back(M - N);

	return sol;

}


int main() {

	fin >> A;
	fin >> B;

	N = strlen(A);
	M = strlen(B);
	vector<int> sol;

	sol = RabinKarp(A, B);


	fout << sol.size()  << '\n'; 
	for(unsigned i = 0 ; i < sol.size() && i < 1000; ++i)
		fout << sol[i] << " " ;

	return 0;
}