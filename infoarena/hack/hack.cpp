#include <bits/stdc++.h>

using namespace std;

ifstream fin("hack.in");
ofstream fout("hack.out");

const int NMAX = 55;

#define PII pair<int, int>
#define VI vector<int>

vector<string> A;
 
const int INFINIT = 1000000;
const int dx[5] = {0, 0, 1, -1};
const int dy[5] = {1, -1, 0, 0};
 
int getDistance(vector<string> &A, PII start) {
    int n = A.size(), m = A[0].size();
    int COUNTER = 0;
 
    start.first--, start.second--; // reindexam de la 0.
 
    queue<PII> Q;
    vector<VI> d(n, vector<int> (m, INFINIT)); 
    d[start.first][start.second] = 0;
    Q.push(start);
   
    while(!Q.empty()) {
        PII node = Q.front();
        Q.pop();
         
        COUNTER++;
 
        for(int dir = 0; dir < 4; ++dir) {
            int newX = node.first + dx[dir];
            int newY = node.second + dy[dir];
            if(newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            int cost = 0;
            if(A[node.first][node.second] != A[newX][newY]) 
                cost = 1;
             
            if(d[node.first][node.second] + cost < d[newX][newY]) {
                d[newX][newY] = d[node.first][node.second] + cost;
                Q.push({newX, newY});
            }
        }
    }
 
    return COUNTER;
}

int check(int offset, int i, int j) {

	if(( (j + offset) == 49 || (i - offset) == 0 || 
			(i + offset) == 49 || (j - offset) == 0 ) && 
		i >= offset && j >= offset && i < 50 - offset && j < 50 - offset)
		return 1;
	return 0;
}

void construct() {

	string line;

	int offset = 0;
	for(int i = 0 ; i < 50; ++i) {
		line.clear();
		for(int j = 0 ; j < 50; ++j)
			if( check(0, i, j) ||  (i == j && i < 25) || 
			(i == 50 - j && i > 4  && i < 45 && j > 4 && j < 45)
			|| (i == 45 && j > 4 && j < 33)
			|| (j == 45 && i > 4 && i < 33) )
				line.push_back('0');
			else {

				char par = j % 2 ? '1' : '0';
				char opPar;
				if(par == '0')
					opPar = '1';
				else 
					opPar = '0';

				line.push_back(i % 2 ? par : opPar);
			}
			cout << line << '\n'; 
		A.push_back(line);
	}
}

int main() {

	construct();
	fout << 50 << ' ' << 50 << ' ' << 40 << ' ' << 48 << "\n";
	for(int i = 0 ; i < 50 ; ++i)
		fout << A[i] << '\n'; 
	//fout <<  getDistance(A, make_pair(40, 48)) << '\n'; 
	return 0;
}