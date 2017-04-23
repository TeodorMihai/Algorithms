#include <stdio.h>
#include <stdlib.h>
#include "const.h"	

Complex::Complex(double x, double y) {
	this -> re = x;
	this -> im = y;
}

double Complex::getRe()const {
	return this -> re;
}

double Complex::getIm() const {
	return this -> im;
}
void Complex::setRe(double x) {
	this -> re = x;
}

void Complex::setIm(double y) {
	this -> im = y;
}

int main() {
	
 	Complex c1(3,4);
	const Complex c2(4,5);
	printf("%lf\n", c1.getRe());	
	return 0;
} 
