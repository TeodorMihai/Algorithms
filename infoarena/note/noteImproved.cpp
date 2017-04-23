#include <fstream>
#include <bitset>

using namespace std;

#define DELETE 1
#define INSERT 1
#define SUBSTITUTE 1

ifstream fin("note.in");
ofstream fout("note.out");

const int VMAX = (1<<9);
const int NMAX = (1<<10);
const int VALMAX = 100;

int d[NMAX + 1][NMAX + 1];

int b[NMAX + 1];

//d[i][j] = costul minim de a broda solfegiul [1...j] la toate partiturile de lungime [1...i]
int v; int n; int m;

bitset<VALMAX + 1> thereis[NMAX + 1];

void read() {

	fin >> v >> n;
	
	int x;

	for(int i = 1; i <= v; ++i) 
		for(int j = 1; j <= n; ++j) {
		
			fin >> x;
			thereis[j][x] = true; 
		}

	fin >> m;

	for(int i = 1; i <= m; ++i)
		fin >> b[i];

	fin.close();
}

void solve() {

	d[0][0] = 0;

	for(int i = 0 ; i <= m ; ++i)
		d[0][i] = i; //le stergem e toate

	for(int i = 1; i <= n; ++i)
		d[i][0] = i; //le inseram pe toate

	int cost = 0;

	//putem modifica doar b => 
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {

			if(thereis[i][b[j]])
				d[i][j] = d[i - 1][j - 1];
			else d[i][j] = d[i - 1][j - 1] + SUBSTITUTE;

			if(d[i][j] > d[i - 1][j] + DELETE)
				d[i][j] = d[i - 1][j] + DELETE;

			if(d[i][j] > d[i][j - 1] + INSERT)
				d[i][j] = d[i][j - 1] + INSERT;
		}

	fout << d[n][m] << '\n'; 
}

int main() {

	read();

	solve();

	return 0;
}