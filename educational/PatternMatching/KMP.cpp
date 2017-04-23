#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int NMAX = 2000001;
const int MOD1 = 10004;
const int MOD2 = 10003;

int N; int M;

char A[NMAX]; char B[NMAX];

int match[NMAX];


vector<int> KMP(char* A, char* B) {

	vector<int> sol;

	match[1] = 0; 
	match[0] = 0;
	int pos = 0;

	for(int i = 2; i <= N; ++i ) {

		while(pos > 0 &&  A[i] != A[pos + 1] )
			pos = match[pos];

		if(A[i] == A[pos + 1]) 
			match[i] = pos++ + 1;		
		else 
			match[i] = 0;
	}

	pos = 0 ;

	for(int i = 1; i <= M; ++i) {

		while(pos > 0 && A[pos + 1] != B[i])
			pos = match[pos];

		if(B[i] == A[pos + 1])
			pos++;
		else 
			pos = 0;

		if(pos == N)
			sol.push_back(i - N);
	}

	return sol;
}


int main() {

	fin >> A + 1;
	fin >> B + 1;

	N = strlen(A + 1);
	M = strlen(B + 1);
	vector<int> sol;

	sol = KMP(A, B);


	fout << sol.size()  << '\n'; 
	
	for(unsigned i = 0 ; i < sol.size() && i < 1000; ++i)
		fout << sol[i] << " " ;

	return 0;
}