#include <bits/stdc++.h>

using namespace std;

ifstream fin("xormax.in");
ofstream fout("xormax.out");

const int NMAX = 1e5 + 5;
const int BMAX = 21;

struct Node {

	Node* z;
	Node* o;
	int pos; //doar pentru frunze
	Node() { z = NULL; o = NULL; }
} *root;

int n;
int a[NMAX], ans = -1, st, dr;
int sxor[NMAX];

void makestring(int x, char* s) {

	for(int i = 20 ; i >= 0 ; --i)
		if(x & (1 << i))
			s[20 - i] = '1';
		else 
			s[20 - i] = '0';

	s[21] = '\0';
}

void ins(char *s, Node* current, int pos) {

	if(*s == '\0') {
		current->pos = pos;
		return ;
	} else if(*s == '0') {

		if(current->z == NULL)
			current->z = new Node();
		ins(s + 1, current->z, pos);
	} else {

		if(current->o == NULL)
			current->o = new Node();
		ins(s + 1, current->o, pos);
	}
}

pair<int, int> search(char* s, Node* current, int x, int pos) {

	if(*s == '\0') {
		return {x, current->pos};
	} else if(*s == '0') {

		if(current->z != NULL)
			return search(s + 1, current->z, x , pos - 1);
		else 
			return search(s + 1, current->o, x + (1 << pos), pos - 1);
	} else if(*s == '1') {

		if(current->o != NULL)
			return search(s + 1, current->o, x + (1 << pos), pos - 1);
		else 
			return search(s + 1, current->z, x, pos - 1);
	}

}

int main() {

	fin >> n;

	for(int i = 1; i <= n; ++i)
		fin >> a[i], sxor[i] = sxor[i - 1] xor a[i];

	char s[22];
	makestring(0, s);
	root = new Node();
	ins(s, root, 0);

	for(int i = 1; i <= n ; ++i) {

		makestring(~sxor[i], s);
		pair<int, int> match = search(s, root, 0, 20);
		
		if( (match.first xor sxor[i]) > ans) {
			ans = match.first xor sxor[i];
			st = match.second + 1;
			dr = i;
		}

		makestring(sxor[i], s);
		ins(s, root, i);
	}

	fout << ans << ' ' << st << ' ' << dr   << '\n';

	return 0;
}