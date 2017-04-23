#include <stdio.h>
#include "complex.h"

int main() {

	Complex number(2, 5);
	Complex *nr = new Complex(2, 4);
	printf("%.3lf %.3lf\n", number.getRe(), number.getIm() );
	printf("%.3lf %.3lf\n", nr->getRe(), nr->getIm() );
	delete nr;

	Complex *v = new Complex[10];
	
	printf("%.3lf\n", v[2].getIm());
	delete[] v;

	int **mat ;
	mat = new int*[100];
	for(int i = 0 ;i < 100; ++i)
		mat[i] = new int[33];

	return 0;
}
