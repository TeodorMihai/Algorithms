#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("kfib.in");
ofstream fout("kfib.out");

const int MOD = 666013;


int N;

int A[][2] = { {0 , 1}, {1 , 1}};

int puteri[32][2][2];

int sol[2][2];

void inm(int C[2][2], int B[][2], int A[][2]) {

	for(int i = 0 ; i < 2; ++i)
		for(int j = 0 ; j < 2; ++j)  {	

			C[i][j]  = 0;
			
			for(int k = 0; k < 2; ++k)
				C[i][j] = (1LL * B[i][k] * A[k][j] + 1LL * C[i][j]) % MOD;
		}
}


int main() {

	fin >> N;

	int aux[2][2];
	
	sol[0][0] = sol[1][1] = 1;
	sol[1][0] = sol[0][1] = 0;

	memcpy(puteri[0], A, sizeof A);

	//putere[i] = A^(2^i)	
	//(f1, f2) * (0 1) = (f2, f1 + f2)
	//            1 1 
	
	for(int i = 1; i < 31; ++i) 
		inm(puteri[i], puteri[i - 1], puteri[i - 1]);

	for(int i = 0 ; i < 31; ++i)
		if((1 << i) & N) {

			memcpy(aux, sol , sizeof sol);//avem nevoie pentru ca se modifica valorile pt sol in timp ce calculam noul sol
			
			inm(sol, aux, puteri[i]);
		}

	fout << sol[1][0] ;
	
	return 0;
}