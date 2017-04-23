#include <bits/stdc++.h>

using namespace std;

int main() {


	int x = -5;

	char *p = NULL;

	p = new char;
	*p = 22;

	printf("%p\n", p);
	printf("%x\n", p[0]);
	printf("%X\n", x);
	return 0;
}