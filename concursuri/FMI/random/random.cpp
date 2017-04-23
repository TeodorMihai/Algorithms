#include <bits/stdc++.h>
using namespace std;

ifstream fin("random.in");
ofstream fout("random.out");

int main() {

	int x;
	fin >> x;

	switch(x) {

		case 1982: fout << "Robert Tarjan"; break;
		case 1986: fout <<  "Leslie Valiant"; break;
		case 1990: fout << "Alexander Razborov"; break;
		case 1994: fout << "Avi Wigderson" ; break;
		case 1998: fout << "Peter Shor"; break;
		case 2002: fout << "Madhu Sudan";  break;
		case 2006: fout << "Jon Kleinberg"; break;
		case 2010: fout << "Daniel Spielman";break; 
		case 2014: fout << "Subhash Khot" ; break;

	}

	return 0;
}