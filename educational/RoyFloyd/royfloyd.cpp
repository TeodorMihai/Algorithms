#include <fstream>

std::ifstream fin ("royfloyd.in");
std::ofstream fout ("royfloyd.out");

const int NMAX = 101;
const int INF = (1<<29);

int N; 

int G[NMAX][NMAX]; 

int dist[NMAX][NMAX];

void read() {

	fin >> N;

	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j) {

			fin >> G[i][j];
			
			dist[i][j] = G[i][j];
			if(G[i][j] == 0)
				dist[i][j] = INF;
		}
}

void royfloyd() {


	for(int k = 1; k <= N; ++k)
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				if(dist[i][j] >  dist[i][k] + dist[k][j] && i != j)
					dist[i][j] = dist[i][k] + dist[k][j];
}


void print() {

	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j)
			if(i != j)
			fout << dist[i][j] << " ";
		else fout << 0 << " ";
		fout << '\n';
	}
}


int main() {


	read();

	royfloyd();

	print();

	return 0;
}