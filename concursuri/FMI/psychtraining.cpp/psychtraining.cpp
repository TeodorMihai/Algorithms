#include <bits/stdc++.h>

using namespace std;

ifstream fin("psychtraining.in");
ofstream fout("psychtraining.out");
int n;
int main() {

	fin >>n;

	fout << 10 <<  '\n';

	for(int i = 0 ; i < 10 ; ++i) {

		for(int j = 0 ; j < n ; ++j)
			if(j & (1 << i))
				fout << "a";
			else fout << "b";
		fout << '\n'; 
	}
}