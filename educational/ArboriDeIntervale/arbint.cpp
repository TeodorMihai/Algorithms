#include <bits/stdc++.h>

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

const int NMAX = 100001;

int N; int M;

int v[NMAX]; 

int A[NMAX * 4];


void construct(int vertex, int left, int right) {


	if(left == right) {

		A[vertex]  = v[left];
		return ;
	}

	int middle = (left + right) / 2;

	construct(vertex * 2, left, middle);
	construct(vertex * 2 + 1, middle + 1, right);

	A[vertex] = max(A[vertex * 2], A[vertex * 2 + 1]);
}

void modify(int vertex, int left, int right, const int &change, const int &value) {

	if(left == right) {

		A[vertex] = value;
		return ;
	}

	int middle = (left + right) / 2;

	if(change <= middle)
		modify(vertex * 2, left, middle, change, value);
	else 
		modify(vertex * 2 + 1 , middle + 1, right, change, value);

	A[vertex] = max(A[vertex * 2], A[vertex * 2 + 1]);
}


int  getValue(int vertex, int left, int right,const int& st,const int& dr) {


	if(st <= left && right <= dr) {
		return A[vertex]; //il include complet
	}


	int middle = (left + right) / 2;
	int maximum = 0;

	if(st <= middle ) maximum = getValue(vertex * 2, left, middle, st , dr); 

	//neaparat compar cu middle!!
	if(middle  + 1 <= dr) maximum = max(maximum, getValue(vertex * 2 + 1, middle + 1, right, st , dr));

	return maximum;
}

int main() {


	int type; 
	
	int x; int y;

	fin >> N >> M;

	for(int i = 1 ; i <= N; ++i) 
		fin >> v[i];

	construct(1, 1, N);

	while(M--) {

		fin >> type >> x >> y;
		
		switch(type) {

			case 0: fout << getValue(1, 1, N, x, y)  << '\n'; break;
			case 1: modify(1, 1, N, x, y);  break;
		}
	}

	return 0;
}