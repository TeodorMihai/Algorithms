#include <bits/stdc++.h>

using namespace std;


ifstream fin("hack.in");
ofstream fout("hack.out");

int a[60][60];


int main() {

	
	int first = 0;

	for(int i  = 0; i < 50 ; ++i) {

		int x = i;
		int y = 0;
		while(x < 50 && y < 50) {
			x++;
			y++;
			if(y > first && y % 2 == 1)
				a[x][y] = 1;

		}
		

		x = 0;
		y = i;

		while(x < 50 && y < 50) {
			x++;
			y++;
			if(x > first && x % 2 == 1)
				a[x][y] = 1;

		}
		first++;

	}

	fout << 50 << " "<< 50 << " " << 1 << " " << 1 << '\n'; 
	for(int i = 0 ; i < 50; ++i) {
		for(int j = 0 ; j < 50 ; j++)
			fout << a[i][j];
		fout << '\n'; 
	}



	return 0;
}
