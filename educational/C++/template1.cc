#include <stdio.h>
#include <stdlib.h>
#include "template1.h"

int main() {
		
	printf("%d\n", getmax<int>(2, 6));
	printf("%lf\n", getmax<double>(2.6, 6.7));

	KeyStorage<long> x;
	x.member = 345;
	printf("%l\n" , x.member);
	return 0;	
}
