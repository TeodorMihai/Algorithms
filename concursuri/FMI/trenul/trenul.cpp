#include <bits/stdc++.h>

using namespace std;

ifstream fin("trenul.in");
ofstream fout("trenul.out");

const int NMAX = 100001;
const int MMAX = 100001;

int n; int m;

int tip[4];


struct cerere {

	int x; int y; int z;

	cerere(int x,int  y,int  z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

};
vector<cerere> v3;
vector<cerere> v2;
vector<cerere> v1;

int c1, c2, c3;

int cer[MMAX];

int main() {

	fin >> n >> m;

	for(int i = 0 ; i < m ; ++i) {

		int x; 
		fin >> x;
		tip[x]++;
		cer[++cer[0]] = x; 
	}

	int cnt = 1;
	
	while(tip[3]) {

		tip[3]--;
		v3.push_back(cerere(cnt, cnt + 1, cnt + 2));
		cnt += 3;
	}

	while(tip[1]) {

		tip[1]--;
		v1.push_back(cerere(cnt, 0, 0));
		cnt++;
	}

	if(cnt % 2 == 0)
		cnt++;

	while(tip[2]) {

		tip[2]--;
		v2.push_back(cerere(cnt, cnt + 1, 0));
		cnt += 2;
	}

	c3 = c2 = c1 = 0;
	for(int i = 1 ; i <= cer[0] ; ++i) {	

		//fout <<c3 << " " << cer[i] << " " << v3[c3].x << '\n'; 
		if(cer[i] == 3) {
			fout << v3[c3].x << " " << v3[c3].y << " "<< v3[c3].z << '\n';

			c3++;
		}

		if(cer[i] == 2) {
			fout << v2[c2].x << " " << v2[c2].y << '\n';
			c2++;
		}

		if(cer[i] == 1) {
			fout << v1[c1].x << '\n'; 
			c1++;
		}
	}



	return 0;	
}