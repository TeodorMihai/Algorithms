#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int x; int y;
	int& rx = x;
	int const &ry = y;
	rx = 4;
	printf("%d", x);
	return 0;
}
