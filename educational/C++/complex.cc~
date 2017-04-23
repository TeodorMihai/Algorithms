#include "complex.h"

/*
Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;
}
*/

//alt tip de constructor
Complex::Complex() {

}

Complex::Complex(double real, double imaginar):
	re(real),
	im(imaginar) {
}

Complex::~Complex() {

}

Complex Complex::conjugate() {

	Complex conjugat(this -> re, -(this -> im));
	return conjugat;
}

double Complex::getRe() {
	return this->re;
}

double Complex::getIm() {
	return this->im;
}
