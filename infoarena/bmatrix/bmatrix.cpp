#include <bits/stdc++.h>

//O(n^2)
using namespace std;


const int NMAX = 205;
const int MMAX = 205;

#define up 0
#define down 1
#define left 0
#define right 1

ifstream fin("bmatrix.in");
ofstream fout("bmatrix.out");

int n, m;

char line[NMAX * 2];
int a[NMAX][MMAX];

int maxUp[NMAX][MMAX];
int maxDown[NMAX][MMAX];
int maxLeft[NMAX][MMAX];
int maxRight[NMAX][MMAX];

int colSquare[MMAX][2]; //left = 0, right = 1 
int lineSquare[NMAX][2]; //up = 0 , down = 1
//aria celui mai mare patrat care e mai sus / jos de linia i, inclusiv


void read() {

	fin >> n >> m;

	for(int i = 1; i <= n ; ++i) {
	
		fin >> line;
		m = strlen(line);

		for(int j = 1; j <= m ; ++j)
			a[i][j] = line[j - 1] - '0';
	
	}

}

int findBiggestArea(int v[], int len) {

	//iau fiecare "stalp"
	//consider ca el da inaltimea, ma uit cat pot sa iau in dr si in stanga si calculez
	int s[NMAX + MMAX];
	int st[NMAX + MMAX];//cat ma pot duce maxim in stanga si in dreapta cu inaltimea h inclusiv
	int dr[NMAX + MMAX];
	s[0] = 0;

	int biggest = 0;

	for(int i = 1; i <= len; ++i) {
		while(s[0] > 0 && v[s[s[0]]] >= v[i])
			s[0]--;
		if(s[0] == 0)
			st[i] = 1;
		else 
			st[i] = s[s[0]] + 1;

		s[++s[0]] = i;
	}

	s[0] = 0;

	for(int i = len; i > 0; --i) {
		

		while(s[0] > 0 && v[s[s[0]]] >= v[i])
			s[0]--;
		if(s[0] == 0)
			dr[i] = len;
		else 
			dr[i] = s[s[0]] - 1;

		s[++s[0]] = i;
	}

	for(int i = 1; i <= len; ++i)
		biggest = max(biggest, v[i] * (dr[i] - st[i] + 1));

	return biggest;
}

void solveLines() {

//up
	for(int j = 1; j <= m ; ++j)
		if(a[1][j] == 0) 
			maxUp[1][j] = 1;
		else 
			maxUp[1][j] = 0;

	
	int biggest = findBiggestArea(maxUp[1], m);
	lineSquare[1][up] = biggest;

	for(int i = 2; i <= n; ++i) {

		for(int j = 1; j <= m ; ++j)
			if(a[i][j] == 0)
				maxUp[i][j] = maxUp[i - 1][j] + 1;
			else 
				maxUp[i][j] = 0;

		int area = findBiggestArea(maxUp[i], m);

		if(biggest < area) 
			biggest = area;
		
		lineSquare[i][up] = biggest;

	}

//down

	biggest = 0;

	for(int j = 1; j <= m; ++j)
		if(a[n][j] == 0) 
			maxDown[n][j] = 1;
		else 
			maxDown[n][j] = 0;

	int area = findBiggestArea(maxDown[n], m);
	if(biggest < area)
		biggest = area;

	lineSquare[n][down] = biggest;

	for(int i = n - 1; i > 0; --i) {

		for(int j = 1; j <= m ; ++j)
			if(a[i][j] == 0)
				maxDown[i][j] = maxDown[i + 1][j] + 1;
			else 
				maxDown[i][j] = 0;

		area = findBiggestArea(maxDown[i], m);

		if(biggest < area) 
			biggest = area;
		
		lineSquare[i][down] = biggest;
	}
}

void solveCol() {

	int v[NMAX];
	int area = 0;
//left
	for(int i = 1; i <= n; ++i)
		if(a[i][1] == 0) {
			maxLeft[i][1] = 1;
			v[i] = 1;
		} else {
			maxLeft[i][1] = 0;
			v[i] = 0;
		}

	int biggest = findBiggestArea(v, n);
	colSquare[1][left] = biggest;


	for(int j = 2; j <= m ; ++j) {
	
		for(int i = 1; i <= n; ++i) {
			if(a[i][j] == 0)
				maxLeft[i][j] = maxLeft[i][j - 1] + 1;
			else 
				maxLeft[i][j] = 0;

			v[i] = maxLeft[i][j];
		}

		int area = findBiggestArea(v, n);
		if(area > biggest)
			biggest = area;

		colSquare[j][left] = biggest;

	}

//right

	for(int i = 1; i <= n; ++i)
		if(a[i][m] == 0) {
			maxRight[i][m] = 1;
			v[i] = 1;
		} else {
			maxRight[i][m] = 0;
			v[i] = 0;
		}

	biggest = findBiggestArea(v, n);
	colSquare[m][right] = biggest;

	for(int j = m - 1; j > 0; --j) {
	
		for(int i = 1; i <= n; ++i) {
			if(a[i][j] == 0)
				maxRight[i][j] = maxRight[i][j + 1] + 1;
			else 
				maxRight[i][j] = 0;

			v[i] = maxRight[i][j];
		}

		int area = findBiggestArea(v, n);

		if(area > biggest)
			biggest = area;

		colSquare[j][right] = biggest;
	}


}

void solve() {

	solveLines();
	solveCol();

	int res = 0;
	//separ printr-o linie
	for(int i = 1; i < n; ++i)
		if(lineSquare[i][up] + lineSquare[i + 1][down] > res
			&& lineSquare[i][up] > 0 && lineSquare[i + 1][down] > 0)
			res = lineSquare[i][up] + lineSquare[i + 1][down];

	for(int j = 1; j < m ; ++j)
		if(colSquare[j][left] + colSquare[j + 1][right] > res  
			&& colSquare[j][left] > 0 && colSquare[j + 1][right] > 0)
			res = colSquare[j][left] + colSquare[j + 1][right];

	fout << res << '\n';
}

int main() {

	read(); solve();
	return 0;

}