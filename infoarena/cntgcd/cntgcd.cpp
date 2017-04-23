#include <bits/stdc++.h>

using namespace std;

ifstream fin("cntgcd.in");
ofstream fout("cntgcd.out");

const int NMAX = 1e9 + 5;
const int MIL = 1e6 + 6;

typedef long long in64;

in64 n, d, x;
in64 phi[MIL], coprimes[MIL];

map<int, in64> m;
map<int, in64>::iterator it;

//f(x, d) = nr de perechi care au gcd d 
//f(x, d) = f(x / d, 1)
//f(x, 1) = x^2 - f(x, 2) - f(x, 3) - ... - f(x, x)
//f(x, 1) = x^2 - f(x/2, 1) - f(x/3, 1) - f(x/4, 1) - ... - f(x/x, 1)

in64 compute(in64 x) {

	if(x < MIL) return coprimes[x];

	it = m.find(x);
	
	if(it != m.end()) return it->second;

	in64 ans = x * x;

	in64 sqr = sqrt(1.0 * x);

	for(in64 i = 2 ; i <= sqr; ++i)
		ans -= compute(x / i);

	++sqr;

	for(in64 i = x / sqr; i >= 1; --i) {
		//[left, right] pt care x / nr == i
		//fie x cel mai mare numar care da right la impartirea cu i
		//deomnstram ca daca am imparti acest numar la right + 1 ar da mai putin de i
		//x == right * i + rest_maxim ==> rest_maxim < i (x / i == right)
		//restul daca am imparti la right + 1 si ar da tot i ar fi 
		//rest_maxim - i < 0, (scadem i pentru ca de fiecare data cand
		//right intra in x, si right + 1 intra, deci se pierde 1 fata de restul precedent)
		// deci nu e posibil => right e capatul maxim al intervalului
		in64 right = x / i;
        in64 left = x / (i + 1);

        ans -= (right - left) * compute(i);
	}

	m.insert({x, ans});

	return ans;
}

int main() {

	fin >> n >> d;

	x = n / d;

	for(int i = 1; i < MIL; ++i)
		phi[i] = i;

	for(int i = 2; i < MIL; ++i)
		if(phi[i] == i) //prim
			for(int j = i ; j < MIL; j += i) {
				phi[j] *= i - 1;
				phi[j] /= i;
			}

	//coprimes[i] = nr de perechi ( x,y) <= 1 (x, y) != (y, x)
	coprimes[1] = 1;
	
	for(int i = 2; i < MIL; ++i)
		coprimes[i] = coprimes[i - 1] + phi[i] * 2;


	in64 ans = compute(x);

	ans = (ans - 1) / 2;//scad(1, 1)

	fout << ans + 1 << '\n';//adaug (1, 1)

	return 0;	
}

